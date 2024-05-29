#include "VulkanFence.hpp"
#include <stdexcept>

void VulkanFence::CreateFence(VkDevice& _LogicalDevice, VkFence& _Fence)
{
	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	if (vkCreateFence(_LogicalDevice, &fenceInfo, nullptr, &_Fence) != VK_SUCCESS) {
		throw std::runtime_error("failed to create Fence objects for a frame!");
	}
}

void VulkanFence::DestroyFence(VkDevice& _LogicalDevice, VkFence& _Fence)
{
	vkDestroyFence(_LogicalDevice, _Fence, nullptr);
}