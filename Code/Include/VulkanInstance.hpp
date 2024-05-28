#pragma once

#include <vulkan/vulkan.h>

class VulkanInstance
{
public:

	static void Create(VkInstance& _Instance);
	static void Destroy(const VkInstance& _Instance);
};

