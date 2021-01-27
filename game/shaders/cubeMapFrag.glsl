
#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

struct Material {
    samplerCube diffuse;
};

uniform Material material;


void main()
{    
    FragColor = texture(material.diffuse, TexCoords);
}