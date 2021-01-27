/**
 * This is sad because I wrote this up, then didn't really use point lights.
 * Was a nice exercise to abstract light management away though
*/

#include "LightManager.h"


// Constructor takes an abient value between 0 and 10 for directional light
LightManager::LightManager(int amb) {
    if (amb < 0) amb = 0;
    if (amb > 10) amb = 10;
    // Set directional light direction
    direction = glm::vec3(-0.2f, -1.0f, -0.2f);
    // Set ambient light intensity
    ambient = glm::vec3(amb/10.0f, amb/10.0f, amb/10.0f);
    std::cout << "Ambient fs: " << amb/10.0f << std::endl;
    diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    specular = glm::vec3(1.0f, 1.0f, 1.0f);
}


// Add a pointlight to the scene
void LightManager::addLight(Light* light) {
  pointLights.push_back(light);
}


// Set the input shader for directional light
void LightManager::setShaderDirectional(Shader* shader) {
  shader->setUniform3f("dirLight.direction", direction.x, direction.y, direction.z);
  shader->setUniform3f("dirLight.ambient", ambient.x, ambient.y, ambient.z);
  shader->setUniform3f("dirLight.diffuse", diffuse.x, diffuse.y, diffuse.z);
  shader->setUniform3f("dirLight.specular", specular.x, specular.y, specular.z);
}


// Set the input shader for point lights
void LightManager::setShaderPointLights(int lightID, Shader* shader) {
  shader->setUniform3f(std::string("pointLights[" + std::to_string(lightID) + "].position").c_str(),
                      pointLights[lightID]->getPosition().x,
                      pointLights[lightID]->getPosition().y,
                      pointLights[lightID]->getPosition().z);
  shader->setUniform3f(std::string("pointLights[" + std::to_string(lightID) + "].ambient").c_str(),
                      pointLights[lightID]->getAmbient().x,
                      pointLights[lightID]->getAmbient().y,
                      pointLights[lightID]->getAmbient().z);
  shader->setUniform3f(std::string("pointLights[" + std::to_string(lightID) + "].diffuse").c_str(),
                      pointLights[lightID]->getDiffuse().x,
                      pointLights[lightID]->getDiffuse().y,
                      pointLights[lightID]->getDiffuse().z);
  shader->setUniform3f(std::string("pointLights[" + std::to_string(lightID) + "].specular").c_str(),
                      pointLights[lightID]->getSpecular().x,
                      pointLights[lightID]->getSpecular().y,
                      pointLights[lightID]->getSpecular().z);
  shader->setUniform1f(std::string("pointLights[" + std::to_string(lightID) + "].constant").c_str(),
                      pointLights[lightID]->getConstant());
  shader->setUniform1f(std::string("pointLights[" + std::to_string(lightID) + "].linear").c_str(),
                      pointLights[lightID]->getLinear());
  shader->setUniform1f(std::string("pointLights[" + std::to_string(lightID) + "].quadratic").c_str(),
                      pointLights[lightID]->getQuadratic());
}


// Get the pointlights
std::vector<Light*>* LightManager::getLights() {
  return &pointLights;
}