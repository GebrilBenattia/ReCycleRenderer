#include <VulkanContext.hpp>

VulkanContext::VulkanContext()
{
    Create();
}

VulkanContext::VulkanContext(const int& _Width, const int& _Height)
{
    Create(_Width, _Height);
}

VulkanContext::~VulkanContext()
{
	Destroy();
}

void VulkanContext::Create(const std::optional<const int>& _Width, const std::optional<const int>& _Height)
{
    if (m_Window) {
        delete m_Window;
    }
	m_Window = new Window(_Width.value_or(900), _Height.value_or(700));
}

void VulkanContext::Init()
{
}

void VulkanContext::Update()
{
    // Loop until GLFW window has been instructed to close
    while (!glfwWindowShouldClose(m_Window->window)) {
        // Checks if any event has been triggered (keyboard inputs, mouse events), update the window state and calls the corresponding functions (callbacks)
        glfwPollEvents();

    }
}

void VulkanContext::Destroy()
{
    m_Window->Destroy();
}