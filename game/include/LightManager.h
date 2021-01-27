#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <vector>
#include "Light.h"
#include "Shader.h"
#include "glm/glm.hpp"

class LightManager{
public:
    // Constructor
    LightManager(int ambientInt);

    void addLight(Light* light);

    void setShaderDirectional(Shader* shader);

    void setShaderPointLights(int lightID, Shader* shader);

    std::vector<Light*>* getLights();

private:
    std::vector<Light*> pointLights;

    glm::vec3 direction;

    glm::vec3 ambient;

    glm::vec3 diffuse;

    glm::vec3 specular;
};

#endif