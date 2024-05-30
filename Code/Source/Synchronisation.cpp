#include "Synchronisation.hpp"
#include <stdexcept>
#include <CommandBuffer.hpp>
#include <Swapchain.hpp>

void Synchronisation::DrawFrame(VkPhysicalDevice& _PhysicalDevice, VkDevice& _LogicalDevice, uint32_t& _CurrentFrame, int _MaxFramesInFlight, VkSwapchainKHR& _Swapchain, std::vector<VkCommandBuffer>& _CmdBuffers, std::vector<VkFence>& _Fences, std::vector<VkSemaphore>& _ImageAvailableSemaphores, std::vector<VkSemaphore>& _RenderFinishedSemaphores, VkQueue& _GraphicsQueue, VkQueue& _PresentQueue, VkRenderPass& _RenderPass, std::vector<VkFramebuffer>& _Framebuffers, VkExtent2D& _Extent, VkPipeline& _Pipeline)
{
    vkWaitForFences(_LogicalDevice, 1, &_Fences[_CurrentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(_LogicalDevice, _Swapchain, UINT64_MAX, _ImageAvailableSemaphores[_CurrentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        Swapchain::RecreateSwapchain(_PhysicalDevice, _LogicalDevice, , , _Swapchain, , , _Extent, , _Framebuffers, _RenderPass);
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    vkResetFences(_LogicalDevice, 1, &_Fences[_CurrentFrame]);

    vkResetCommandBuffer(_CmdBuffers[_CurrentFrame], /*VkCommandBufferResetFlagBits*/ 0);
    CommandBuffer::RecordCommandBuffer(_CmdBuffers[_CurrentFrame], imageIndex, _RenderPass, _Framebuffers, _Extent, _Pipeline);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { _ImageAvailableSemaphores[_CurrentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &_CmdBuffers[_CurrentFrame];

    VkSemaphore signalSemaphores[] = { _RenderFinishedSemaphores[_CurrentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(_GraphicsQueue, 1, &submitInfo, _Fences[_CurrentFrame]) != VK_SUCCESS) {
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

    result = vkQueuePresentKHR(_PresentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
        framebufferResized = false;
        //RecreateSwapChain();
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    _CurrentFrame = (_CurrentFrame + 1) % _MaxFramesInFlight;
}