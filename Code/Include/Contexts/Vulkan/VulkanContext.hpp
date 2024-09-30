#pragma once

#include <IRendererContext.hpp>
#include <vulkan/vulkan.h>
#include <memory>

class VulkanContext : public IRendererContext
{
private:

public:

	VulkanContext();
	~VulkanContext();

	// Initializes the Vulkan API context
	void Init() override;

	// Destroys the Vulkan API context (e.g. cleaning, destroying allocated stuff)
	void Destroy() override;
};