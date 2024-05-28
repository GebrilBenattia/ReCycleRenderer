#pragma once

#include <vulkan/vulkan.h>
#include <Window.hpp>
#include <vector>

class Renderer
{
private:

	VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice;

public:

	Window* window;

	void Init();
	void InitVulkan();

	void Update();
	
    void Cleanup();
};

