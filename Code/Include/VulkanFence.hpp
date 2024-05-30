#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class VulkanFence
{
private:

public:

	static void CreateFence(VkDevice& _LogicalDevice, VkFence& _Fence);
	static void CreateFences(VkDevice& _LogicalDevice, std::vector<VkFence>& _Fences, int _FramesInFlightCount);
	static void DestroyFence(VkDevice& _LogicalDevice, VkFence& _Fence);
	static void DestroyFences(VkDevice& _LogicalDevice, std::vector<VkFence>& _Fences);
};