#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "OpticalEscape.h"


// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
OpticalEscape::OpticalEscape(int w, int h){
    // std::cout << "(OpticalEscape.cpp) Constructor Called\n";
    // Initialization flag
    bool success = true;
    // String to hold any errors that occur.
    std::stringstream errorStream;
    // The window we'll be rendering to
    gWindow = NULL;
    // Render flag

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO)< 0){
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    }
    else{
    //Use OpenGL 3.3 core
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    // We want to request a double buffer for smooth updating.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //Create window
    gWindow = SDL_CreateWindow( "Optical Escape",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

        // Check if Window did not create.
        if( gWindow == NULL ){
            errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        //Create an OpenGL Graphics Context
        gContext = SDL_GL_CreateContext( gWindow );
        if( gContext == NULL){
            errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        // Initialize GLAD Library
        if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
            errorStream << "Failed to iniitalize GLAD and OpenGL\n";
            success = false;
        }
    }

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "OpticalEscape::OpticalEscape - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("OpticalEscape::OpticalEscape - No SDL, GLAD, or OpenGL, errors detected during initialization\n");
    }

    // SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
    getOpenGLVersionInfo();


    // Setup our Renderer
    renderer = new Renderer(w,h);
}



// Proper shutdown of SDL and destroy initialized objects
OpticalEscape::~OpticalEscape(){
    if(renderer!=nullptr){
        delete renderer;
    }

    //Destroy window
    SDL_DestroyWindow( gWindow );
    // Point gWindow to NULL to ensure it points to nothing.
    gWindow = NULL;
    //Quit SDL subsystems
    SDL_Quit();
}


Cube* giantCube;
SceneNode* skybox;

Cube* cubes[54];
SceneNode* cubeNodes[54];

LightManager* lightM = new LightManager(10);

