#version 300 es

precision mediump float;

in vec3 vTexCoords;

uniform samplerCube skybox;

out vec4 fColor;

void main()
{
    fColor = texture(skybox, vTexCoords);
}