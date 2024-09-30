#include <Application.hpp>
#include <exception>
#include <iostream>

int main()
{
	try {
		// Creating application instance
		Application app;

		// Performs the main update loop
		app.Update();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	// Indicates success if no exceptions occurred
	return EXIT_SUCCESS;
}