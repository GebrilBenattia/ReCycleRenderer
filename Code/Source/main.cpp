#include "Application.hpp"
#include <exception>
#include <iostream>

int main()
{
	Application app;

	try {
		app.Update();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}