#pragma once

#include <vulkan/vulkan.h>

class VulkanPipeline
{
private:

public:

	static void CreateRenderPass(VkDevice& _LogicalDevice, VkFormat& _ImageFormat, VkRenderPass& _RenderPass);
	static void CreateGraphicsPipeline(VkDevice& _LogicalDevice, const char* _Vert, const char* _Frag, VkRenderPass& _RenderPass, VkPipelineLayout& _PipelineLayout, VkPipeline& _Pipeline);
	static void DestroyPipeline(VkDevice& _LogicalDevice, VkRenderPass& _RenderPass, VkPipelineLayout& _PipelineLayout, VkPipeline& _Pipeline);
};

