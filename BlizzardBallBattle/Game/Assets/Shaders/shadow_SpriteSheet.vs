#version 410 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 transform;
uniform float aspectRatio;
uniform vec2 lightPoint;
uniform ivec3 texData; //columnCount, rowCount, index

void main() {
	vec4 pos = transform * vec4(position, 1.0);
	pos.y *= aspectRatio;

    //WORKING: OLD VERSION
    vec4 dif = pos - vec4(lightPoint, 0.0, 0.0);
	gl_Position = pos + dif / 20.0;
    //

	//Current row/column in the spritesheet
	vec2 currentPos = vec2(texData.z % texData.x, texData.z / texData.x);

	//Must flip texCoord.y 
	TexCoord = (currentPos + vec2(texCoord.x, 1.0 - texCoord.y)) / vec2(texData.x, texData.y);
}

