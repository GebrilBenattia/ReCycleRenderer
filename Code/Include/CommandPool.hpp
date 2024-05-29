#pragma once

#include <vulkan/vulkan.h>

class CommandPool
{
private:

public:

	static void CreateCommandPool(VkPhysicalDevice& _PhysicalDevice, VkSurfaceKHR& _Surface, VkDevice& _LogicalDevice, VkCommandPool& _CmdPool);
	static void DestroyCommandPool(VkDevice& _LogicalDevice, VkCommandPool& _CmdPool);
};