#pragma once

#include <Window.hpp>
#include <IRendererContext.hpp>
#include <Renderer.hpp>
#include <memory>
#include <optional>

class Application
{
private:

	std::unique_ptr<Window> m_Window = nullptr;
	RENDERING_CONTEXT m_ActiveContext = RENDERING_CONTEXT::OPENGL;
	std::unique_ptr<Renderer> m_Renderer = nullptr;

public:

	// std::nullopt works as a = 0 but it also allows me to declare my app as if I had default constructor
	Application(const std::optional<const int>& _Width = std::nullopt, const std::optional<const int>& _Height = std::nullopt);
	~Application();

	// Asks the user to select the active Graphics API context for the rendering
	void SelectActiveContext();

	// Initializes the application
	void Init();

	// Updates the application
	void Update();

	// Shuts down the application (e.g. cleaning, destroying allocated stuff)
	void Shutdown();
};