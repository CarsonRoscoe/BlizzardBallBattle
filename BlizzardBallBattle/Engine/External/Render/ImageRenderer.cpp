// #include "ImageRenderer.h"

// ImageRenderer::ImageRenderer(int width, int height) {
// 	this.fbo = new Fbo(width, height, Fbo.NONE);
// }

// ImageRenderer::ImageRenderer() {}

// void ImageRenderer::renderQuad() {
// 	if (fbo != null) {
// 		fbo.bindFrameBuffer();
// 	}
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
// 	if (fbo != null) {
// 		fbo.unbindFrameBuffer();
// 	}
// }

// int ImageRenderer::getOutputTexture() {
// 	return fbo.getColourTexture();
// }

// void ImageRenderer::cleanUp() {
// 	if (fbo != null) {
// 		fbo.cleanUp();
// 	}
// }