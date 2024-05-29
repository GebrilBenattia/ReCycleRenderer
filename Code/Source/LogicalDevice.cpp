#include "LogicalDevice.hpp"
#include <ValidationLayers.hpp>
#include <PhysicalDevice.hpp>
#include <set>

void LogicalDevice::CreateLogicalDevice(VkPhysicalDevice& _PhysicalDevice, VkDevice& _LogicalDevice, VkQueue& _GraphicsQueue, VkQueue& _PresentQueue, VkSurfaceKHR& _Surface)
{
    QueueFamilyIndices indices = PhysicalDevice::FindQueueFamilies(_PhysicalDevice, _Surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(PhysicalDevice::deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = PhysicalDevice::deviceExtensions.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers::validationLayers.size());
        createInfo.ppEnabledLayerNames = ValidationLayers::validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(_PhysicalDevice, &createInfo, nullptr, &_LogicalDevice) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(_LogicalDevice, indices.graphicsFamily.value(), 0, &_GraphicsQueue);
    vkGetDeviceQueue(_LogicalDevice, indices.presentFamily.value(), 0, &_PresentQueue);
}

void LogicalDevice::DestroyDevice(VkDevice& _Device)
{
	vkDestroyDevice(_Device, nullptr);
}