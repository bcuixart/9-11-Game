#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;

out vec3 vColor;
out vec2 vUV;

uniform mat4 TG;
uniform mat4 PM;
uniform mat4 VM;

uniform vec3 bend;

void main()  {
    if (vertex.y >= 25 && vertex.y <= 35) {
        gl_Position = PM * VM * TG * vec4 (vertex + bend, 1.0);
    } else {
        gl_Position = PM * VM * TG * vec4 (vertex, 1.0);
    }

    vColor = color;
    //vUV = vec2(0.0805555556, 1); // NEGRE
    vUV = uv;

    //vUV = vec2(vertex.x / 6, vertex.y / 30);
}
