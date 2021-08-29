#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

flat out int MaterialID;
out vec3 geomNormal;

uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;
uniform mat4 modelMatrix;

void main() {    

    // Calculate Material
    if (gl_in[0].gl_Position.x == gl_in[1].gl_Position.x && gl_in[0].gl_Position.x == gl_in[2].gl_Position.x) {
        // X-Axis Material
        MaterialID = 0;
    } else if (gl_in[0].gl_Position.y == gl_in[1].gl_Position.y && gl_in[0].gl_Position.y == gl_in[2].gl_Position.y) {
        // Y-Axis Material
        MaterialID = 1;
    } else { 
        // Z-Axis Material
        MaterialID = 2;
    }

    // Calculate Normal
    vec3 u = (gl_in[1].gl_Position - gl_in[0].gl_Position).xyz;
    vec3 v = (gl_in[2].gl_Position - gl_in[0].gl_Position).xyz;

    vec3 Normal = normalize(cross(v, u));

    for(int i=0; i < gl_in.length(); ++i) 
    {
        gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * gl_in[i].gl_Position;
        geomNormal = Normal;
        EmitVertex();
    }

    EndPrimitive();
}  