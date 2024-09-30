#pragma once

#include <IRendererContext.hpp>
#include <d3d11.h>
#include <memory>

#ifdef max
#undef max // causes a redefinition error in Renderer.cpp because it's defined in a header that <d3d11> include 
#endif

class Direct3D11Context : public IRendererContext
{
private:

public:

	Direct3D11Context();
	~Direct3D11Context();

	// Initializes the Direct3D11 API context
	void Init() override;
	
	// Destroys the Direct3D11 API context (e.g. cleaning, destroying allocated stuff)
	void Destroy() override;
};