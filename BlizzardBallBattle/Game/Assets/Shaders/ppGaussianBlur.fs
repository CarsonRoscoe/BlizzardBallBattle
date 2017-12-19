#version 410 core

out vec4 color;
in vec2 blueTextureCoordinates[11];

uniform sampler2D fboTexture;

void main( ) {
    color = vec4(0.0);
    color += texture(fboTexture, blueTextureCoordinates[0]) * 0.0093;
    color += texture(fboTexture, blueTextureCoordinates[1]) * 0.028002;
    color += texture(fboTexture, blueTextureCoordinates[2]) * 0.065984;
    color += texture(fboTexture, blueTextureCoordinates[3]) * 0.121703;
    color += texture(fboTexture, blueTextureCoordinates[4]) * 0.175713;
    color += texture(fboTexture, blueTextureCoordinates[5]) * 0.198596;
    color += texture(fboTexture, blueTextureCoordinates[6]) * 0.175713;
    color += texture(fboTexture, blueTextureCoordinates[7]) * 0.121703;
    color += texture(fboTexture, blueTextureCoordinates[8]) * 0.065984;
    color += texture(fboTexture, blueTextureCoordinates[9]) * 0.028002;
    color += texture(fboTexture, blueTextureCoordinates[10]) * 0.0093;
}