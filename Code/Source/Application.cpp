#include <Application.hpp>
#include <iostream>

Application::Application()
{
	r = new Renderer();

	std::cout << "\x1b[32m" << "Launching ReCycleRenderer..." << "\x1b[0m" << std::endl;
	Init();
}

Application::~Application()
{
	Shutdown();
}

void Application::Init()
{
	r->Init();
}

void Application::Update()
{
	r->Update();
}

void Application::Shutdown()
{
	std::cout << "\x1b[31m" << "Closing ReCycleRenderer..." << "\x1b[0m" << std::endl;
}