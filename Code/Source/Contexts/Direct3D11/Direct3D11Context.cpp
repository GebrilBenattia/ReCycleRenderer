#include "Direct3D11Context.hpp"

Direct3D11Context::Direct3D11Context()
{
	Create();
}

Direct3D11Context::Direct3D11Context(const int& _Width, const int& _Height)
{
	Create(_Width, _Height);
}

Direct3D11Context::~Direct3D11Context()
{
	Destroy();
}

void Direct3D11Context::Create(const std::optional<const int>& _Width, const std::optional<const int>& _Height)
{
	if (m_Window) {
		delete m_Window;
	}
	m_Window = new Window(_Width.value_or(900), _Height.value_or(700));
}

void Direct3D11Context::Init()
{
}

void Direct3D11Context::Update()
{
	while (!glfwWindowShouldClose(m_Window->window)) {
		glfwPollEvents();

	}
}

void Direct3D11Context::Destroy()
{
	m_Window->Destroy();
}