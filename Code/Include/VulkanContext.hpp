#pragma once

#include <RendererContext.hpp>
#include <vulkan/vulkan.h>
#include <vector>

#define MAX_FRAMES_IN_FLIGHT 2

class VulkanContext : public RendererContext
{
private:

	static Window* m_Window;
	static VkInstance m_Instance;
	static VkDebugUtilsMessengerEXT m_DebugMessenger;
	static VkSurfaceKHR m_Surface;
	static VkPhysicalDevice m_PhysicalDevice;
	static VkDevice m_Device;
	static VkQueue m_GraphicsQueue;
	static VkQueue m_PresentQueue;

	static VkSwapchainKHR m_Swapchain; //TODO KEEP OLD SWAPCHAIN FOR RECREATION OPTIMIZATION, SEE IF THAT'S THE SAME FOR FRAMEBUFFERS
	static std::vector<VkImage> m_SwapchainImages;
	static VkFormat m_SwapchainImageFormat;
	static VkExtent2D m_SwapchainExtent;
	static std::vector<VkImageView> m_SwapchainImageViews;

	static VkRenderPass m_RenderPass;
	static VkPipelineLayout m_PipelineLayout;
	static VkPipeline m_GraphicsPipeline;

	static std::vector<VkFramebuffer> m_SwapchainFramebuffers;

	static VkCommandPool m_CommandPool;

	static std::vector<VkCommandBuffer> m_DrawCommandBuffers;

	static std::vector<VkSemaphore> m_ImageAvailableSemaphores;
	static std::vector<VkSemaphore> m_RenderFinishedSemaphores;
	static std::vector<VkFence> m_InFlightFences;
	static uint32_t m_CurrentFrame;

public:

	VulkanContext();
	VulkanContext(const int _Width, const int _Height);
	~VulkanContext();

	void Create(std::optional<const int> _Width = std::nullopt, std::optional<const int> _Height = std::nullopt) override;
	void InitVulkan();
	void Update() override;
	void Destroy() override;

	static VkInstance& GetInstance() { return m_Instance; };
	static VkDebugUtilsMessengerEXT& GetDebugMessenger() { return m_DebugMessenger; };
	static VkSurfaceKHR& GetSurface() { return m_Surface; };
	static VkPhysicalDevice& GetPhysicalDevice() { return m_PhysicalDevice; };
	static VkDevice& GetLogicalDevice() { return m_Device; };
	static VkQueue& GetGraphicsQueue() { return m_GraphicsQueue; };
	static VkQueue& GetPresentQueue() { return m_PresentQueue; };

	static VkSwapchainKHR& GetSwapchain() { return m_Swapchain; };
	static std::vector<VkImage>& GetSwapchainImages() { return m_SwapchainImages; };
	static VkFormat GetSwapchainImageFormat() { return m_SwapchainImageFormat; };
	static VkExtent2D GetSwapchainExtent() { return m_SwapchainExtent; };
	static std::vector<VkImageView>& GetSwapchainImageViews() { return m_SwapchainImageViews; };
	static std::vector<VkFramebuffer>& GetSwapchainFramebuffers() { return m_SwapchainFramebuffers; };

	static VkRenderPass& GetRenderPass() { return m_RenderPass; };
	static VkPipelineLayout& GetPipelineLayout() { return m_PipelineLayout; };
	static VkPipeline& GetGraphicsPipeline() { return m_GraphicsPipeline; };

	static VkCommandPool& GetCommandPool() { return m_CommandPool; };

	static std::vector<VkCommandBuffer>& GetDrawCommandBuffers() { return m_DrawCommandBuffers; };

	static std::vector<VkSemaphore>& GetImageAvailableSemaphores() { return m_ImageAvailableSemaphores; };
	static std::vector<VkSemaphore>& GetRenderFinishedSemaphores() { return m_RenderFinishedSemaphores; };
	static std::vector<VkFence>& GetInFlightFences() { return m_InFlightFences; };
	static uint32_t& GetCurrentFrame() { return m_CurrentFrame; };
};