#include <Direct3D12Context.hpp>

Direct3D12Context::Direct3D12Context()
{
	Create();
}

Direct3D12Context::Direct3D12Context(const int& _Width, const int& _Height)
{
	Create(_Width, _Height);
}

Direct3D12Context::~Direct3D12Context()
{
	Destroy();
}

void Direct3D12Context::Create(const std::optional<const int>& _Width, const std::optional<const int>& _Height)
{
	if (m_Window) {
		delete m_Window;
	}
	m_Window = new Window(_Width.value_or(900), _Height.value_or(700));
}

void Direct3D12Context::Init()
{
}

void Direct3D12Context::Update()
{
	// Loop until GLFW window has been instructed to close
	while (!glfwWindowShouldClose(m_Window->window)) {
		// Checks if any event has been triggered (keyboard inputs, mouse events), update the window state and calls the corresponding functions (callbacks)
		glfwPollEvents();

	}
}

void Direct3D12Context::Destroy()
{
	m_Window->Destroy();
}