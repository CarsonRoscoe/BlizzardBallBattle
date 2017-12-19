#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "SpriteSheet.h"
#include <string>
#include <vector>

class ComplexSpriteinfo {
private:
    std::vector<std::string> filePaths;
    std::vector<int> numberOfColumns;
    std::vector<int> numberOfRows;

public:
    void AddInfo(std::string filePath, int columnCount, int rowCount) {
        filePaths.push_back(filePath);
        numberOfColumns.push_back(columnCount);
        numberOfRows.push_back(rowCount);
    }

    std::string GetFilePath(int index) {
        return filePaths[index];
    }

    int GetColumnCount(int index) {
        return numberOfColumns[index];
    }

    int GetRowCount(int index) {
        return numberOfRows[index];
    }

    int GetSpriteCount() {
        return filePaths.size();
    }
};

//MenuSprite* TitleMenu("Title.png", x, y, scale = 1, nondefaultShader = nullptr);
class ComplexSprite : public GameObject {
private:
    Shader* shader;
    std::vector<SpriteSheet*> sprites;
    int currentSpriteSheet;
	int spriteToReturnTo;
	int framesTilReturn;

public:
    ComplexSprite(ComplexSpriteinfo* info, float x, float y, float z = 0.0f, float scale = 1.0f, Shader* nonDefaultShader = nullptr);
    //~ComplexSprite();

    void NextFrame();
    void ChangeSprite(int spriteIndexInComplexInfo);
	int GetCurrentSprite();
	void ChangeSprite(int spriteIndexInComplexInfo, int returnSprite);
};