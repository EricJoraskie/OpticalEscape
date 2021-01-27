#ifndef OPTICALESCAPE
#define OPTICALESCAPE

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif


#include "Renderer.h"
#include <algorithm>

// Optical Escape Game
class OpticalEscape{
public:
    // Constructor
    OpticalEscape(int w, int h);
    // Desctructor
    ~OpticalEscape();
    // loop that runs forever
    void loop();
    // Get Pointer to Window
    SDL_Window* getSDLWindow();
    // Helper Function to Query OpenGL information.
    void getOpenGLVersionInfo();
    // Pause and print help message to terminal
    void help();

private:
    // The window we'll be rendering to
    SDL_Window* gWindow ;
    // OpenGL context
    SDL_GLContext gContext;
	// The Renderer responsible for drawing objects
	Renderer* renderer;
};

#endif