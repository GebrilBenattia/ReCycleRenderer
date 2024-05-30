#pragma once

#include <vulkan/vulkan.h>
#include <Window.hpp>
#include <vector>

#define MAX_FRAMES_IN_FLIGHT 2

class Renderer
{
private:

	Window* window = nullptr;
	VkInstance instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device = VK_NULL_HANDLE;
	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentQueue = VK_NULL_HANDLE;

	VkSwapchainKHR swapchain = VK_NULL_HANDLE;
	std::vector<VkImage> swapchainImages;
	VkFormat swapchainImageFormat;
	VkExtent2D swapchainExtent;
	std::vector<VkImageView> swapchainImageViews;

	VkRenderPass renderPass = VK_NULL_HANDLE;
	VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
	VkPipeline graphicsPipeline = VK_NULL_HANDLE;

	std::vector<VkFramebuffer> swapchainFramebuffers;

	VkCommandPool commandPool = VK_NULL_HANDLE;

	std::vector<VkCommandBuffer> drawCommandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores ;
	std::vector<VkFence> inFlightFences;
	uint32_t currentFrame = 0;


public:

	void Init();
	void InitVulkan();

	void Update();
	
    void Cleanup();
};