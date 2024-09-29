#pragma once

#include <RendererContext.hpp>
#include <vulkan/vulkan.h>

class VulkanContext : public RendererContext
{
private:

	Window* m_Window = nullptr;

public:

	VulkanContext();
	VulkanContext(const int& _Width, const int& _Height);
	~VulkanContext();

	void Create(const std::optional<const int>& _Width = std::nullopt, const std::optional<const int>& _Height = std::nullopt) override;
	void Init() override;
	void Update() override;
	void Destroy() override;
};