#include "PhysicalDevice.hpp"
#include <vector>
#include <set>

const std::vector<const char*> PhysicalDevice::deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

void PhysicalDevice::PickPhysicalDevice(VkInstance& _Instance, VkPhysicalDevice& _PhysicalDevice, VkSurfaceKHR& _Surface) 
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(_Instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(_Instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (IsDeviceSuitable(device, _Surface)) {
            _PhysicalDevice = device;
            break;
        }
    }

    if (_PhysicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice _PhysicalDevice, VkSurfaceKHR& _Surface)
{
    QueueFamilyIndices indices = FindQueueFamilies(_PhysicalDevice, _Surface);

    bool extensionsSupported = CheckDeviceExtensionSupport(_PhysicalDevice);

    return indices.IsComplete() && extensionsSupported;
}

QueueFamilyIndices PhysicalDevice::FindQueueFamilies(VkPhysicalDevice _PhysicalDevice, VkSurfaceKHR& _Surface)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(_PhysicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(_PhysicalDevice, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(_PhysicalDevice, i, _Surface, &presentSupport);

        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.IsComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

bool PhysicalDevice::CheckDeviceExtensionSupport(VkPhysicalDevice _PhysicalDevice)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(_PhysicalDevice, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(_PhysicalDevice, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}