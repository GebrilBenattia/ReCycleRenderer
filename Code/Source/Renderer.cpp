#include "Renderer.hpp"

#include <OpenGLContext.hpp>
#include <VulkanContext.hpp>
#include <DirectXContext.hpp>

#include <stdexcept>

void Renderer::Init()
{
	switch (activeContext)
	{
	case OPENGL:
		context = new OpenGLContext();
		break;
	case VULKAN:
		context = new VulkanContext();
		break;
	case DIRECTX:
		context = new DirectXContext();
		break;
	default:
		throw std::runtime_error("Select a renderer context");
		break;
	}
}

void Renderer::Update()
{
    context->Update();
}

void Renderer::Cleanup()
{
    context->Destroy();
}