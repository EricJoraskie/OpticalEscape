// ====================================================
#version 330 core

// ======================= IN =========================
in vec3 myNormals; // Import our normal data
in vec2 v_texCoords; // Import our texture coordinates from vertex shader
in vec3 FragPoss; // Import the fragment position

// ======================= out ========================
// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

// ======================= Globals ====================
// We will have another constant for specular strength
float specularStrength = 0.5f;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};


struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Our light source data structure
struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 46

// ======================= uniform ====================

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;

uniform mat4 view;
uniform vec3 viewPos;

uniform vec3 intensity;
uniform int colorMod;

// =====================================================

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 fragColor = texture(material.diffuse, v_texCoords).rgb;;
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * fragColor;
    vec3 diffuse = light.diffuse * diff * fragColor;
    vec3 specular = light.specular * spec * fragColor;
    return (ambient); // + diffuse + specular);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 fragColor = texture(material.diffuse, v_texCoords).rgb;;

    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * fragColor;
    vec3 diffuse = light.diffuse * diff * fragColor;
    vec3 specular = light.specular * spec * fragColor;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular)*10;
}


void main()
{
    vec3 norm = normalize(myNormals);
    vec3 viewDir = normalize(viewPos - FragPoss);
    vec3 Lighting = CalcDirLight(dirLight, norm, viewDir);
    Lighting += intensity;

    if(gl_FrontFacing){
        FragColor = vec4( Lighting,1.0);
    }else{
        // Additionally color the back side the same color
         FragColor = vec4( Lighting,1.0);
    }
}
// ==================================================================
