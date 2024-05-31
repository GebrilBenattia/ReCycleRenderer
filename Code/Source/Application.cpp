#include "Application.hpp"
#include <iostream>

Application::Application()
{
	r = new Renderer();

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

}