/**
 * This is also sad that I wrote this up then didn't really use it
*/

#include "Light.h"


// Constructor for a light. Need to input all the necessary values
Light::Light(glm::vec3 pos,
             glm::vec3 amb,
             glm::vec3 diff,
             glm::vec3 spec,
             float constant,
             float linear,
             float quadratic) {
  setPosition(pos);
  setAmbient(amb);
  setDiffuse(diff);
  setSpecular(spec);
  setConstant(constant);
  setLinear(linear);
  setQuadratic(quadratic);

}


// Setters and Getters
void Light::setPosition(glm::vec3 pos) {
  position = pos;
}

void Light::setAmbient(glm::vec3 amb) {
  ambient = amb;
}

void Light::setDiffuse(glm::vec3 diff) {
  diffuse = diff;
}

void Light::setSpecular(glm::vec3 spec) {
  specular = spec;
}

void Light::setConstant(float con) {
  constant = con;
}

void Light::setLinear(float lin) {
  linear = lin;
}

void Light::setQuadratic(float quad) {
  quadratic = quad;
}

glm::vec3 Light::getPosition() {
  return position;
}

glm::vec3 Light::getAmbient() {
  return ambient;
}

glm::vec3 Light::getDiffuse() {
  return diffuse;
}

glm::vec3 Light::getSpecular() {
  return specular;
}

float Light::getConstant() {
  return constant;
}

float Light::getLinear() {
  return linear;
}

float Light::getQuadratic() {
  return quadratic;
}
