#include "Cube.h"


// Calls the initalization routine
Cube::Cube(float size, int sb){
    skybox = sb;
    init(size);
}

// Construct the geometry for a cube
void Cube::init(float size){
        // Positions
        // Face 1
        geometry.addVertex(-size, -size,  size);   // 1
        geometry.addVertex( size, -size,  size);   // 2
        geometry.addVertex(-size,  size,  size);   // 3
        geometry.addVertex(-size,  size,  size);   // 3
        geometry.addVertex( size, -size,  size);   // 2
        geometry.addVertex( size,  size,  size);   // 4
        // Face 2
        geometry.addVertex(-size,  size,  size);   // 3
        geometry.addVertex( size,  size,  size);   // 4
        geometry.addVertex(-size,  size, -size);   // 5
        geometry.addVertex(-size,  size, -size);   // 5
        geometry.addVertex( size,  size,  size);   // 4
        geometry.addVertex( size,  size, -size);   // 6
        // Face 3
        geometry.addVertex(-size,  size, -size);   // 5
        geometry.addVertex( size,  size, -size);   // 6
        geometry.addVertex(-size, -size, -size);   // 7
        geometry.addVertex(-size, -size, -size);   // 7
        geometry.addVertex( size,  size, -size);   // 6
        geometry.addVertex( size, -size, -size);   // 8
        // Face 4
        geometry.addVertex(-size, -size, -size);   // 7
        geometry.addVertex( size, -size, -size);   // 8
        geometry.addVertex(-size, -size,  size);   // 1
        geometry.addVertex(-size, -size,  size);   // 1
        geometry.addVertex( size, -size, -size);   // 8
        geometry.addVertex( size, -size,  size);   // 2
        // Face 5
        geometry.addVertex( size, -size,  size);   // 2
        geometry.addVertex( size, -size, -size);   // 8
        geometry.addVertex( size,  size,  size);   // 4
        geometry.addVertex( size,  size,  size);   // 4
        geometry.addVertex( size, -size, -size);   // 8
        geometry.addVertex( size,  size, -size);   // 6
        // Face 6
        geometry.addVertex(-size, -size, -size);   // 7
        geometry.addVertex(-size, -size,  size);   // 1
        geometry.addVertex(-size,  size, -size);   // 5
        geometry.addVertex(-size,  size, -size);   // 5
        geometry.addVertex(-size, -size,  size);   // 1
        geometry.addVertex(-size,  size,  size);   // 3

        // Textures
        // Face 1
        geometry.addTexture(0.0f, 0.0f);         // 1
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(1.0f, 1.0f);         // 4
        // Face 2
        geometry.addTexture(0.0f, 0.0f);         // 1
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(1.0f, 1.0f);         // 4
        // Face 3
        geometry.addTexture(0.0f, 0.0f);         // 1
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(1.0f, 1.0f);         // 4
        // Face 4
        geometry.addTexture(0.0f, 0.0f);         // 1
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(1.0f, 1.0f);         // 4
        // Face 5
        geometry.addTexture(0.0f, 0.0f);         // 1
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(1.0f, 1.0f);         // 4
        // Face 6
        geometry.addTexture(0.0f, 0.0f);         // 1
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(0.0f, 1.0f);         // 3
        geometry.addTexture(1.0f, 0.0f);         // 2
        geometry.addTexture(1.0f, 1.0f);         // 4

        // Make our triangles and populate our
        // indices data structure
        // F1
        geometry.makeTriangle(0,1,2);
        geometry.makeTriangle(3,4,5);
        // F2
        geometry.makeTriangle(6,7,8);
        geometry.makeTriangle(9,10,11);
        // F3
        geometry.makeTriangle(12,13,14);
        geometry.makeTriangle(15,16,17);
        // F4
        geometry.makeTriangle(18,19,20);
        geometry.makeTriangle(21,22,23);
        // F5
        geometry.makeTriangle(24,25,26);
        geometry.makeTriangle(27,28,29);
        // F6
        geometry.makeTriangle(30,31,32);
        geometry.makeTriangle(33,34,35);

        // Finally generate a simple 'array of bytes' that contains
        // everything for our buffer to work with.
        geometry.gen();

        // Create a buffer and set the stride of information
        myBuffer.CreateBufferNormalMapLayout(14,
                                            geometry.getSize(),
                                            geometry.getIndicesSize(),
                                            geometry.getData(),
                                            geometry.getIndicesData());
}