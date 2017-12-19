#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;

void main( ) {
    //0.2543 == 0.25
    float pixelation = 250.0f; //Lower = more pixels, higher = finer detail
    float newX = floor(TexCoord.x * pixelation) / pixelation;
    float newY = floor(TexCoord.y * pixelation) / pixelation;
    vec2 voxelTexCoord = vec2(newX, newY);
    color = texture(ourTexture1, voxelTexCoord);
}