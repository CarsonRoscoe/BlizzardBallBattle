#version 410 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 texCoord;

out vec2 TexCoord;

void main() {
	gl_Position = vec4(position.x * 2.0, position.y * 2.0, position.z, 1.0);
	TexCoord = vec2(texCoord.x, texCoord.y);
}