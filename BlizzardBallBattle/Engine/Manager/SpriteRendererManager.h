#pragma once

#include <map> ////
#include "GLHeaders.h"
#include <stdio.h>
#include <string>
#define GL3_PROTOTYPES 1
#include <iostream>
#include "SharedConstants.h"
#include <vector>
#include <array>
#include "SpriteRenderer.h"
#include "Transform.h"
#include <unordered_set>
#include <thread>
#include <mutex>
#include "FrameBufferObject.h"
#include "UserDefinedRenderLayers.h"

#define SHADER_TYPE_DEFAULT 0
#define SHADER_TYPE_PIXEL 1
#define SHADER_TYPE_SPRITESHEET 2

struct RenderingObject {
    ISprite* sprite;
    Transform* transform;
    SpriteRenderer* spriteRenderer;

	bool IsValid() {
		if (spriteRenderer == NULL || spriteRenderer == nullptr || transform == NULL || transform == nullptr) {
			return false;
		}
		return true;
	}
};

struct RenderingTextureCoordinateGroup {

};

struct RenderingShaderGroup {
    int shaderID;
    GLuint shaderProgram;
    std::vector<RenderingObject> children;
    ~RenderingShaderGroup() {
        children.clear();
    }
};

class SpriteRendererManager {
private:
    //Singleton variables
    static SpriteRendererManager *instance;
    std::vector<SpriteRenderer*> activeSprites;
    std::unordered_set<int> disabledLayers;
    std::thread renderingThread;
    std::mutex renderTalkingStick;
    std::mutex renderReadingStick;
    std::vector<RenderingShaderGroup> renderingGroups;
    bool renderingThreadIsAlive;
    bool rendering;
    FrameBufferObject fboPlainPass, fboHorizontalGaussianBlur, fboGaussianBlur, fboBloomBrightness, fboBloomBlurBrightness, fboAmbientLighting;

    //Rendering variables
    SDL_Window* mainWindow = NULL;
    SDL_GLContext glContext = NULL;
    std::array<GLfloat, 12> quadVertices;
    std::array<GLfloat, 8> textCoordinates;
    std::array<GLuint, 6> indices;
    GLuint VBO, VAO, EBO, CBO; //VertexBufferObject, VertexArrayObject, ElementsBufferObject, CoordinateBufferObject
    GLuint ppVAO;

    //Rendering methods
    bool SetOpenGLAttributes();
    void PrintSDL_GL_Attributes();
    void CheckSDLError(int line);
    void PrepareRenderingThread();


public:
    static SpriteRendererManager* GetInstance();

    //void Subscribe(int id, SpriteRenderer* spriteRenderer);
    //void UnSubscribe(int id);
    void OnUpdate(int ticks);

    SpriteRendererManager();
    bool Init();
    void Cleanup();
    void Render();
    GLuint GenerateTexture(std::string textureFileName);
    void AddSpriteForRendering(SpriteRenderer* sprite);
    
    void DisableRenderingLayer(int layer);
    void EnableRenderingLayer(int layer);
    void EnableAllRenderingLayers();
    bool IsRenderingLayerEnabled(int layer);
	void RemoveSpriteFromRendering(SpriteRenderer* sprite);
    void Purge();

    /////RENDERING METHODS: Maybe extract to a base "RenderContext" class to pass to the Camera
    void RenderShadowPass(float xSourceDirection, float ySourceDirection, float shadowStrength);
    void RenderPass(int layer = RENDER_LAYER_ALL, bool clearFirst = true);
    void RenderFBO(FrameBufferObject fboToRender, Shader* shader, FrameBufferObject* toFbo = nullptr); //Default "FBOShader" type assumes it takes a texture to draw

    void RenderGaussianBlur(FrameBufferObject fboToBlur, FrameBufferObject* toFbo = nullptr); //Blurs then draws
    void RenderBloom(FrameBufferObject fboToBloom, FrameBufferObject* toFbo = nullptr); //Takes input, extracts light, stores that, blurrs, stores that
    void RenderDirectionalBloom(FrameBufferObject fboToBloom, float xSourceDirection, float ySourceDirection, float bloomIntensity, FrameBufferObject* toFbo = nullptr); //Takes input, extracts light, stores that, blurrs, stores that
    void ApplyEndProcessing(FrameBufferObject mainTexture, FrameBufferObject postProcessingOverlay, FrameBufferObject* toFbo = nullptr);
    void RenderAmbientColor(FrameBufferObject fboToColor, float r, float g, float b, float a, FrameBufferObject* toFbo = nullptr);
    void RenderFullLighting(FrameBufferObject fboToEffect, FrameBufferObject bloomBlurredLight, FrameBufferObject shadow, FrameBufferObject moodLighting, FrameBufferObject* toFbo = nullptr);
};