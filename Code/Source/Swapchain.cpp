#include "Swapchain.hpp"
#include <stdexcept>
#include <algorithm>
#include <PhysicalDevice.hpp>
#include <VulkanImages.hpp>
#include <Framebuffers.hpp>

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

VkExtent2D Swapchain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& _Capabilities, GLFWwindow* _Window)
{
    if (_Capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return _Capabilities.currentExtent;
    }
    else {
        int width, height;
        glfwGetFramebufferSize(_Window, &width, &height);

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, _Capabilities.minImageExtent.width, _Capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, _Capabilities.minImageExtent.height, _Capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

SwapChainSupportDetails Swapchain::QuerySwapChainSupport(VkPhysicalDevice& _PhysicalDevice, VkSurfaceKHR& _Surface)
{
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_PhysicalDevice, _Surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(_PhysicalDevice, _Surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(_PhysicalDevice, _Surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice, _Surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(_PhysicalDevice, _Surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

void Swapchain::CreateSwapchain(VkPhysicalDevice& _PhysicalDevice, VkDevice& _LogicalDevice, VkSurfaceKHR& _Surface, GLFWwindow* _Window, VkSwapchainKHR& _Swapchain, std::vector<VkImage>& _SwapchainImages, VkFormat& _SwapchainImageFormat, VkExtent2D& _SwapchainExtent)
{
    SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(_PhysicalDevice, _Surface);

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities, _Window);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = _Surface;

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = PhysicalDevice::FindQueueFamilies(_PhysicalDevice, _Surface);
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

    if (vkCreateSwapchainKHR(_LogicalDevice, &createInfo, nullptr, &_Swapchain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(_LogicalDevice, _Swapchain, &imageCount, nullptr);
    _SwapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(_LogicalDevice, _Swapchain, &imageCount, _SwapchainImages.data());

    _SwapchainImageFormat = surfaceFormat.format;
    _SwapchainExtent = extent;
}

void Swapchain::CreateSwapchainImageViews(VkDevice& _LogicalDevice, std::vector<VkImage>& _SwapchainImages, VkFormat& _SwapchainImageFormat, std::vector<VkImageView>& _SwapchainImageViews)
{
    _SwapchainImageViews.resize(_SwapchainImages.size());

    for (size_t i = 0; i < _SwapchainImages.size(); i++)
        _SwapchainImageViews[i] = VulkanImages::CreateImageView(_LogicalDevice, _SwapchainImages[i], _SwapchainImageFormat);
}

void Swapchain::CreateSwapchainFramebuffers(VkDevice& _LogicalDevice, std::vector<VkFramebuffer>& _Framebuffers, std::vector<VkImageView>& _Attachement0, size_t _ViewCount, VkRenderPass& _RenderPass, VkExtent2D _Extent)
{
    Framebuffers::CreateFramebuffers(_LogicalDevice, _Framebuffers, _Attachement0, _ViewCount, _RenderPass, _Extent);
}

void Swapchain::RecreateSwapchain(VkPhysicalDevice& _PhysicalDevice, VkDevice& _LogicalDevice, VkSurfaceKHR& _Surface, GLFWwindow* _Window, VkSwapchainKHR& _Swapchain, std::vector<VkImage>& _SwapchainImages, VkFormat& _SwapchainImageFormat, VkExtent2D& _SwapchainExtent, std::vector<VkImageView>& _SwapchainImageViews, std::vector<VkFramebuffer>& _SwapchainFramebuffers, VkRenderPass& _RenderPass)
{
    int width = 0, height = 0;
    glfwGetFramebufferSize(_Window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(_Window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(_LogicalDevice);

    DestroySwapchain(_LogicalDevice, _Swapchain, _SwapchainImageViews, _SwapchainFramebuffers);

    CreateSwapchain(_PhysicalDevice, _LogicalDevice, _Surface, _Window, _Swapchain, _SwapchainImages, _SwapchainImageFormat, _SwapchainExtent);
    CreateSwapchainImageViews(_LogicalDevice, _SwapchainImages, _SwapchainImageFormat, _SwapchainImageViews);
    CreateSwapchainFramebuffers(_LogicalDevice, _SwapchainFramebuffers, _SwapchainImageViews, _SwapchainImageViews.size(), _RenderPass, _SwapchainExtent);
}

void Swapchain::DestroySwapchain(VkDevice& _LogicalDevice, VkSwapchainKHR& _Swapchain, std::vector<VkImageView>& _SwapchainImageViews, std::vector<VkFramebuffer>& _SwapchainFramebuffers)
{
    Framebuffers::DestroyFramebuffers(_LogicalDevice, _SwapchainFramebuffers);

    for (auto imageView : _SwapchainImageViews) {
        vkDestroyImageView(_LogicalDevice, imageView, nullptr);
    }
    _SwapchainImageViews.clear();

    vkDestroySwapchainKHR(_LogicalDevice, _Swapchain, nullptr);
}