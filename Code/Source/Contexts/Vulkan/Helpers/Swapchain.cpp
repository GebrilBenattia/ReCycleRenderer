#include "Swapchain.hpp"
#include <stdexcept>
#include <algorithm>
#include <PhysicalDevice.hpp>
#include <VulkanImages.hpp>
#include <Framebuffers.hpp>
#include <Renderer.hpp>
#include <VulkanContext.hpp>

VkSurfaceFormatKHR Swapchain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR Swapchain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _AvailablePresentModes)
{
    for (const auto& availablePresentMode : _AvailablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Swapchain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& _Capabilities)
{
    VulkanContext* context = reinterpret_cast<VulkanContext*>(Renderer::context);

    if (_Capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return _Capabilities.currentExtent;
    }
    else {
        int width, height;
        glfwGetFramebufferSize(context->GetWindow().window, &width, &height);

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, _Capabilities.minImageExtent.width, _Capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, _Capabilities.minImageExtent.height, _Capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

SwapChainSupportDetails Swapchain::QuerySwapChainSupport()
{
    VulkanContext* context = reinterpret_cast<VulkanContext*>(Renderer::context);

    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(context->GetPhysicalDevice(), context->GetSurface(), &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(context->GetPhysicalDevice(), context->GetSurface(), &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(context->GetPhysicalDevice(), context->GetSurface(), &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(context->GetPhysicalDevice(), context->GetSurface(), &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(context->GetPhysicalDevice(), context->GetSurface(), &presentModeCount, details.presentModes.data());
    }

    return details;
}

void Swapchain::CreateSwapchain()
{
    VulkanContext* context = reinterpret_cast<VulkanContext*>(Renderer::context);

    SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport();

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = context->GetSurface();

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = PhysicalDevice::FindQueueFamilies(context->GetPhysicalDevice(), context->GetSurface());
    uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(context->GetLogicalDevice(), &createInfo, nullptr, &context->GetSwapchain()) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(context->GetLogicalDevice(), context->GetSwapchain(), &imageCount, nullptr);
    context->GetSwapchainImages().resize(imageCount);
    vkGetSwapchainImagesKHR(context->GetLogicalDevice(), context->GetSwapchain(), &imageCount, context->GetSwapchainImages().data());

    context->GetSwapchainImageFormat() = surfaceFormat.format;
    context->GetSwapchainExtent() = extent;
}

void Swapchain::CreateSwapchainImageViews()
{
    VulkanContext* context = reinterpret_cast<VulkanContext*>(Renderer::context);

    context->GetSwapchainImageViews().resize(context->GetSwapchainImages().size());

    for (size_t i = 0; i < context->GetSwapchainImages().size(); i++)
        context->GetSwapchainImageViews()[i] = VulkanImages::CreateImageView(context->GetLogicalDevice(), context->GetSwapchainImages()[i], context->GetSwapchainImageFormat());
}

void Swapchain::CreateSwapchainFramebuffers()
{
    VulkanContext* context = reinterpret_cast<VulkanContext*>(Renderer::context);

    Framebuffers::CreateFramebuffers(context->GetLogicalDevice(), context->GetSwapchainFramebuffers(), context->GetSwapchainImageViews(), context->GetSwapchainImageViews().size(), context->GetRenderPass(), context->GetSwapchainExtent());
}

void Swapchain::RecreateSwapchain()
{
    VulkanContext* context = reinterpret_cast<VulkanContext*>(Renderer::context);

    int width = 0, height = 0;
    glfwGetFramebufferSize(context->GetWindow().window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(context->GetWindow().window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(context->GetLogicalDevice());

    DestroySwapchain();

    CreateSwapchain();
    CreateSwapchainImageViews();
    CreateSwapchainFramebuffers();
}

void Swapchain::DestroySwapchain()
{
    VulkanContext* context = reinterpret_cast<VulkanContext*>(Renderer::context);

    Framebuffers::DestroyFramebuffers(context->GetLogicalDevice(), context->GetSwapchainFramebuffers());

    for (auto imageView : context->GetSwapchainImageViews()) {
        vkDestroyImageView(context->GetLogicalDevice(), imageView, nullptr);
    }

    vkDestroySwapchainKHR(context->GetLogicalDevice(), context->GetSwapchain(), nullptr);
}