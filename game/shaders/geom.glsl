#version 330 core


layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

// Export our normal data, and read it into our frag shader
in vec3 myNormal[];
// Export our Fragment Position computed in world space
in vec3 FragPos[];
// If we have texture coordinates we can now use this as well
in vec2 v_texCoord[];

out vec3 myNormals; // Import our normal data
out vec2 v_texCoords; // Import our texture coordinates from vertex shader
out vec3 FragPoss; // Import the fragment position

uniform int eliminate;
uniform float fade;



vec3 calcEliminate(int i, int place) {
    vec3 a;
    vec3 b;
    switch(place) {
        case 0:
            a = vec3(gl_in[i+1].gl_Position) - vec3(gl_in[i].gl_Position);
            b = vec3(gl_in[i+2].gl_Position) - vec3(gl_in[i].gl_Position);
            return (b+a)/4;
            break;
        case 1:
            a = vec3(gl_in[i-1].gl_Position) - vec3(gl_in[i].gl_Position);
            b = vec3(gl_in[i+1].gl_Position) - vec3(gl_in[i].gl_Position);
            return (b+a)/4;
            break;
        case 2:
            a = vec3(gl_in[i-1].gl_Position) - vec3(gl_in[i].gl_Position);
            b = vec3(gl_in[i-2].gl_Position) - vec3(gl_in[i].gl_Position);
            return (b+a)/4;
            break;
    }
}


vec4 disappear(vec4 position) {
    return position*0;
}


void main() {

    if(eliminate == 0) {
        for( int i = 0; i < gl_in.length(); ++i ) {
            myNormals = myNormal[i];
            v_texCoords = v_texCoord[i];
            FragPoss = FragPos[i];
            gl_Position = gl_in[i].gl_Position;
            EmitVertex();
        }
        EndPrimitive();
    } else if(eliminate == 1 && fade < 1.3) {
        vec3 eliminate;
        for( int i = 0; i < gl_in.length(); ++i ) {
            eliminate = calcEliminate(i, i%3);
            myNormals = myNormal[i];
            v_texCoords = v_texCoord[i];
            FragPoss = FragPos[i];
            gl_Position =  gl_in[i].gl_Position+vec4((eliminate*fade), 0.0);
            EmitVertex();
        }
        EndPrimitive();
    } else {
        vec3 eliminate;
        for( int i = 0; i < gl_in.length(); ++i ) {
            eliminate = calcEliminate(i, i%3);
            myNormals = myNormal[i];
            v_texCoords = v_texCoord[i];
            FragPoss = FragPos[i];
            gl_Position = disappear(gl_in[i].gl_Position+vec4((eliminate*fade), 0.0));
            EmitVertex();
        }
        EndPrimitive();
    }
    
}  