#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <unordered_map>
#include <functional>

struct Input
{
	int key;
	int scancode;
	int action;
	int mod;

	bool operator==(const Input& other) const
	{
		return key == other.key &&
			scancode == other.scancode &&
			action == other.action &&
			mod == other.mod;
	}
};

// Hash function specialization for Input
template <>
struct std::hash<Input>
{
	size_t operator()(const Input& input) const
	{
		return std::hash<int>()(input.key) ^
			std::hash<int>()(input.scancode) ^
			std::hash<int>()(input.action) ^
			std::hash<int>()(input.mod);
	}
};

class InputBus
{
private:

	std::unordered_map<Input, std::vector<std::function<void(const Input&)>>> m_Listeners;

public:

	// Add callback related to a certain input
	void Subscribe(const Input& input, std::function<void(const Input&)> callback)
	{
		m_Listeners[input].push_back(callback);
	}

	// Calls the callbacks for all listeners bounded to a certain input
	void Publish(const Input& input)
	{
		for (const auto& callback : m_Listeners[input]) {
			callback(input);
		}
	}
};

class InputManager
{
private:

	GLFWwindow* m_Window;
	InputBus m_InputBus;

public:

	InputManager(GLFWwindow* window) : m_Window(window) 
	{
		// Create an Input instance for the Escape key
		Input escapeInput{ GLFW_KEY_ESCAPE, 0, GLFW_PRESS, 0 };
		m_InputBus.Subscribe(escapeInput, [this](const Input& input) 
		{
			// Close the window
			glfwSetWindowShouldClose(m_Window, true); 
		});
	}

	void HandleInput()
	{
		// Check the state of the Escape key
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			Input escapeInput{ GLFW_KEY_ESCAPE, 0, GLFW_PRESS, 0 };
			// Publish the input event
			m_InputBus.Publish(escapeInput);
		}

		// Handle other inputs if necessary
		// For example, you could read other keys and publish their events
	}
};