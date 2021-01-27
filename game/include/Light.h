#ifndef LIGHT_H
#define LIGHT_H

#include "Transform.h"
#include "glm/glm.hpp"

class Light{
public:
	// Constructor
  Light(glm::vec3 pos,
        glm::vec3 amb,
        glm::vec3 diff,
        glm::vec3 spec,
        float constant,
        float linear,
        float quadratic);

  // Setters
  void setPosition(glm::vec3 position);

  void setAmbient(glm::vec3 ambient);

  void setDiffuse(glm::vec3 diffuse);

  void setSpecular(glm::vec3 specular);

  void setConstant(float constant);

  void setLinear(float linear);

  void setQuadratic(float quadratic);

  // Getters
  glm::vec3 getPosition();

  glm::vec3 getAmbient();

  glm::vec3 getDiffuse();

  glm::vec3 getSpecular();

  float getConstant();

  float getLinear();

  float getQuadratic();

private:

  glm::vec3 position;

  glm::vec3 ambient;

  glm::vec3 diffuse;

  glm::vec3 specular;

  float constant;

  float linear;

  float quadratic;


};

#endif