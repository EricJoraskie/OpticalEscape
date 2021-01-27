#include "Object.h"
#include "Geometry.h"
#include <cmath>

#ifndef Cube_H
#define Cube_H

class Cube : public Object{

    public:
        // Constructor for the Cube
        Cube(float size, int sb=0);
        // The intialization routine for this object.
        void init(float size);
        // Is this a skybox?
        int skybox;
};

#endif