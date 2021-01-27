/** 
 * A tiny modification to FrameBuffer
 * If we're being honest, this doesn't deserve it's own class
 * I should have made it so that you can just give a framebuffer a specfic
 * shader, but everything works and I'll break it after I submit it
 */
#ifndef PICKER_BUFFER_H
#define PICKER_BUFFER_H

#include <glad/glad.h>
#include "Shader.h" // Each PickerBuffer can have a custom shader

class PickerBuffer{
public:
    // Default Constructor
    PickerBuffer();
    // Destructor
    ~PickerBuffer();
    // Create the PickerBuffer
    void Create(int width, int height);
    // Select our PickerBuffer
    void Bind();
    // Update our PickerBuffer once per frame for any
    // changes that may have occurred.
    void Update();
    // overloading our update to pass the filter version from the keyboard
    void Update(int filter);
    // Done with our PickerBuffer
    void Unbind();
    // Draws the screen quad
    void drawFBO();
private: 
    // Creates a quad that will be overlaid on top of the screen
    // ? add x1,x2, etc. to draw FBO over a range in the scene.
    void setupScreenQuad(float x1,float x2, float y1, float y2);
// public member variables
public:
    Shader* fboShader;
    // Our PickerBuffer also needs a texture.
    unsigned int colorBuffer_id;
// private member variables
private:
    // PickerBuffer id
    unsigned int fbo_id; 
    // Finally create our render buffer object
    unsigned int rbo_id;
    // Store our screen buffer
    unsigned int quadVAO, quadVBO;

};

#endif
