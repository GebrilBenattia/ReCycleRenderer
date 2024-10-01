#include <Renderer.hpp>

#include <OpenGLContext.hpp>
#include <VulkanContext.hpp>
#include <Direct3D11Context.hpp>
#include <Direct3D12Context.hpp>

#include <OpenGLRHI.hpp>
#include <VulkanRHI.hpp>
#include <Direct3D11RHI.hpp>
#include <Direct3D12RHI.hpp>

#include <stdexcept>
#include <iostream>

Renderer::Renderer(const Window* _Window)
{
	m_Window = _Window;
}

void Renderer::CreateActiveContext(const RENDERING_CONTEXT _ActiveContext)
{
	switch (_ActiveContext)
	{
	case OPENGL:
		std::cout << "Creating OpenGL context...\n";
		m_Context = std::make_unique<OpenGLContext>();
		m_RHI = std::make_unique<OpenGLRHI>();
		break;
	case VULKAN:
		std::cout << "Creating Vulkan context...\n";
		m_Context = std::make_unique<VulkanContext>();
		m_RHI = std::make_unique<VulkanRHI>();
		break;
	case DIRECT3D11:
		std::cout << "Creating Direct3D11 context...\n";
		m_Context = std::make_unique<Direct3D11Context>();
		m_RHI = std::make_unique<Direct3D11RHI>();
		break;
	case DIRECT3D12:
		std::cout << "Creating Direct3D12 context...\n";
		m_Context = std::make_unique<Direct3D12Context>();
		m_RHI = std::make_unique<Direct3D12RHI>();
		break;
	default:
		throw std::runtime_error("Select a renderer context");
		break;
	}
}

void Renderer::Init(const RENDERING_CONTEXT& _ActiveContext)
{
	CreateActiveContext(_ActiveContext);
	m_Context->Init(); // NOW OUTSIDE OF THE CONSTRUCTOR BECAUSE OF THE MULTIPLE CALL OF THE CONTEXT INSIDE OTHER SETUP CLASSES, NOT SET UNTIL WE GET OUT OF THE CONSTRUCTOR SO WE NEED TO PUT IT OUTSIDE, ELSE WE USE NULL POINTER
}

void Renderer::Update()
{
	m_RHI.get()->Update();
}

void Renderer::Cleanup()
{
}