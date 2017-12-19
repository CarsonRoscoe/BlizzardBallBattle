#version 410 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 texCoord;

out vec2 TexCoord;
out float brightnessFactor;

uniform vec2 bloomDirection;

//Vt: 0.5/0.5   Tx: 1.0/1.0 //Top Right
//Vt: 0.5/-0.5  Tx: 1.0/0.0 //Bottom Right
//Vt: -0.5/-0.5 Tx: 0.0/0.0 //Bottom Left
//Vt: -0.5/0.5  Tx: 0.0/1.0 //Top Left

//TR =  1.0 /  1.0
//BR =  1.0 / -1.0
//BL = -1.0 / -1.0
//TL = -1.0 /  1.0

void main() {
	gl_Position = vec4(position.x * 2.0, position.y * 2.0, position.z, 1.0);
	TexCoord = vec2(texCoord.x, texCoord.y);

    vec2 ourPos = normalize(position.xy);
    vec2 bloomDir = normalize(bloomDirection);

    brightnessFactor = 1.0 - distance(ourPos, bloomDir) / 2.5;
}