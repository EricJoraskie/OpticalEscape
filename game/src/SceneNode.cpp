#include "SceneNode.h"
#include <string>

// The constructor
SceneNode::SceneNode(Cube* ob, int IdNum, LightManager* theLights){
  // std::cout << "(SceneNode.cpp) Constructor called\n";
  object = ob;
  ID = IdNum;
  lights = theLights;
  intensity = glm::vec3(0.0f, 0.0f, 0.0f);
  fade = 0.0f;
  gone = 0;
  wrong = 0;
  difficulty = 1;
  parent = nullptr;
  // Setup shaders for the node.
  std::string vertexShader = myShader.LoadShader("./shaders/vert.glsl");
  std::string fragmentShader = myShader.LoadShader("./shaders/frag.glsl");
  std::string geometryShader = myShader.LoadShader("./shaders/geom.glsl");
  // Actually create our shader
  myShader.CreateShader(vertexShader,fragmentShader, geometryShader);

  std::string pickVertShader = pickShader.LoadShader("./shaders/vert.glsl");
  std::string pickFragShader = pickShader.LoadShader("./shaders/pickFrag.glsl");
  // Actually create our shader
  pickShader.CreateShader(pickVertShader, pickFragShader);

  std::string skyVertShader = skyShader.LoadShader("./shaders/cubeMapVert.glsl");
  std::string skyFragShader = skyShader.LoadShader("./shaders/cubeMapFrag.glsl");
  // Actually create our shader
  skyShader.CreateShader(skyVertShader, skyFragShader);
}


// The destructor
SceneNode::~SceneNode(){
  // Remove each object
  for(unsigned int i =0; i < children.size(); ++i){
    delete children[i];
  }
}


// Adds a child node to our current node.
void SceneNode::AddChild(SceneNode* n){
  n->parent = this;
  // Add a child node into our SceneNode
  children.push_back(n);
}


// Draw simply draws the current nodes
void SceneNode::Draw(){
  // If its the skybox, use the skyshader
  if(object->skybox) skyShader.Bind();
  else myShader.Bind();
  if(object!=nullptr){
    // if its the skybox render as cubeMap, otherwise draw normally
    if(object->skybox) object->renderSky();
    else object->render();
    for(int i = 0; i < children.size(); ++i){
      children[i]->Draw();
    }
  }
}


// Draws to our pickbuffer to help with screen picking
void SceneNode::DrawWPick(){
  pickShader.Bind();
  if(object!=nullptr){
    object->render();
    for(int i = 0; i < children.size(); ++i){
      children[i]->DrawWPick();
    }
  }
}


// We use this update when setting our picking buffer
void SceneNode::Update(glm::mat4 projectionMatrix, Camera* camera){
  if(object!=nullptr){
    if(parent) {
      worldTransform = parent->worldTransform*localTransform;
    } else {
      worldTransform = localTransform;
    }
    // Now apply our shader transformation
    myShader.Bind();
      myShader.setUniform1i("material.diffuse", 0);
      myShader.setUniform1i("material.specular", 1);
      myShader.setUniform1f("material.shininess", 8.0f);
      // Set the MVP Matrix for our object
      // Send it into our shader
      myShader.setUniformMatrix4fv("model", &worldTransform.getInternalMatrix()[0][0]);
      myShader.setUniformMatrix4fv("view", &camera->getWorldToViewmatrix()[0][0]);
      myShader.setUniformMatrix4fv("projection", &projectionMatrix[0][0]);
      myShader.setUniform3f("viewPos", camera->getEyeXPosition(),
                                        camera->getEyeYPosition(),
                                        camera->getEyeZPosition());
      myShader.setUniform1i("cubeID", ID);

      for(int i = 0; i < lights->getLights()->size(); i++) {
        lights->setShaderPointLights(i, &myShader);
      }

      lights->setShaderDirectional(&myShader);

    for(int i = 0; i < children.size(); ++i){
      children[i]->Update(projectionMatrix, camera);
    }
  }
}


