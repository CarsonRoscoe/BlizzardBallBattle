#pragma once

#include "GLHeaders.h"
#include "SharedConstants.h"

class FrameBufferObject {
private:
	int width;
	int height;

	GLuint frameBuffer;
	GLuint texture;
	
public:
	FrameBufferObject(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);
	void cleanUp();
	void bindFrameBuffer();
	void unbindFrameBuffer();
	void bindToRead();
	GLuint getTexture();
	void createFrameBuffer();
	void createTextureAttachment();
	void init();
	//void createDepthTextureAttachment();
	//void createDepthBufferAttachment();
};
