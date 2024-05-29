#pragma once

#include <vulkan/vulkan.h>

class LogicalDevice
{
private:

public:

	static void CreateLogicalDevice(VkPhysicalDevice& _PhysicalDevice, VkDevice& _LogicalDevice, VkQueue& _GraphicsQueue, VkQueue& _PresentQueue, VkSurfaceKHR& _Surface);
	static void DestroyDevice(VkDevice& _Device);
};