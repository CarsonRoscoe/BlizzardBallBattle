#version 410 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 transform;
uniform float aspectRatio;

void main() {
	vec4 pos = transform * vec4(position, 1.0);
	pos.y *= aspectRatio;
	gl_Position = pos;
	TexCoord = vec2(texCoord.x, texCoord.y);
}
