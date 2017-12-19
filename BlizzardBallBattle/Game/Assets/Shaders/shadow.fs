#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform float shadowStrength;

void main( ) {
    color = texture(ourTexture1, TexCoord) / shadowStrength;
}