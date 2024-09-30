#pragma once

#include <IRendererContext.hpp>
#include <d3d12.h>
#include <memory>

class Direct3D12Context : public IRendererContext
{
private:

public:

	Direct3D12Context();
	~Direct3D12Context();

	// Initializes the Direct3D12 API context
	void Init() override;
	
	// Destroys the Direct3D12 API context (e.g. cleaning, destroying allocated stuff)
	void Destroy() override;
};