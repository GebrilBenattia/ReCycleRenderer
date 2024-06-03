#include "VulkanInstance.hpp"
#include <Helper.hpp>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <ValidationLayers.hpp>

void VulkanInstance::Create(VkInstance& _Instance)
{
    if (enableValidationLayers && !ValidationLayers::CheckValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo = Helper::ApplicationInfo("ReCycleRenderer", VK_MAKE_VERSION(1, 0, 0), "ReCycle", VK_MAKE_VERSION(1, 0, 0), VK_API_VERSION_1_0);

    VkInstanceCreateInfo createInfo = Helper::InstanceInfo(appInfo);

    auto extensions = ValidationLayers::GetRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers::validationLayers.size());
        createInfo.ppEnabledLayerNames = ValidationLayers::validationLayers.data();

        ValidationLayers::PopulateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &_Instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void VulkanInstance::Destroy(const VkInstance& _Instance)
{
    vkDestroyInstance(_Instance, nullptr);
}