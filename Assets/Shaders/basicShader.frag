#version 330 core

in vec3 vColor;
in vec2 vUV;
in vec3 fogPos;

out vec4 fragColor;

uniform sampler2D textureSampler;

uniform float fogMaxDistance = 1000.0;
uniform vec3 fogColor = vec3(0.5, 0.7, 1.0);

void main() {
    vec4 texColor = texture(textureSampler, vUV);

    // Distància radial (2D, només en x i z)
    float distanceFromCenter = length(fogPos.xz);
    float fogFactor = clamp(1.0 - distanceFromCenter / fogMaxDistance, 0.0, 1.0);

    vec3 finalColor = mix(fogColor, texColor.rgb, fogFactor);
    fragColor = vec4(finalColor, texColor.a);
}