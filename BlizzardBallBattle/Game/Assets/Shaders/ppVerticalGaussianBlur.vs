#version 410 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 texCoord;

out vec2 blueTextureCoordinates[11];

void main() {
	gl_Position = vec4(position.x * 2.0, position.y * 2.0, position.z, 1.0);
    vec2 centerTexCoords = position.xy * 0.5 + 0.5;
    float pixelSize = 1.0 / 768.0;

    for(int i = -5; i <= 5; i++) {
        blueTextureCoordinates[i+5] = centerTexCoords + vec2(0.0, pixelSize * i);
    }
}