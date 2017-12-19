#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D fboTexture;
uniform vec4 ambientColor;

void main( ) {
    color = texture(fboTexture, TexCoord) * (1 - ambientColor.a) + vec4(ambientColor.xyz, 1.0f ) * (ambientColor.a);
}