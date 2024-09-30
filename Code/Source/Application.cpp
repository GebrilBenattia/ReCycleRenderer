#include <Application.hpp>
#include <iostream>

Application::Application(const std::optional<const int>& _Width, const std::optional<const int>& _Height)
{
	// Asks the client to choose which Graphics API to use
	//SelectActiveContext();

	// Creates a shared pointer to Application Window instance, ensuring proper memory management
	m_Window = std::make_unique<Window>(m_ActiveContext, _Width.value_or(900), _Height.value_or(700));

	// Creates a unique pointer to a Renderer instance, ensuring proper memory management.
	m_Renderer = std::make_unique<Renderer>(m_Window.get());

	// Outputs a message indicating that the application is launching, with green text for visibility.
	std::cout << "\x1b[32m" << "Launching ReCycleRenderer..." << "\x1b[0m" << std::endl;

	// Initializes the renderer and any necessary components.
	Init();
}

Application::~Application()
{
	// Calls the Shutdown function to clean up resources before the application is destroyed.
	Shutdown();
}

void Application::SelectActiveContext()
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

		m_ActiveContext = static_cast<RENDERING_CONTEXT>(choice - 1);
		break;  // Breaks out of the loop if valid input is received
	}
}

void Application::Init()
{
	// Initializes the renderer, which sets up the graphics context and prepares rendering according the API choice.
	m_Renderer->Init(m_ActiveContext);
}

void Application::Update()
{
	// Loops until GLFW window has been instructed to close
	while (!glfwWindowShouldClose(m_Window->window.get())) {
		// Checks if any event has been triggered (keyboard inputs, mouse events), update the window state and calls the corresponding functions (callbacks)
		glfwPollEvents();

		// Updates the renderer
		m_Renderer->Update();
	}
}

void Application::Shutdown()
{
	// Destroys the window, releasing any resources it holds before the application fully shuts down.
	m_Window.get()->Destroy();

	// Outputs a message indicating that the application is closing, with red text for visibility.
	std::cout << "\x1b[31m" << "Closing ReCycleRenderer..." << "\x1b[0m" << std::endl;
}