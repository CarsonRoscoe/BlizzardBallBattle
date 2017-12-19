#include "SpriteRenderer.h"
#include "SpriteRendererManager.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject) : Renderer(gameObject) {
  SpriteRendererManager::GetInstance()->AddSpriteForRendering(this); //.subscribe(gameObject.id, this); NOTE: Not subscribing/unsubscribing for now
  activeShader = Shader::GetShader();
}

void SpriteRenderer::Render() {
  glBindTexture(GL_TEXTURE_2D, textureBufferID);
  glDrawArrays(GL_QUADS, 0, 4);
}

void SpriteRenderer::SetActiveShader(Shader* shader) {
  activeShader = shader;
}

Shader* SpriteRenderer::GetShader() {
  return activeShader;
}

void SpriteRenderer::SetActiveSprite(ISprite* sprite) {
  activeSprite = sprite;
}

ISprite* SpriteRenderer::GetSprite() {
  return activeSprite;
}

SpriteRenderer::~SpriteRenderer() {
  SpriteRendererManager::GetInstance()->RemoveSpriteFromRendering(this);
}
