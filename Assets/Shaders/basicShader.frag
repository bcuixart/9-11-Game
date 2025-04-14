#version 330 core

in vec3 vColor;
in vec2 vUV;

out vec4 fragColor;

uniform sampler2D textureSampler;

void main() {
    vec4 texColor = texture(textureSampler, vUV);
    fragColor = texColor * vec4(vUV, 0, 1.0);

    //fragColor = vec4(vUV, 0.0, 1.0); // Mostra les UVs com a color

    fragColor = texture(textureSampler, vUV);

}