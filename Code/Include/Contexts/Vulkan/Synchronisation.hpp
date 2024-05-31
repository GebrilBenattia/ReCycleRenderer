#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <Window.hpp>

class Synchronisation
{
private:

public:

	static void DrawFrame(VkPhysicalDevice& _PhysicalDevice, VkDevice& _LogicalDevice, uint32_t& _CurrentFrame, int _MaxFramesInFlight, VkSwapchainKHR& _Swapchain, std::vector<VkCommandBuffer>& _CmdBuffers, std::vector<VkFence>& _Fences, std::vector<VkSemaphore>& _ImageAvailableSemaphores, std::vector<VkSemaphore>& _RenderFinishedSemaphores, VkQueue& _GraphicsQueue, VkQueue& _PresentQueue, VkRenderPass& _RenderPass, std::vector<VkFramebuffer>& _Framebuffers, VkExtent2D& _Extent, VkPipeline& _Pipeline, VkSurfaceKHR& _Surface, std::vector<VkImage>& _SwapchainImages, std::vector<VkImageView>& _SwapchainImageViews, VkFormat& _SwapchainImageFormat, Window& _Window);
};