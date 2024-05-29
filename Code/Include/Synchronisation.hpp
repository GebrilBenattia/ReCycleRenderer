#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class Synchronisation
{
private:

public:

	static void DrawFrame(VkDevice& _LogicalDevice, VkSwapchainKHR& _Swapchain, VkCommandBuffer& _CmdBuffer, VkFence& _Fence, VkSemaphore& _ImageAvailableSemaphore, VkSemaphore& _RenderFinishedSemaphore, VkQueue& _GraphicsQueue, VkQueue& _PresentQueue, VkRenderPass& _RenderPass, std::vector<VkFramebuffer>& _Framebuffers, VkExtent2D& _Extent, VkPipeline& _Pipeline);
};