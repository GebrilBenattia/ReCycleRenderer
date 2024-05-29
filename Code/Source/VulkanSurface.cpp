#include "VulkanSurface.hpp"
#include <stdexcept>

void VulkanSurface::CreateSurface(VkInstance& _Instance, GLFWwindow* _Window, VkSurfaceKHR& _Surface)
{
	if (glfwCreateWindowSurface(_Instance, _Window, nullptr, &_Surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

void VulkanSurface::DestroySurface(VkInstance& _Instance, VkSurfaceKHR& _Surface)
{
	vkDestroySurfaceKHR(_Instance, _Surface, nullptr);
}
