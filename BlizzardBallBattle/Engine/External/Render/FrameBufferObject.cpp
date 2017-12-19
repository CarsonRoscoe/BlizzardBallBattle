#include "FrameBufferObject.h"

	/**
	 * Creates an FrameBufferObject of a specified width and height, with the desired type of
	 * depth buffer attachment.
	 * 
	 * @param width
	 *            - the width of the FrameBufferObject.
	 * @param height
	 *            - the height of the FrameBufferObject.
	 * @param depthBufferType
	 *            - an int indicating the type of depth buffer attachment that
	 *            this FrameBufferObject should use.
	 */
	FrameBufferObject::FrameBufferObject(int width, int height) {
		this->width = width;
		this->height = height;
	}

	void FrameBufferObject::init() {
		createFrameBuffer();
		createTextureAttachment();
		unbindFrameBuffer();
	}

	/**
	 * Deletes the frame buffer and its attachments when the game closes.
	 */
	void FrameBufferObject::cleanUp() {
		glDeleteFramebuffers(1, &frameBuffer);
		glDeleteTextures(1, &texture);
	}

	/**
	 * Binds the frame buffer, setting it as the current render target. Anything
	 * rendered after this will be rendered to this FrameBufferObject, and not to the screen.
	 */
	void FrameBufferObject::bindFrameBuffer() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
		glViewport(0, 0, width, height);
	}

	/**
	 * Unbinds the frame buffer, setting the default frame buffer as the current
	 * render target. Anything rendered after this will be rendered to the
	 * screen, and not this FrameBufferObject.
	 */
	void FrameBufferObject::unbindFrameBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	/**
	 * Binds the current FrameBufferObject to be read from (not used in tutorial 43).
	 */
	void FrameBufferObject::bindToRead() {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
	}

	/**
	 * @return The ID of the texture containing the colour buffer of the FrameBufferObject.
	 */
	GLuint FrameBufferObject::getTexture() {
		return texture;
	}

	/**
	 * Creates a new frame buffer object and sets the buffer to which drawing
	 * will occur - colour attachment 0. This is the attachment where the colour
	 * buffer texture is.
	 * 
	 */
	void FrameBufferObject::createFrameBuffer() {
		glGenFramebuffers(1, &frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}

	/**
	 * Creates a texture and sets it as the colour buffer attachment for this
	 * FrameBufferObject.
	 */
	void FrameBufferObject::createTextureAttachment() {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture,
				0);
	}

	/**
	 * Adds a depth buffer to the FrameBufferObject in the form of a texture, which can later
	 * be sampled.
	 */
	 /*void FrameBufferObject::createDepthTextureAttachment() {
		glGenTextures(1, &depthTexture);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT,
				GL_FLOAT, (ByteBuffer) null);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
	}*/

	/**
	 * Adds a depth buffer to the FrameBufferObject in the form of a render buffer. This can't
	 * be used for sampling in the shaders.
	 */
	/*void FrameBufferObject::createDepthBufferAttachment() {
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
				depthBuffer);
	}*/
