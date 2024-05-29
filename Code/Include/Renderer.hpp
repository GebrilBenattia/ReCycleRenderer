#pragma once

#include <vulkan/vulkan.h>
#include <Window.hpp>
#include <vector>

class Renderer
{
private:

	Window* window;
	VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapchain;
	std::vector<VkImage> swapchainImages;
	VkFormat swapchainImageFormat;
	VkExtent2D swapchainExtent;
	std::vector<VkImageView> swapchainImageViews;

public:

	void Init();
	void InitVulkan();

	void Update();
	
    void Cleanup();
};

