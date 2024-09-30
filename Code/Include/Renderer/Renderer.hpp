#pragma once

#include <Window.hpp>
#include <IRendererContext.hpp>
#include <IRHI.hpp>
#include <memory>

class Renderer
{
private:

	static inline const Window* m_Window = nullptr;
	static inline std::unique_ptr<IRendererContext> m_Context = nullptr;
	static inline std::unique_ptr<IRHI> m_RHI = nullptr;

public:

	Renderer(const Window* _Window);

	/// <summary>
	/// Creates Graphics API context
	/// </summary>
	/// <param name="_ActiveContext : Graphics API choosed by the user"></param>
	void CreateActiveContext(const RENDERING_CONTEXT _ActiveContext);

	/// <summary>
	/// Initializes the renderer
	/// </summary>
	/// <param name="_ActiveContext : Graphics API choosed by the user"></param>
	void Init(const RENDERING_CONTEXT& _ActiveContext);

	// Updates the renderer
	void Update();

	// Cleans up the allocated rendering stuff before application shutdown
	void Cleanup();

	// Returns a pointer of the application Window
	[[nodiscard]] static const Window* GetWindow() { return m_Window; }

	// Returns the active RendererContext
	[[nodiscard]] static const IRendererContext* GetContext() { return m_Context.get(); }

	// Returns the RHI linked to the active RendererContext
	[[nodiscard]] static const IRHI* GetRHI() { return m_RHI.get(); }
};