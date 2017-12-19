#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;

void main( ) {
    color = texture(ourTexture1, TexCoord);
    color *= 1.25f;
    color.a = 0.35f;
}