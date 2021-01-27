#include "Renderer.h"

// Sets the height and width of our renderer
Renderer::Renderer(unsigned int w, unsigned int h) {
    // std::cout << "(Renderer.cpp) Constructor called)\n";
    screenWidth = w;
    screenHeight = h;
    // Init our camera
    camera = new Camera();
    root = nullptr;
    // Setup our Framebuffer within the renderer
    myFramebuffer = new Framebuffer();
    myFramebuffer->Create(w,h);
    // Set up the framebuffer for picking!
    pickerBuffer = new PickerBuffer();
    pickerBuffer->Create(w,h);
}


// Sets the height and width of our renderer
Renderer::~Renderer() {
    delete camera;
    delete myFramebuffer;
    delete pickerBuffer;
}


void Renderer::Update() {
    projectionMatrix = glm::perspective(45.0f,((float)screenWidth)/((float)screenHeight),0.1f,512.0f);
    // Perform the update
    if(root!=nullptr) {
        root->Update(projectionMatrix, camera);
    }
}


void Renderer::Update(int lookID, int target) {
    projectionMatrix = glm::perspective(45.0f,((float)screenWidth)/((float)screenHeight),0.1f,512.0f);
    // Perform the update
    if(root!=nullptr) {
        root->Update(projectionMatrix, camera, lookID, target);
    }
}


void Renderer::Render(){
    // Setup our uniforms
    myFramebuffer->Update();
    // Bind to our framebuffer
    myFramebuffer->Bind();
    // What we are doing, is telling opengl to create a depth(or Z-buffer)
    // for us that is stored every frame.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    // This is the background of the screen.
    glViewport(0, 0, screenWidth, screenHeight);
    glClearColor( 0.4f, 0.4f, 0.4f, 1.f );
    // Clear color buffer and Depth Buffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // This is how we know things are working with our FBO
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    // Now we render our objects from our scenegraph
    if(root!=nullptr){
        root->Draw();
    }
    // Finish with our framebuffer
    myFramebuffer->Unbind();
    // Now draw a new scene
    // We do not need depth since we are drawing a '2D'
    // image over our screen.
    glDisable(GL_DEPTH_TEST);
    // Clear everything away
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    // We only have 'color' in our buffer that is stored
    glClear(GL_COLOR_BUFFER_BIT);
    // Use our new 'simple screen shader'
    myFramebuffer->fboShader->Bind();
    // Overlay our 'quad' over the screen
    myFramebuffer->drawFBO();
    // Unselect our shader and continue
    myFramebuffer->fboShader->Unbind();
}


void Renderer::Render(int filter){
    // Setup our uniforms
    myFramebuffer->Update(filter);
    // Bind to our framebuffer
    myFramebuffer->Bind();
    // What we are doing, is telling opengl to create a depth(or Z-buffer)
    // for us that is stored every frame.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    // This is the background of the screen.
    glViewport(0, 0, screenWidth, screenHeight);
    glClearColor( 0.4f, 0.4f, 0.4f, 1.f );
    // Clear color buffer and Depth Buffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // This is how we know things are working with our FBO
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    // Now we render our objects from our scenegraph
    if(root!=nullptr){
        root->Draw();
    }
    myFramebuffer->Unbind();
    // Now draw a new scene
    // We do not need depth since we are drawing a '2D'
    // image over our screen.
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    // We only have 'color' in our buffer that is stored
    glClear(GL_COLOR_BUFFER_BIT);
    // Use our new 'simple screen shader'
    myFramebuffer->fboShader->Bind();
    // Overlay our 'quad' over the screen
    myFramebuffer->drawFBO();
    // Unselect our shader and continue
    myFramebuffer->fboShader->Unbind();
}


// Determines what the root is of the renderer, so the
// scene can be drawn.
void Renderer::setRoot(SceneNode* n){
    root = n;
}


int Renderer::Pick() {
    // Setup our uniforms
    // In reality, only need to do this once for this
    // particular fbo because the texture data is
    // not going to change.
    // pickerBuffer->Update();
    // Bind to our framebuffer
    pickerBuffer->Bind();
    // Set up to draw
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, screenWidth, screenHeight);
    glClearColor( 0.4f, 0.4f, 0.4f, 1.f );
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    // Draw to our pick buffer
    if(root!=nullptr){
        root->DrawWPick();
    }
    // Grab the center pixel values!!
    unsigned char pixel[4];
    glReadPixels(screenWidth/2, screenHeight/2, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    // Finish with our framebuffer
    pickerBuffer->Unbind();
    return static_cast<int>(pixel[0]);
}

