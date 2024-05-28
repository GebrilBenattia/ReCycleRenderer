#pragma once

#include <vulkan/vulkan.h>

namespace Helper
{
	VkApplicationInfo ApplicationInfo(const char* _ApplicationName, const uint32_t _ApplicationVersion, const char* _EngineName, const uint32_t _EngineVersion, const uint32_t _APIVersion)
	{
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = _ApplicationName;
        appInfo.applicationVersion = _ApplicationVersion;
        appInfo.pEngineName = _EngineName;
        appInfo.engineVersion = _EngineVersion;
        appInfo.apiVersion = _APIVersion;

        return appInfo;
	}

    VkInstanceCreateInfo InstanceInfo(const VkApplicationInfo& _AppInfo)
    {
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &_AppInfo;
        createInfo.enabledLayerCount = 0;

        return createInfo;
    }
};