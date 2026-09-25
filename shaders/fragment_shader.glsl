#version 460 core

in vec3 vFragPos;
in vec3 vNormal;
in vec2 vTexCoords;
in vec4 vFragPosLightSpace;

out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Light uLights[4];
uniform int uNumLights;
uniform Material uMaterial;
uniform vec3 uViewPos;
uniform bool uUseShadow;
uniform sampler2D uShadowMap;
uniform vec3 uFogColor;
uniform float uFogDensity;
uniform bool uUseFog;
uniform bool uUseLighting;
uniform bool uUseTexture;

float calculateShadow(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    if (!uUseShadow) return 0.0;
    
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    
    if (projCoords.z > 1.0) return 0.0;
    
    float closestDepth = texture(uShadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float bias = max(0.005 * (1.0 - dot(normal, lightDir)), 0.0005);
    
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(1024.0, 1024.0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(uShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    return shadow;
}

vec3 calculateLightContribution(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    
    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, vTexCoords));
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * vec3(texture(uMaterial.diffuse, vTexCoords));
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = spec * light.specular * vec3(texture(uMaterial.specular, vTexCoords));
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    float shadowFactor = 1.0 - shadow;
    
    return (ambient + (diffuse + specular) * shadowFactor);
}

float calculateFog(float fogDistance)
{
    if (!uUseFog) return 0.0;
    float fogFactor = 1.0 - exp(-uFogDensity * fogDistance);
    return clamp(fogFactor, 0.0, 1.0);
}

void main()
{
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(uViewPos - vFragPos);
    
    vec3 result = vec3(0.0);
    
    if (uUseLighting) {
        float shadow = calculateShadow(vFragPosLightSpace, norm, normalize(uLights[0].position - vFragPos));
        
        for (int i = 0; i < uNumLights && i < 4; ++i) {
            result += calculateLightContribution(uLights[i], norm, vFragPos, viewDir, shadow);
        }
    } else {
        result = vec3(texture(uMaterial.diffuse, vTexCoords));
    }
    
    float fogDistance = length(vFragPos - uViewPos);
    float fogFactor = calculateFog(fogDistance);
    result = mix(result, uFogColor, fogFactor * float(uUseFog));
    
    FragColor = vec4(result, 1.0);
}