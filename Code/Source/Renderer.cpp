#include "Renderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#include <VulkanInstance.hpp>
#include <ValidationLayers.hpp>
#include <VulkanSurface.hpp>
#include <PhysicalDevice.hpp>
#include <LogicalDevice.hpp>
#include <Swapchain.hpp>

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
}

void Renderer::Update()
{
    while (!glfwWindowShouldClose(window->window)) {
        glfwPollEvents();
        
    }
}

void Renderer::Cleanup()
{
    Swapchain::DestroySwapchain(device, swapchain, swapchainImageViews);

    LogicalDevice::DestroyDevice(device);

    if (enableValidationLayers)
        ValidationLayers::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, VK_NULL_HANDLE);

    VulkanSurface::DestroySurface(instance, surface);

    VulkanInstance::Destroy(instance);
    window->Destroy();
}