#version 330 core

in vec2 vUV;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 fragNormal;

uniform sampler2D screenTexture;
uniform sampler2D depthTexture;
uniform sampler2D normalTexture;

uniform int frameCount;
uniform int seedChange = 12;

uniform float outlineThickness = 1.0;
uniform float outlineSensitivity = 1.0;
uniform float crayonEffect = 0.5;

float rand(vec2 co) {
    float seedVariation = float(frameCount / seedChange);
    return fract(sin(dot(co + seedVariation, vec2(12.9898, 78.233))) * 43758.5453);
}

float getEdgeFactor(vec2 uv, float thickness, float sensitivity) {
    // Obtenim la profunditat i normals dels píxels veïns
    float depth = texture(depthTexture, uv).r;
    vec3 normal = texture(normalTexture, uv).rgb;
    
    // Mostrejem els veïns
    vec2 pixelSize = 1.0 / textureSize(depthTexture, 0);
    float depthDiff = 0.0;
    vec3 normalDiff = vec3(0.0);
    
    // Comprovem els 8 veïns (podries ajustar el thickness variant aquest nombre)
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue;
            
            vec2 offset = vec2(x, y) * pixelSize * thickness;
            float neighborDepth = texture(depthTexture, uv + offset).r;
            vec3 neighborNormal = texture(normalTexture, uv + offset).rgb;
            
            depthDiff += abs(neighborDepth - depth);
            normalDiff += abs(neighborNormal - normal);
        }
    }
    
    // Combinem diferències de profunditat i normals
    float edge = (depthDiff * 2.0 + length(normalDiff)) * sensitivity;
    return clamp(edge, 0.0, 1.0);
}

void main() 
{
    float frameSeed = float(frameCount / seedChange);

    // Primer apliquem el jitter al sampleig de la textura original
    vec2 jitter = vec2(rand(vUV + frameSeed), rand(vUV + 0.5 + frameSeed)) * 0.005;
    vec4 texColor = texture(screenTexture, vUV + jitter);
    
    // Efecte de taques blanques
    float noise = rand(vUV * 20.0 + frameSeed);
    float taca = smoothstep(0.4, 0.0, noise) * crayonEffect;
    
    // Apliquem les taques al color amb jitter
    vec3 colorAmbTaques = vec3(
        texColor.r + (1.0 - texColor.r) * taca,
        texColor.g + (1.0 - texColor.g) * taca,
        texColor.b + (1.0 - texColor.b) * taca
    );
    
    // Detecció de contorns
    float edge = getEdgeFactor(vUV, outlineThickness, outlineSensitivity);
    edge *= smoothstep(0.3, 0.7, rand(vUV * 50.0 + frameSeed));
    
    // Apliquem l'outline al resultat combinat
    fragColor = vec4(mix(colorAmbTaques, vec3(0.0), edge), 1.0);
}