#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D fboTexture;

void main( ) {
    color = texture(fboTexture, TexCoord);
}