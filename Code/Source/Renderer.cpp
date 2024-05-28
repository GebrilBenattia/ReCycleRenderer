#include "Renderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#include <VulkanInstance.hpp>
#include <ValidationLayers.hpp>

void Renderer::Init()
{
    window = new Window();
    InitVulkan();
}

void Renderer::InitVulkan()
{
    VulkanInstance::Create(instance);
    ValidationLayers::SetupDebugMessenger(instance, debugMessenger);
}

void Renderer::Update()
{
    while (!glfwWindowShouldClose(window->window)) {
        glfwPollEvents();

    }
}

void Renderer::Cleanup()
{
    if (enableValidationLayers)
        ValidationLayers::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, VK_NULL_HANDLE);

    VulkanInstance::Destroy(instance);
    window->Destroy();
}