#version 460 core

in vec3 vWorldPos;
in vec3 vNormal;
in vec2 vUv;

uniform sampler2D uAlbedo;
uniform vec3 uLightDir;
uniform vec3 uLightColor;
uniform vec3 uViewPos;

out vec4 FragColor;

void main()
{
    vec3 albedo = texture(uAlbedo, vUv).rgb;
    vec3 n = normalize(vNormal);
    vec3 l = normalize(-uLightDir);
    vec3 v = normalize(uViewPos - vWorldPos);
    vec3 h = normalize(l + v);

    float diff = max(dot(n, l), 0.0);
    float spec = pow(max(dot(n, h), 0.0), 32.0);

    vec3 ambient = 0.18 * albedo;
    vec3 color = ambient + albedo * diff * uLightColor + spec * uLightColor * 0.25;
    FragColor = vec4(color, 1.0);
}
