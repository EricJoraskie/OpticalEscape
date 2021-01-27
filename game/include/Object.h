/** 
 * Expanded on code written by Mike Shah
 * 
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <vector>

#include "Buffer.h"
#include "Texture.h"
#include "Geometry.h"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Purpose:
// An abstraction to create multiple objects
class Object{
public:
    // Object Constructor
    Object();
    // Object destructor
    ~Object();
    // Initialization routine
    // The method can be overridden by other primitives.
    virtual void init();
    // How to draw the object
    void render();
    // Added renderSky, used to render skybox
    void renderSky();
    // Loads a specific texture
    void LoadTexture(std::string fileName);
    // Used to load cubetexture
    void LoadCubeTexture(std::string fileName[]);

protected:
    // Helper method for when we are ready to draw or update our object
    void Bind();
    // Binds the necessary for skybox
    void BindSky();
    // For now we have one buffer per object.
    Buffer myBuffer;
    // For now we have one diffuse map and one normal map per object
    Texture diffuseMap;
    // Store the objects Geometry
    Geometry geometry;
};


#endif
