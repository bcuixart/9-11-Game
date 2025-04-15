#version 330 core

in vec3 vColor;
in vec2 vUV;
in vec3 fragPosWorld; 

out vec4 fragColor;

uniform sampler2D textureSampler;

uniform vec3 cameraPos;
uniform float fogStart = 20.0;
uniform float fogEnd = 1000.0;
uniform vec3 fogColor = vec3(0.5, 0.7, 1.0);

void main() {
    vec4 texColor = texture(textureSampler, vUV);

    fragColor = texColor;
}