#ifndef RENDERER_H
#define RENDERER_H
/**
 * Extended on code by Mike Shah
 * 
 * 
*/
#include <glad/glad.h>

#include <vector>

#include "SceneNode.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "PickerBuffer.h"

class Renderer{
public:
    // The constructor	
    // Sets the width and height of the rendererer draws to
    Renderer(unsigned int w, unsigned int h);
    // Destructor
    ~Renderer();
    // Update the scene
    void Update();
    void Update(int lookID, int target);
    // Render the scene
    void Render();
    // overloading the render to pass the filter to the framebuffer
    // from the keyboard
    void Render(int filter);
    // Sets the root of our renderer to some node to
    // draw an entire scene graph
    void setRoot(SceneNode* n);
    // The method we use to draw the scene with the pickBuffer
    int Pick();
    // The one camera per Renderer
    Camera* camera;
    // A renderer can have any number of framebuffers
    // For now, let's just initialize one.
    Framebuffer* myFramebuffer;
    // The pickbuffer (which is really just a FrameBuffer... I didn't really
    // need a different class, just the option to input a different shader
    // but I'm running out of time for code clean up, so this is how I'll submit)
    PickerBuffer* pickerBuffer;
protected:
    // Root scene node
    SceneNode* root;
    // Store the projection matrix for our camera.
    glm::mat4 projectionMatrix;

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
};

#endif
