#include "Renderer.hpp"

#include <OpenGLContext.hpp>
#include <VulkanContext.hpp>
#include <DirectXContext.hpp>

#include <stdexcept>
#include <iostream>

void Renderer::SelectActiveContext()
{
	while (true) {
		std::cout << "Select the renderer context:\n"
			<< "1. OpenGL\n"
			<< "2. Vulkan\n"
			<< "3. DirectX\n"
			<< "Enter your choice (1-3): ";

		int choice;
		if (!(std::cin >> choice)) {
			std::cout << "\x1b[2J\x1b[H";
			std::cerr << "Invalid input. Please enter a number." << std::endl;
			std::cin.clear();  // Clear error flags
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
			continue;  // Ask for input again
		}

		if (choice < 1 || choice > 3) {
			std::cout << "\x1b[2J\x1b[H";
			std::cerr << "Invalid choice. Please enter a number between 1 and 3." << std::endl;
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
		break;
	case VULKAN:
		std::cout << "Creating Vulkan context...\n";
		context = new VulkanContext();
		break;
	case DIRECTX:
		std::cout << "Creating DirectX context...\n";
		context = new DirectXContext();
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