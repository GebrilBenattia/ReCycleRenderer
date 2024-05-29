#pragma once

#include <vulkan/vulkan.h>

class VulkanSemaphore
{
private:

public:

	void CreateSemaphore(VkDevice& _LogicalDevice, VkSemaphore& _Semaphore);
	void DestroySemaphore(VkDevice& _LogicalDevice, VkSemaphore& _Semaphore);
};