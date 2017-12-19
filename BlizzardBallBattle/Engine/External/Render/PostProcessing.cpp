// #include "PostProcessing.h"

// static void PostProcessing::start(){
// 	glBindVertexArray(quad.getVaoID());
// 	glEnableVertexAttribArray(0);
// 	glDisable(GL_DEPTH_TEST);
// }

// static void PostProcessing::end(){
// 	glEnable(GL_DEPTH_TEST);
// 	glDisableVertexAttribArray(0);
// 	glBindVertexArray(0);
// }
// static void PostProcessing::init(Loader loader){
// 	quad = loader.loadToVAO(POSITIONS, 2);
// }

// static void PostProcessing::doPostProcessing(int colourTexture){
// 	start();
	
// 	end();
// }

// static void PostProcessing::cleanUp(){
// }