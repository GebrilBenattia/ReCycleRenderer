#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class VulkanSemaphore
{
private:

public:

	static void CreateSemaphore(VkDevice& _LogicalDevice, VkSemaphore& _Semaphore);
	static void CreateSemaphores(VkDevice& _LogicalDevice, std::vector<VkSemaphore>& _Semaphore, int _FramesInFlightCount);
	static void DestroySemaphore(VkDevice& _LogicalDevice, VkSemaphore& _Semaphore);
	static void DestroySemaphores(VkDevice& _LogicalDevice, std::vector<VkSemaphore>& _Semaphores);
};