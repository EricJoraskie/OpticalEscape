#ifndef SCENENODE_H
#define SCENENODE_H
// Expanded on code from Mike Shah
#include <vector>
#include "Cube.h"
#include "Transform.h"
#include "Camera.h"
#include "Shader.h"
#include "LightManager.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SceneNode{
public:
    // A SceneNode is created by taking
    // a pointer to an object.
    SceneNode(Cube* ob, int ID, LightManager* lights);
    // Our destructor takes care of destroying
    // all of the children within the node.
    // Now we do not have to manage deleting
    // each individual object.
    ~SceneNode();
    // Adds a child node to our current node.
    void AddChild(SceneNode* n);
    // Draws the current SceneNode
    void Draw();
    // Draws the scene for the pick buffer
    void DrawWPick();
    // Updates the current SceneNode
    void Update(glm::mat4 projectionMatrix, Camera* camera);
    // Updates based on the look
    void Update(glm::mat4 projectionMatrix, Camera* camera, int lookID, int target);
    // Scales our color given where we're looking
    void scaleIntensity(int lookId, int target);
    // Scales how far gone our cube is in the geometry shader
    void scaleFade();
    //reset the node to starting state (in game failure event)
    void nodeReset();
    // set difficulty
    void addDifficulty(int upOrDown);
    // get difficulty
    int getDifficulty();
    // Returns the local transformation transform
    // Remember that local is local to an object, where it's center is the origin.
    Transform& getLocalTransform();
    // Returns a SceneNode's world transform
    Transform& getWorldTransform();
    // For now we have one shader per Node.

    // Yes, I could have made these private, but Ill do it later. Everythings works rn
    Shader myShader;
    // Shader for the screen picking
    Shader pickShader;
    // Shader for the skybox
    Shader skyShader;
    // Manages The scene lights
    LightManager* lights;
    // THe intensity of the color of the object we're looking at
    glm::vec3 intensity;
    // The amount to 
    float fade;
    // Cube successfully eliminated!
    int gone;
    // Have we chosen the wrong cube?
    int wrong;

protected:
    // Parent
    SceneNode* parent;
private:
    // Children of the scene node
    std::vector<SceneNode*> children;
    // The object stored in the scene graph
    Cube* object;
    // The scene node's Id number
    int ID;
    // increase difficulty as the game progresses
    int difficulty;
    // Each SceneNode nodes locals transform.
    Transform localTransform;
    // We additionally can store the world transform
    Transform worldTransform;
};

#endif
