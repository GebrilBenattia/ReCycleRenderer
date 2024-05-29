#include "Synchronisation.hpp"
#include <stdexcept>
#include <CommandBuffer.hpp>

void Synchronisation::DrawFrame(VkDevice& _LogicalDevice, VkSwapchainKHR& _Swapchain, VkCommandBuffer& _CmdBuffer, VkFence& _Fence, VkSemaphore& _ImageAvailableSemaphore, VkSemaphore& _RenderFinishedSemaphore, VkQueue& _GraphicsQueue, VkQueue& _PresentQueue, VkRenderPass& _RenderPass, std::vector<VkFramebuffer>& _Framebuffers, VkExtent2D& _Extent, VkPipeline& _Pipeline)
{
    vkWaitForFences(_LogicalDevice, 1, &_Fence, VK_TRUE, UINT64_MAX);
    vkResetFences(_LogicalDevice, 1, &_Fence);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(_LogicalDevice, _Swapchain, UINT64_MAX, _ImageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    vkResetCommandBuffer(_CmdBuffer, /*VkCommandBufferResetFlagBits*/ 0);
    CommandBuffer::RecordCommandBuffer(_CmdBuffer, imageIndex, _RenderPass, _Framebuffers, _Extent, _Pipeline);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { _ImageAvailableSemaphore };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &_CmdBuffer;

    VkSemaphore signalSemaphores[] = { _RenderFinishedSemaphore };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(_GraphicsQueue, 1, &submitInfo, _Fence) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { _Swapchain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(_PresentQueue, &presentInfo);
}