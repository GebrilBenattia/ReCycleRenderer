#pragma once

#include <vulkan/vulkan.h>
#include <iostream>
#include <optional>
#include <vector>

struct QueueFamilyIndices 
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool IsComplete() 
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class PhysicalDevice
{
private:

    static bool IsDeviceSuitable(VkPhysicalDevice _PhysicalDevice, VkSurfaceKHR& _Surface);
    static bool CheckDeviceExtensionSupport(VkPhysicalDevice _PhysicalDevice);

public:

    static const std::vector<const char*> deviceExtensions;

    static void PickPhysicalDevice(VkInstance& _Instance, VkPhysicalDevice& _PhysicalDevice, VkSurfaceKHR& _Surface);
    static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice _PhysicalDevice, VkSurfaceKHR& _Surface);
};