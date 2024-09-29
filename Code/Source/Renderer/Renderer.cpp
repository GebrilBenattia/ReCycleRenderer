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

void Renderer::SelectActiveContext()
{
	while (true) {
		std::cout << "Select the renderer context:\n"
			<< "1. OpenGL\n"
			<< "2. Vulkan\n"
			<< "3. Direct3D11\n"
			<< "4. Direct3D12\n"
			<< "Enter your choice (1-4): ";

		int choice;
		if (!(std::cin >> choice)) {
			std::cout << "\x1b[2J\x1b[H";
			std::cerr << "\x1b[31m" << "Invalid input. Please enter a number." << "\x1b[0m" << std::endl;
			std::cin.clear();  // Clear error flags
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
			continue;  // Ask for input again
		}

		if (choice < 1 || choice > 4) {
			std::cout << "\x1b[2J\x1b[H";
			std::cerr << "\x1b[31m" << "Invalid choice. Please enter a number between 1 and 4." << "\x1b[0m" << std::endl;
			continue;  // Ask for input again
		}

		activeContext = static_cast<RENDERING_CONTEXT>(choice - 1);
		break;  // Break out of the loop if valid input is received
	}
}

void Renderer::CreateActiveContext()
{
	switch (activeContext)
	{
	case OPENGL:
		std::cout << "Creating OpenGL context...\n";
		context = new OpenGLContext();
		rhi = new OpenGLRHI();
		break;
	case VULKAN:
		std::cout << "Creating Vulkan context...\n";
		context = new VulkanContext();
		rhi = new VulkanRHI();
		break;
	case DIRECT3D11:
		std::cout << "Creating Direct3D11 context...\n";
		context = new Direct3D11Context();
		rhi = new Direct3D11RHI();
		break;
	case DIRECT3D12:
		std::cout << "Creating Direct3D12 context...\n";
		context = new Direct3D12Context();
		rhi = new Direct3D12RHI();
		break;
	default:
		throw std::runtime_error("Select a renderer context");
		break;
	}
}

void Renderer::Init()
{
	//SelectActiveContext();
	CreateActiveContext();
	context->Init(); // NOW OUTSIDE OF THE CONSTRUCTOR BECAUSE OF THE MULTIPLE CALL OF THE CONTEXT INSIDE OTHER SETUP CLASSES, NOT SET UNTIL WE GET OUT OF THE CONSTRUCTOR SO WE NEED TO PUT IT OUTSIDE, ELSE WE USE NULL POINTER
}

void Renderer::Update()
{
    context->Update();
}