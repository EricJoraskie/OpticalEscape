// ====================================================
#version 330 core

// ======================= uniform ====================
// If we have texture coordinates, they are stored in this sampler.
uniform sampler2D u_DiffuseMap;
uniform int filter;

// ======================= IN =========================
in vec2 v_texCoord; // Import our texture coordinates from vertex shader

// ======================= out ========================
// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

// ====================== constants ===================
const float offset = 1.0 / 300.0;

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset),
        vec2(   0.0f,  offset),
        vec2( offset,  offset),
        vec2(-offset,  0.0f),
        vec2(   0.0f,  0.0f),
        vec2( offset,  0.0f),
        vec2(-offset,  -offset),
        vec2(   0.0f,  -offset),
        vec2( offset,  -offset)
    );

    float kernel[9];
    float kernel2[9];
    float kernel3[9];

    kernel = float[](
        0, 0, 0,
        0, 1, 0,
        0, 0, 0
    );

    kernel2 = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    kernel3 = float[](
        1,  1,  1,
        1, -8,  1,
        1,  1,  1
    );

    vec3 buildTexture[9];
    for(int i = 0; i < 9; i++) {
        buildTexture[i] = vec3(texture(u_DiffuseMap, v_texCoord + offsets[i]));
    }
    vec3 finalCol = vec3(0.0);
    for(int i = 0; i < 9; i++) {
        if(buildTexture[4].y > 0.7f && buildTexture[i].x < 0.1f) finalCol += buildTexture[i] * kernel2[i];
        if(buildTexture[4].y > 0.8f && buildTexture[i].x < 0.1f) finalCol -= vec3(0.2, 0.2, 0.2);
        else {
            if(buildTexture[4].x > 0.8f) { finalCol += buildTexture[i] * kernel3[i]; finalCol += vec3(0.005, 0.0, 0.0);}
            else finalCol += buildTexture[i] * kernel[i];
        }
    }
    
    FragColor = vec4(finalCol ,1.0);
}
// ==================================================================
