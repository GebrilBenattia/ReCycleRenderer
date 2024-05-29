#pragma once

#include <vulkan/vulkan.h>

class VulkanFence
{
private:

public:

	static void CreateFence(VkDevice& _LogicalDevice, VkFence& _Fence);
	static void DestroyFence(VkDevice& _LogicalDevice, VkFence& _Fence);
};