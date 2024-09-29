#include <Synchronisation.hpp>
#include <stdexcept>
#include <CommandBuffer.hpp>
#include <Swapchain.hpp>
#include <Renderer.hpp>
#include <VulkanContext.hpp>

void Synchronisation::DrawFrame()
{
    VulkanContext* context = reinterpret_cast<VulkanContext*>(Renderer::context);

    vkWaitForFences(context->GetLogicalDevice(), 1, &context->GetInFlightFences()[context->GetCurrentFrame()], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(context->GetLogicalDevice(), context->GetSwapchain(), UINT64_MAX, context->GetImageAvailableSemaphores()[context->GetCurrentFrame()], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        Swapchain::RecreateSwapchain();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    vkResetFences(context->GetLogicalDevice(), 1, &context->GetInFlightFences()[context->GetCurrentFrame()]);

    vkResetCommandBuffer(context->GetDrawCommandBuffers()[context->GetCurrentFrame()], /*VkCommandBufferResetFlagBits*/ 0);
    CommandBuffer::RecordCommandBuffer(context->GetDrawCommandBuffers()[context->GetCurrentFrame()], imageIndex, context->GetRenderPass(), context->GetSwapchainFramebuffers(), context->GetSwapchainExtent(), context->GetGraphicsPipeline());

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { context->GetImageAvailableSemaphores()[context->GetCurrentFrame()] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &context->GetDrawCommandBuffers()[context->GetCurrentFrame()];

    VkSemaphore signalSemaphores[] = { context->GetRenderFinishedSemaphores()[context->GetCurrentFrame()] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(context->GetGraphicsQueue(), 1, &submitInfo, context->GetInFlightFences()[context->GetCurrentFrame()]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { context->GetSwapchain() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(context->GetPresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || context->GetWindow().framebufferResized) {
        context->GetWindow().framebufferResized = false;
        Swapchain::RecreateSwapchain();
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    context->GetCurrentFrame() = (context->GetCurrentFrame() + 1) % context->GetMaxFramesInFlight();
}