//Loops forever!
void OpticalEscape::loop(){

    static float rotate = 0.0f;

    giantCube = new Cube(20, 1);
    skybox = new SceneNode(giantCube, 54, lightM);

    std::string skyboxTexture[6];
    skyboxTexture[0] = "right.ppm";
    skyboxTexture[1] = "left.ppm";
    skyboxTexture[2] = "bottom.ppm";
    skyboxTexture[3] = "top.ppm";
    skyboxTexture[4] = "back.ppm";
    skyboxTexture[5] = "front.ppm";

    giantCube->LoadCubeTexture(skyboxTexture);

    for(int i = 0; i < 54; i++) {
        cubes[i] = new Cube(0.40f);
        cubeNodes[i] = new SceneNode(cubes[i], i, lightM);
        cubes[i]->LoadTexture("carbon.ppm");
        // cubeNodes[i]->lights->addLight();
    }

    // Set our SceneTree up
    renderer->setRoot(skybox);
    
    for(int i = 0; i < 6; i++) {
        skybox->AddChild(cubeNodes[i]);
    }
    for(int i = 6; i < 54; i++) {
        if(i%6 == 0) cubeNodes[0]->AddChild(cubeNodes[i]);
        if(i%6 == 1) cubeNodes[1]->AddChild(cubeNodes[i]);
        if(i%6 == 2) cubeNodes[2]->AddChild(cubeNodes[i]);
        if(i%6 == 3) cubeNodes[3]->AddChild(cubeNodes[i]);
        if(i%6 == 4) cubeNodes[4]->AddChild(cubeNodes[i]);
        if(i%6 == 5) cubeNodes[5]->AddChild(cubeNodes[i]);
    }

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text 
    SDL_StartTextInput();

    // Set a default speed for the camera
    float cameraSpeed = 0.5f;
    int filter = 0;

    std::vector<int> cubesLeft;
    for(int i = 0; i < 54; i++) {
        cubesLeft.push_back(i);
    }
    std::random_shuffle(cubesLeft.begin(), cubesLeft.end());
    cubesLeft.push_back(54);
    int whereInCubes = 0;
    int gameOverCheckW = 0;
    int gameOverCheckL = 0;
    int untilFail = 2;
    bool End = false;

    std::cout << "\n\n\nWELCOME. PLEASE ENTER THE CORRECT PASSWORD TO INITIATE ESCAPE PROTOCOL. "
                 "=== PRESS q AT ANY TIME TO EXIT. PRESS h FOR INSTRUCTIONS ===\n\n";
    // While application is running
    while(!quit){

        rotate+=0.01f;

        cubeNodes[0]->getLocalTransform().loadIdentity();
        cubeNodes[0]->getLocalTransform().translate(0.0f, 0.0f, -2.0f);

        cubeNodes[1]->getLocalTransform().loadIdentity();
        cubeNodes[1]->getLocalTransform().translate(-2.0f, 0.0f, 0.0f);
        cubeNodes[1]->getLocalTransform().rotate(1.570796f,0.0f,1.0f,0.0f);

        cubeNodes[2]->getLocalTransform().loadIdentity();
        cubeNodes[2]->getLocalTransform().translate(0.0f, 0.0f, 2.0f);
        cubeNodes[2]->getLocalTransform().rotate(3.141593f,0.0f,1.0f,0.0f);

        cubeNodes[3]->getLocalTransform().loadIdentity();
        cubeNodes[3]->getLocalTransform().translate(2.0f, 0.0f, 0.0f);
        cubeNodes[3]->getLocalTransform().rotate(4.712389f,0.0f,1.0f,0.0f);

        cubeNodes[4]->getLocalTransform().loadIdentity();
        cubeNodes[4]->getLocalTransform().translate(0.0f, 2.0f, 0.0f);
        cubeNodes[4]->getLocalTransform().rotate(1.570796f,1.0f,0.0f,0.0f);

        cubeNodes[5]->getLocalTransform().loadIdentity();
        cubeNodes[5]->getLocalTransform().translate(0.0f, -2.0f, 0.0f);
        cubeNodes[5]->getLocalTransform().rotate(4.712389f,1.0f,0.0f,0.0f);

        for(int i = 6; i < 54; i++) {
            if(i < 12) {
                cubeNodes[i]->getLocalTransform().loadIdentity();
                cubeNodes[i]->getLocalTransform().translate(1.0f,1.0f,0.0f);
            }
            if(i >= 12 && i < 18) {
                cubeNodes[i]->getLocalTransform().loadIdentity();
                cubeNodes[i]->getLocalTransform().translate(1.0f,0.0f,0.0f);
            }
            if(i >= 18 && i < 24) {
                cubeNodes[i]->getLocalTransform().loadIdentity();
                cubeNodes[i]->getLocalTransform().translate(1.0f,-1.0f,0.0f);
            }
            if(i >= 24 && i < 30) {
                cubeNodes[i]->getLocalTransform().loadIdentity();
                cubeNodes[i]->getLocalTransform().translate(0.0f,1.0f,0.0f);
            }
            if(i >= 30 && i < 36) {
                cubeNodes[i]->getLocalTransform().loadIdentity();
                cubeNodes[i]->getLocalTransform().translate(0.0f,-1.0f,0.0f);
            }
            if(i >= 36 && i < 42) {
                cubeNodes[i]->getLocalTransform().loadIdentity();
                cubeNodes[i]->getLocalTransform().translate(-1.0f,1.0f,0.0f);
            }
            if(i >= 42 && i < 48) {
                cubeNodes[i]->getLocalTransform().loadIdentity();
                cubeNodes[i]->getLocalTransform().translate(-1.0f,0.0f,0.0f);
            }
            if(i >= 48 && i < 54) {
                cubeNodes[i]->getLocalTransform().loadIdentity();
                cubeNodes[i]->getLocalTransform().translate(-1.0f,-1.0f,0.0f);
            }
        }

        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                std::cout << "\n=== ESCAPE PROTOCOL TERMINATED ===\n\n";
                quit = true;
            }
            // Handle keyboad input for the camera class
            if(e.type==SDL_MOUSEMOTION){
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
               renderer->camera->mouseLook(mouseX, mouseY);
            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT:
                            renderer->camera->moveLeft(cameraSpeed);
                            break;
                        case SDLK_RIGHT:
                            renderer->camera->moveRight(cameraSpeed);
                            break;
                        case SDLK_UP:
                            renderer->camera->moveForward(cameraSpeed);
                            break;
                        case SDLK_DOWN:
                            renderer->camera->moveBackward(cameraSpeed);
                            break;
                        case SDLK_RSHIFT:
                            renderer->camera->moveUp(cameraSpeed);
                            break;
                        case SDLK_RCTRL:
                            renderer->camera->moveDown(cameraSpeed);
                            break;
                        case SDLK_f:
                            renderer->camera->lookFront();
                            break;
                        case SDLK_q:
                            std::cout << "\n=== ESCAPE PROTOCOL TERMINATED ===\n\n";
                            quit = true;
                            break;
                        case SDLK_h:
                            help();
                            break;
                    }
                break;
            }
        } // End SDL_PollEvent loop.
        // Update the renderer for the pick framebuffer
        renderer->Update();
        // Draw the scene to the pick frambuffer with the cubeIDs encoded, and
        // grab ID of center pixel.
        int lookID = renderer->Pick();
        // Update our scene through our renderer
        renderer->Update(lookID, cubesLeft[whereInCubes]);
        // Render our scene using our selected renderer
        renderer->Render(filter);
        // Delay to slow things down just a bit!
        SDL_Delay(25); 
        //Update screen of our specified window
        SDL_GL_SwapWindow(getSDLWindow());
        // Check how many cubes are either eliminated or locked in
        for(int i = 0; i < 54; i++) {
            gameOverCheckW += cubeNodes[i]->gone;
            gameOverCheckL += cubeNodes[i]->wrong;
        }
        whereInCubes = gameOverCheckW;
        // If the player has made it part way through the game, we want to difficulty to increase
        // we also give them a couple of extra mulligans as the difficulty increases
        switch (whereInCubes) {
            case (15):
                for(int i = 0; i < 54; i++) {if(cubeNodes[i]->getDifficulty() < 2) cubeNodes[i]->addDifficulty(1);}
                break;
            case (25):
                for(int i = 0; i < 54; i++) {if(cubeNodes[i]->getDifficulty() < 3) cubeNodes[i]->addDifficulty(1);}
                if(untilFail == 2) ++untilFail;
                break;
            case (34):
                for(int i = 0; i < 54; i++) {if(cubeNodes[i]->getDifficulty() < 4) cubeNodes[i]->addDifficulty(1);}
                if(untilFail == 3) ++untilFail;
                break;
            case (42):
                for(int i = 0; i < 54; i++) {if(cubeNodes[i]->getDifficulty() < 5) cubeNodes[i]->addDifficulty(1);}
                if(untilFail == 4) ++untilFail;
                break;
            default:
                break;
        }
        // In case the new selection is already locked out, we want the player to proceed
        while(cubeNodes[cubesLeft[whereInCubes]]->wrong == 1 || cubeNodes[cubesLeft[whereInCubes]]->gone == 1) ++whereInCubes;
        // if the number of failures is above threshold, reset the game nodes.
        if(gameOverCheckL > untilFail) {
            std::cout << "\nTOO MANY FAILED ATTEMPTS: PASSWORD NOT ACCEPTED\n=== ESCAPE ACTIVATION SEQUENCE RESET ===\n\n";
            for(int i = 0; i < 54; i++) {
                cubeNodes[i]->nodeReset();
            }
        }
        // If they've eliminated or locked out all cubes, they win! removes locked out cubes to that
        // The player can look around the skybox
        if(gameOverCheckW + gameOverCheckL == 54) {
            std::cout << "\nWE HOPE YOU ENJOYED YOUR STAY. PLEASE ENJOY THE VIEW. === PRESS q TO EXIT ===\n";
            for(int i = 0; i < 54; i++) {
                cubeNodes[i]->gone = 1;
            }
            End = true;
        }
        if(End) {
            for(int i = 0; i < 54; i++) {
                if(cubeNodes[i]->fade < 1.6f) cubeNodes[i]->fade += 0.03;
            }
        }
        // Reset the counters for next round. 
        gameOverCheckW = 0;
        gameOverCheckL = 0;
    }

    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* OpticalEscape::getSDLWindow(){
  return gWindow;
}

// Helper Function to get OpenGL Version Information
void OpticalEscape::getOpenGLVersionInfo(){
    SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
    SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
    SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
    SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
    SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void OpticalEscape::help() {
    SDL_Event e;
    // Enable text 
    SDL_StartTextInput();
    bool quit = false;
    const char* help = "\nGAME PAUSED FOR HELP.\nHOW TO PLAY: The center of the screen is "
            "your picker.\nFind the green cube in the scene and look at the cube long enough to remove it.\n"
            "After removing every cube, the escape sequence is successfully activated.\nAfter completing the escape "
            "sequence, all locked-in,  incorrect blocks\nwill be removed and you'll be able to freely view the sky.\n"
            "\nTHE GAME WILL GROW MORE DIFFICULT THE MORE CORRECT ACCESSES YOU HAVE IN A GIVEN SEQUENCE.\n"
            "\n===PRESS h TO RESUME ===\n";
    std::cout << help << std::endl;
    while(!quit) {
            while(SDL_PollEvent( &e ) != 0) {
            if(e.type == SDL_QUIT){
                quit = true;
            }
            switch(e.type){
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_h:
                            quit = true;
                            break;
                }
            }
        }
    }
}
