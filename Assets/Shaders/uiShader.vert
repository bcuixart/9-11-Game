#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 uv;

out vec3 vColor;
out vec2 vUV;

uniform mat4 TG;
uniform mat4 PM;
uniform mat4 VM;

void main()  
{
    vUV = uv;
    vColor = color;
    
        gl_Position = TG * vec4 (vertex, 1.0);
}