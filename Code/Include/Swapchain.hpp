#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

struct SwapChainSupportDetails 
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Swapchain
{
private:

    static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _AvailablePresentModes);
    static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& _Capabilities, GLFWwindow* _Window);
    static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice& _PhysicalDevice, VkSurfaceKHR& _Surface);

public:

    static void CreateSwapchain(VkPhysicalDevice& _PhysicalDevice, VkDevice& _LogicalDevice, VkSurfaceKHR _Surface, GLFWwindow* _Window, VkSwapchainKHR& _Swapchain, std::vector<VkImage>& _SwapchainImages, VkFormat& _SwapchainImageFormat, VkExtent2D& _SwapchainExtent);
    static void CreateSwapchainImageViews(VkDevice& _LogicalDevice, std::vector<VkImage>& _SwapchainImages, VkFormat& _SwapchainImageFormat, std::vector<VkImageView>& _SwapchainImageViews);
    static void DestroySwapchain(VkDevice& _LogicalDevice, VkSwapchainKHR& _Swapchain, std::vector<VkImageView>& _SwapchainImageViews);
};