// Update simply updates the current nodes
void SceneNode::Update(glm::mat4 projectionMatrix, Camera* camera, int lookID, int target){
  if(object!=nullptr) {
    if(parent) {
      worldTransform = parent->worldTransform*localTransform;
    } else {
      worldTransform = localTransform;
    }
    // Shader for scene
    myShader.Bind();
      // Set the uniforms in our current shader
      myShader.setUniform1i("material.diffuse", 0);
      myShader.setUniform1i("material.specular", 1);
      myShader.setUniform1f("material.shininess", 8.0f);
      // Set the MVP Matrix for our object
      // Send it into our shader
      myShader.setUniformMatrix4fv("model", &worldTransform.getInternalMatrix()[0][0]);
      myShader.setUniformMatrix4fv("view", &camera->getWorldToViewmatrix()[0][0]);
      myShader.setUniformMatrix4fv("projection", &projectionMatrix[0][0]);
      myShader.setUniform3f("viewPos", camera->getEyeXPosition(),
                                        camera->getEyeYPosition(),
                                        camera->getEyeZPosition());
      myShader.setUniform1i("cubeID", ID);
      scaleIntensity(lookID, target);
      myShader.setUniform3f("intensity", intensity.x, intensity.y, intensity.z);
      int colorMod = (lookID == ID) ? 1 : 0;
      myShader.setUniform1i("colorMod", colorMod);
      // Determine if removing cube
      // int eliminate = 0;
      // if(intensity.y > 0.8) eliminate = 1;
      myShader.setUniform1i("eliminate", gone);
      scaleFade();
      myShader.setUniform1f("fade", fade);

      // Lighting
      // for(int i = 0; i < lights->getLights()->size(); i++) {
      // 	lights->setShaderPointLights(i, &myShader);
      // }
      lights->setShaderDirectional(&myShader);
    // Shader for camera picking
    pickShader.Bind();
      // Set the uniforms in our current shader
      pickShader.setUniform1i("material.diffuse", 0);
      pickShader.setUniform1i("material.specular", 1);
      pickShader.setUniform1f("material.shininess", 8.0f);
      // Set the MVP Matrix for our object
      // Send it into our shader
      pickShader.setUniformMatrix4fv("model", &worldTransform.getInternalMatrix()[0][0]);
      pickShader.setUniformMatrix4fv("view", &camera->getWorldToViewmatrix()[0][0]);
      pickShader.setUniformMatrix4fv("projection", &projectionMatrix[0][0]);
      pickShader.setUniform3f("viewPos", camera->getEyeXPosition(),
                                        camera->getEyeYPosition(),
                                        camera->getEyeZPosition());
      pickShader.setUniform1i("cubeID", ID);
      // Lights
      lights->setShaderDirectional(&pickShader);
    // Shader for if this is the skybox
    skyShader.Bind();
      skyShader.setUniform1i("material.diffuse", 0);
      skyShader.setUniformMatrix4fv("view", &camera->getWorldToViewmatrix()[0][0]);
      skyShader.setUniformMatrix4fv("projection", &projectionMatrix[0][0]);
      // Lights
      // for(int i = 0; i < lights->getLights()->size(); i++) {
      // 	lights->setShaderPointLights(i, &pickShader);
      // }
      lights->setShaderDirectional(&skyShader);
    // Update children
    for(int i = 0; i < children.size(); ++i){
      children[i]->Update(projectionMatrix, camera, lookID, target);
    }
  }
}


// Returns the actual local transform stored in our SceneNode
// which can then be modified
Transform& SceneNode::getLocalTransform(){
    return localTransform;
}


// Returns the worled  transform stored in our SceneNode
// which can then be modified
Transform& SceneNode::getWorldTransform(){
    return worldTransform;
}


// Scales the color if being looked at
void SceneNode::scaleIntensity(int lookID, int target) {
  // if the color is above threshold
  // if green all the way, mark as removed
  if(intensity.y >= 0.8f) {gone = 1; return;}
  // If red all the way, mark as a failure
  if(intensity.x >= 0.8f) {wrong = 1; return;}
  // otherwise, as long as we're not looking at the skybox:
  if(lookID == ID && !(lookID == 54)) {
    if(target == ID) {
      if (intensity.y < 0.8f) {intensity.y += 0.02; intensity.z += 0.01;}
    } else {
      switch(difficulty) {
        case 1:
          if (intensity.x < 0.8f) intensity.x += 0.02;
          break;
        case 2:
          if (intensity.x < 0.8f) intensity.x += 0.028;
          break;
        case 3:
          if (intensity.x < 0.8f) intensity.x += 0.034;
          break;
        case 4:
          if (intensity.x < 0.8f) intensity.x += 0.039;
          break;
        case 5:
          if (intensity.x < 0.8f) intensity.x += 0.044;
          break;
      }
    }
  } else {
      if (intensity.y > 0.003f) {intensity.y -= 0.003; intensity.z -= 0.0015;}
      switch(difficulty) {
        case 1:
          if (intensity.x > 0.003f) intensity.x -= 0.006;
          break;
        case 2:
          if (intensity.x > 0.003f) intensity.x -= 0.004;
          break;
        case 3:
          if (intensity.x > 0.003f) intensity.x -= 0.003;
          break;
        case 4:
          if (intensity.x > 0.003f) intensity.x -= 0.0025;
          break;
        case 5:
          if (intensity.x > 0.003f) intensity.x -= 0.0022;
          break;
      }
  }
}


// Scale our fade float if we've locked in the a finished cube
void SceneNode::scaleFade() {
  if(intensity.y > 0.8f && fade < 1.6f) fade += 0.03;
}


void SceneNode::nodeReset() {
  intensity = glm::vec3(0.0f, 0.0f, 0.0f);
  fade = 0.0f;
  gone = 0;
  wrong = 0;
  difficulty = 1;
}

// Setter for difficulty 
void SceneNode::addDifficulty(int upOrDown) {
  if(upOrDown > 0) difficulty++;
  else difficulty--;
}

int SceneNode::getDifficulty() {
  return difficulty;
}