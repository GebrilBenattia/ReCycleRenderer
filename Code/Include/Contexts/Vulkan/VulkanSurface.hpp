#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class VulkanSurface
{
private:

public:

	static void CreateSurface(VkInstance& _Instance, GLFWwindow* _Window, VkSurfaceKHR& _Surface);
	static void DestroySurface(VkInstance& _Instance, VkSurfaceKHR& _Surface);
};