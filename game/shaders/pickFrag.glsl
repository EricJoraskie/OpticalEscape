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

#define NR_POINT_LIGHTS 46

// ======================= uniform ====================

uniform int cubeID;

void main() {
    vec3 Lighting = vec3(cubeID/255.0f, 0.0f, 0.0f);
    if(gl_FrontFacing){
        FragColor = vec4( Lighting,1.0);
    }else{
        // Additionally color the back side the same color
         FragColor = vec4( Lighting,1.0);
    }
}
// ==================================================================
