#version 410 core

in vec2 TexCoord;

out vec4 color;
in float brightnessFactor;

uniform sampler2D fboTexture;

void main( ) {
    vec4 origColor = texture(fboTexture, TexCoord);
    float brightness = (origColor.r * 0.2126) + (origColor.g * 0.7152) + (origColor.b * 0.0722);
    color = (origColor + brightness) * brightnessFactor;
}