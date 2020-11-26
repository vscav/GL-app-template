#version 300 es

precision mediump float;

out vec4 fFragColor;

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform vec3 uCameraPosition;

void main()
{
    vec3 sunPos = vec3(1.2, 1.0, 2.0);
    vec3 sunColor = vec3(1.0, 1.0, 1.0);
    vec3 objectColor = vec3(1.0, 0.5, 0.3);

    // Ambient
    float ambientStrength = 0.05;
    vec3 ambient = ambientStrength * sunColor;
    
    // Diffuse
    vec3 norm = normalize(vNormal_vs);
    vec3 sunDir = normalize(sunPos - vPosition_vs);
    float diff = max(dot(norm, sunDir), 0.0);
    vec3 diffuse = diff * sunColor;
    
    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(uCameraPosition - vPosition_vs);
    vec3 reflectDir = reflect(-sunDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * sunColor;
    
    vec3 res = (ambient + diffuse + specular) * objectColor;
    fFragColor = vec4(res, 1.0);
}