#include "VulkanContext.hpp"
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

VulkanContext::VulkanContext()
{
    Create();
}

VulkanContext::VulkanContext(const int& _Width, const int& _Height)
{
    Create(_Width, _Height);
}

VulkanContext::~VulkanContext()
{
	Destroy();
}

void VulkanContext::Create(const std::optional<const int>& _Width, const std::optional<const int>& _Height)
{
    if (m_Window) {
        delete m_Window;
    }
	m_Window = new Window(_Width.value_or(900), _Height.value_or(700));
}

void VulkanContext::Init()
{
    VulkanInstance::Create(m_Instance);
    ValidationLayers::SetupDebugMessenger(m_Instance, m_DebugMessenger);
    VulkanSurface::CreateSurface(m_Instance, m_Window->window, m_Surface);
    PhysicalDevice::PickPhysicalDevice(m_Instance, m_PhysicalDevice, m_Surface);
    LogicalDevice::CreateLogicalDevice(m_PhysicalDevice, m_Device, m_GraphicsQueue, m_PresentQueue, m_Surface);

    Swapchain::CreateSwapchain();
    Swapchain::CreateSwapchainImageViews();

    VulkanPipeline::CreateRenderPass(m_Device, m_SwapchainImageFormat, m_RenderPass);
    VulkanPipeline::CreateGraphicsPipeline(m_Device, "Assets/Shaders/vert.spv", "Assets/Shaders/frag.spv", m_RenderPass, m_PipelineLayout, m_GraphicsPipeline);

    Swapchain::CreateSwapchainFramebuffers();

    CommandPool::CreateCommandPool(m_PhysicalDevice, m_Surface, m_Device, m_CommandPool);

    CommandBuffer::CreateCommandBuffers(m_Device, m_CommandPool, m_DrawCommandBuffers, MAX_FRAMES_IN_FLIGHT);

    VulkanSemaphore::CreateSemaphores(m_Device, m_ImageAvailableSemaphores, MAX_FRAMES_IN_FLIGHT);
    VulkanSemaphore::CreateSemaphores(m_Device, m_RenderFinishedSemaphores, MAX_FRAMES_IN_FLIGHT);
    VulkanFence::CreateFences(m_Device, m_InFlightFences, MAX_FRAMES_IN_FLIGHT);
}

void VulkanContext::Update()
{
    while (!glfwWindowShouldClose(m_Window->window)) {
        glfwPollEvents();

        Synchronisation::DrawFrame();
    }
}

void VulkanContext::Destroy()
{
    vkDeviceWaitIdle(m_Device);
    
    VulkanSemaphore::DestroySemaphores(m_Device, m_ImageAvailableSemaphores);
    VulkanSemaphore::DestroySemaphores(m_Device, m_RenderFinishedSemaphores);
    VulkanFence::DestroyFences(m_Device, m_InFlightFences);

    CommandPool::DestroyCommandPool(m_Device, m_CommandPool);

    Swapchain::DestroySwapchain();

    VulkanPipeline::DestroyPipeline(m_Device, m_RenderPass, m_PipelineLayout, m_GraphicsPipeline);

    LogicalDevice::DestroyDevice(m_Device);

    if (enableValidationLayers)
        ValidationLayers::DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, VK_NULL_HANDLE);

    VulkanSurface::DestroySurface(m_Instance, m_Surface);

    VulkanInstance::Destroy(m_Instance);
    m_Window->Destroy();
}