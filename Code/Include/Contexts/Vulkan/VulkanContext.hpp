#pragma once

#include <RendererContext.hpp>
#include <vulkan/vulkan.h>
#include <vector>

#define MAX_FRAMES_IN_FLIGHT 2

class VulkanContext : public RendererContext
{
private:

	Window* m_Window = nullptr;
	VkInstance m_Instance = VK_NULL_HANDLE;
	VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;
	VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	VkDevice m_Device = VK_NULL_HANDLE;
	VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
	VkQueue m_PresentQueue = VK_NULL_HANDLE;

	VkSwapchainKHR m_Swapchain = VK_NULL_HANDLE; //TODO KEEP OLD SWAPCHAIN FOR RECREATION OPTIMIZATION, SEE IF THAT'S THE SAME FOR FRAMEBUFFERS
	std::vector<VkImage> m_SwapchainImages;
	VkFormat m_SwapchainImageFormat;
	VkExtent2D m_SwapchainExtent;
	std::vector<VkImageView> m_SwapchainImageViews;

	VkRenderPass m_RenderPass = VK_NULL_HANDLE;
	VkPipelineLayout m_PipelineLayout = VK_NULL_HANDLE;
	VkPipeline m_GraphicsPipeline = VK_NULL_HANDLE;

	std::vector<VkFramebuffer> m_SwapchainFramebuffers;

	VkCommandPool m_CommandPool = VK_NULL_HANDLE;

	std::vector<VkCommandBuffer> m_DrawCommandBuffers;

	std::vector<VkSemaphore> m_ImageAvailableSemaphores;
	std::vector<VkSemaphore> m_RenderFinishedSemaphores;
	std::vector<VkFence> m_InFlightFences;
	uint32_t m_CurrentFrame = 0;

public:

	VulkanContext();
	VulkanContext(const int _Width, const int _Height);
	~VulkanContext();

	void Create(std::optional<const int> _Width = std::nullopt, std::optional<const int> _Height = std::nullopt);
	void InitVulkan();
	void Update();
	void Destroy();

	VkInstance& GetInstance() { return m_Instance; };
	VkDebugUtilsMessengerEXT& GetDebugMessenger() { return m_DebugMessenger; };
	VkSurfaceKHR& GetSurface() { return m_Surface; };
	VkPhysicalDevice& GetPhysicalDevice() { return m_PhysicalDevice; };
	VkDevice& GetLogicalDevice() { return m_Device; };
	VkQueue& GetGraphicsQueue() { return m_GraphicsQueue; };
	VkQueue& GetPresentQueue() { return m_PresentQueue; };

	VkSwapchainKHR& GetSwapchain() { return m_Swapchain; };
	std::vector<VkImage>& GetSwapchainImages() { return m_SwapchainImages; };
	VkFormat GetSwapchainImageFormat() { return m_SwapchainImageFormat; };
	VkExtent2D GetSwapchainExtent() { return m_SwapchainExtent; };
	std::vector<VkImageView>& GetSwapchainImageViews() { return m_SwapchainImageViews; };
	std::vector<VkFramebuffer>& GetSwapchainFramebuffers() { return m_SwapchainFramebuffers; };

	VkRenderPass& GetRenderPass() { return m_RenderPass; };
	VkPipelineLayout& GetPipelineLayout() { return m_PipelineLayout; };
	VkPipeline& GetGraphicsPipeline() { return m_GraphicsPipeline; };

	VkCommandPool& GetCommandPool() { return m_CommandPool; };

	std::vector<VkCommandBuffer>& GetDrawCommandBuffers() { return m_DrawCommandBuffers; };

	std::vector<VkSemaphore>& GetImageAvailableSemaphores() { return m_ImageAvailableSemaphores; };
	std::vector<VkSemaphore>& GetRenderFinishedSemaphores() { return m_RenderFinishedSemaphores; };
	std::vector<VkFence>& GetInFlightFences() { return m_InFlightFences; };
	uint32_t& GetCurrentFrame() { return m_CurrentFrame; };
};