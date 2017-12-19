#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D fboTexture;
uniform sampler2D highlightTexture;
uniform float bloomIntensity;

void main( ) {
    vec4 sceneColor = texture(fboTexture, TexCoord);
    vec4 highlightColor = texture(highlightTexture, TexCoord);
    color = sceneColor + highlightColor * bloomIntensity;
}