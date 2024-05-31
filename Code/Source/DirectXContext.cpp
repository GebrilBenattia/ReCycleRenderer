#include "DirectXContext.hpp"

Window* DirectXContext::m_Window = nullptr;

DirectXContext::DirectXContext()
{
	Create();
}

DirectXContext::DirectXContext(const int _Width, const int _Height)
{
	Create(_Width, _Height);
}

DirectXContext::~DirectXContext()
{
	Destroy();
}

void DirectXContext::Create(std::optional<const int> _Width, std::optional<const int> _Height)
{
	if (m_Window) {
		delete m_Window;
	}
	m_Window = new Window(_Width.value_or(900), _Height.value_or(700));
}

void DirectXContext::InitDirectX()
{
}

void DirectXContext::Update()
{
	while (!glfwWindowShouldClose(m_Window->window)) {
		glfwPollEvents();

	}
}

void DirectXContext::Destroy()
{
	m_Window->Destroy();
}