#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>

class VulkanShader
{
private:

public:

	static std::vector<char> ReadFile(const std::string& filename);
	static VkShaderModule CreateShaderModule(VkDevice& _LogicalDevice, const std::vector<char>& _Code);
};