// Expanded upon code by Mike Shah

#include "OpticalEscape.h"
#include <iostream>

int main(int argc, char** argv){

	std::cout << "(main.cpp) Beginning Intitialization\n";
	// Create an instance of an object for a SDLGraphicsProgram
	OpticalEscape gameController(1480,820);  // 1280,720
	// Run our program forever
	gameController.loop();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}
