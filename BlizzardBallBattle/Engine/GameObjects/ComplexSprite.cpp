#include "ComplexSprite.h"
#include "SpriteRendererManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "Shader.h"
#include "HelperFunctions.h"

ComplexSprite::ComplexSprite(ComplexSpriteinfo* info, float x, float y, float z, float scale, Shader* nonDefaultShader) : GameObject(false) {
    SpriteRenderer* spriteRenderer = new SpriteRenderer(this);
    spriteRenderer->SetActiveShader(Shader::GetShader(SHADER_SPRITESHEET));
    
    for(int i = 0; i != info->GetSpriteCount(); i++) {
        std::string totalPath("Game/Assets/Sprites/" + info->GetFilePath(i));
        GLuint texture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath((char*)totalPath.c_str()));
        int columns = info->GetColumnCount(i);
        int rows = info->GetRowCount(i);
        sprites.push_back(new SpriteSheet(texture, columns, rows));
    }

    if (nonDefaultShader != nullptr) {
        shader = nonDefaultShader;
        spriteRenderer->SetActiveShader(shader);
    }

    currentSpriteSheet = 0;
    spriteRenderer->SetActiveSprite(sprites[currentSpriteSheet]);

    Transform* transform = GetTransform();
    transform->setPosition(x, y, z);
    transform->setScale(scale);
    AddComponent<SpriteRenderer*>(spriteRenderer);
	framesTilReturn = -1;
}

//ComplexSprite::~ComplexSprite() {
    //TODO: Memory leak fix
    //if (sprite != nullptr) {
    //    delete(sprite);
    //}
    //if (shader != nullptr) {
    //    delete(shader);
    //}
//}

void ComplexSprite::NextFrame() {
    sprites[currentSpriteSheet]->NextIndex();
	if (framesTilReturn > -1) {
		if (--framesTilReturn == 0) {
			ChangeSprite(spriteToReturnTo);
			framesTilReturn = -1;
		}
	}
}

void ComplexSprite::ChangeSprite(int spriteIndexInComplexInfo) {
	if (spriteIndexInComplexInfo != currentSpriteSheet) {
		sprites[currentSpriteSheet]->ResetIndex();
		currentSpriteSheet = spriteIndexInComplexInfo;
		GetComponent<SpriteRenderer*>()->SetActiveSprite(sprites[spriteIndexInComplexInfo]);
	}
}

int ComplexSprite::GetCurrentSprite() {
	return currentSpriteSheet;
}

void ComplexSprite::ChangeSprite(int spriteIndexInComplexInfo, int returnSprite) {
	ChangeSprite(spriteIndexInComplexInfo);
	spriteToReturnTo = returnSprite;
	framesTilReturn = sprites[returnSprite]->GetColumnCount() * sprites[returnSprite]->GetRowCount();
}