#include "CommandBuffer.hpp"
#include <stdexcept>

void CommandBuffer::CreateCommandBuffer(VkDevice& _LogicalDevice, VkCommandPool& _CmdPool, VkCommandBuffer& _CmdBuffer)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = _CmdPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(_LogicalDevice, &allocInfo, &_CmdBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void CommandBuffer::CreateCommandBuffers(VkDevice& _LogicalDevice, VkCommandPool& _CmdPool, std::vector<VkCommandBuffer>& _CmdBuffers, int _FramesInFlightCount)
{
    _CmdBuffers.resize(_FramesInFlightCount);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = _CmdPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = static_cast<uint32_t>(_CmdBuffers.size());


    for (size_t i = 0; i < _FramesInFlightCount; i++) {
        if (vkAllocateCommandBuffers(_LogicalDevice, &allocInfo, &_CmdBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }
    }
}

void CommandBuffer::RecordCommandBuffer(VkCommandBuffer& _CmdBuffer, uint32_t _ImageIndex, VkRenderPass& _RenderPass, std::vector<VkFramebuffer>& _Framebuffers, VkExtent2D& _Extent, VkPipeline& _Pipeline)
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(_CmdBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = _RenderPass;
    renderPassInfo.framebuffer = _Framebuffers[_ImageIndex];
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = _Extent;

    VkClearValue clearColor = { {{0.07f, 0.13f, 0.17f, 1.0f}} };
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(_CmdBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(_CmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _Pipeline);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)_Extent.width;
    viewport.height = (float)_Extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(_CmdBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = _Extent;
    vkCmdSetScissor(_CmdBuffer, 0, 1, &scissor);

    //DRAW CALLS
    vkCmdDraw(_CmdBuffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(_CmdBuffer);

    if (vkEndCommandBuffer(_CmdBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}