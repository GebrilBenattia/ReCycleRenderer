#include "Renderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#include <VulkanInstance.hpp>
#include <ValidationLayers.hpp>
#include <VulkanSurface.hpp>
#include <PhysicalDevice.hpp>
#include <LogicalDevice.hpp>
#include <Swapchain.hpp>
#include <VulkanPipeline.hpp>
#include <Framebuffers.hpp>
#include <CommandPool.hpp>
#include <CommandBuffer.hpp>
#include <VulkanSemaphore.hpp>
#include <VulkanFence.hpp>
#include <Synchronisation.hpp>

void Renderer::Init()
{
    window = new Window();
    InitVulkan();
}

void Renderer::InitVulkan()
{
    VulkanInstance::Create(instance);
    ValidationLayers::SetupDebugMessenger(instance, debugMessenger);
    VulkanSurface::CreateSurface(instance, window->window, surface);
    PhysicalDevice::PickPhysicalDevice(instance, physicalDevice, surface);
    LogicalDevice::CreateLogicalDevice(physicalDevice, device, graphicsQueue, presentQueue, surface);
    
    Swapchain::CreateSwapchain(physicalDevice, device, surface, window->window, swapchain, swapchainImages, swapchainImageFormat, swapchainExtent);
    Swapchain::CreateSwapchainImageViews(device, swapchainImages, swapchainImageFormat, swapchainImageViews);
    
    VulkanPipeline::CreateRenderPass(device, swapchainImageFormat, renderPass);
    VulkanPipeline::CreateGraphicsPipeline(device, "Assets/Shaders/vert.spv", "Assets/Shaders/frag.spv", renderPass, pipelineLayout, graphicsPipeline);

    Swapchain::CreateSwapchainFramebuffers(device, swapchainFramebuffers, swapchainImageViews, swapchainImageViews.size(), renderPass, swapchainExtent);

    CommandPool::CreateCommandPool(physicalDevice, surface, device, commandPool);

    CommandBuffer::CreateCommandBuffers(device, commandPool, drawCommandBuffers, MAX_FRAMES_IN_FLIGHT);

    VulkanSemaphore::CreateSemaphores(device, imageAvailableSemaphores, MAX_FRAMES_IN_FLIGHT);
    VulkanSemaphore::CreateSemaphores(device, renderFinishedSemaphores, MAX_FRAMES_IN_FLIGHT);
    VulkanFence::CreateFences(device, inFlightFences, MAX_FRAMES_IN_FLIGHT);
}

void Renderer::Update()
{
    while (!glfwWindowShouldClose(window->window)) {
        glfwPollEvents();
        
        Synchronisation::DrawFrame(device, currentFrame, MAX_FRAMES_IN_FLIGHT, swapchain, drawCommandBuffers, inFlightFences, imageAvailableSemaphores, renderFinishedSemaphores, graphicsQueue, presentQueue, renderPass, swapchainFramebuffers, swapchainExtent, graphicsPipeline);
    }

    vkDeviceWaitIdle(device);
}

void Renderer::Cleanup()
{
    VulkanSemaphore::DestroySemaphores(device, imageAvailableSemaphores);
    VulkanSemaphore::DestroySemaphores(device, renderFinishedSemaphores);
    VulkanFence::DestroyFences(device, inFlightFences);

    CommandPool::DestroyCommandPool(device, commandPool);

    Swapchain::DestroySwapchain(device, swapchain, swapchainImageViews, swapchainFramebuffers);

    VulkanPipeline::DestroyPipeline(device, renderPass, pipelineLayout, graphicsPipeline);

    LogicalDevice::DestroyDevice(device);

    if (enableValidationLayers)
        ValidationLayers::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, VK_NULL_HANDLE);

    VulkanSurface::DestroySurface(instance, surface);

    VulkanInstance::Destroy(instance);
    window->Destroy();
}