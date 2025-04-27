#version 330 core

in vec3 vColor;
in vec2 vUV;
in vec3 fragPosWorld; 

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 fragNormal;

uniform sampler2D textureSampler;

uniform vec3 cameraPos;
uniform float fogStart = 20.0;
uniform float fogEnd = 1000.0;
uniform vec3 fogColor = vec3(0.5, 0.7, 1.0);

void main() {
    vec4 texColor = texture(textureSampler, vUV);

    float distance = length(fragPosWorld - cameraPos);
    float fogFactor = clamp((fogEnd - distance) / (fogEnd - fogStart), 0.0, 1.0);

    vec3 finalColor = mix(fogColor, texColor.rgb, fogFactor);
    fragColor = vec4(finalColor, texColor.a);
}