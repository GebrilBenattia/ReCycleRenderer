#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class Framebuffers
{
private:

public:

	static void CreateFramebuffers(VkDevice& _LogicalDevice, std::vector<VkFramebuffer> _Framebuffers, std::vector<std::vector<VkImageView>>& _Attachements, size_t _ViewCount, VkRenderPass& _RenderPass, VkExtent2D _Extent);
	static void DestroyFramebuffers(VkDevice& _LogicalDevice, std::vector<VkFramebuffer>& _Framebuffers);
};