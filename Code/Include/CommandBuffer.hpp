#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class CommandBuffer
{
private:

public:

	static void CreateCommandBuffer(VkDevice& _LogicalDevice, VkCommandPool& _CmdPool, VkCommandBuffer& _CmdBuffer);
	static void RecordCommandBuffer(VkCommandBuffer& _CmdBuffer, uint32_t _ImageIndex, VkRenderPass& _RenderPass, std::vector<VkFramebuffer>& _Framebuffers, VkExtent2D& _Extent, VkPipeline& _Pipeline);
};

