#version 330 core

in vec3 vColor;
in vec2 vUV;
in vec3 fragPosWorld; 

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 fragNormal;

uniform sampler2D textureSampler;

void main() {
    vec4 texColor = texture(textureSampler, vUV);

    fragColor = texColor;
}