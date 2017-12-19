#include "Shader.h"

std::map<int, Shader*> Shader::createdShaders;

Shader* Shader::GetShader(int shaderID) {
  map<int, Shader*>::iterator iter = createdShaders.find(shaderID);
  if (iter == createdShaders.end()) {
    //Shader does not exhist, make it
    Shader* shader = nullptr;
    switch (shaderID) {
      case SHADER_DEFAULT:
        shader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str(), SHADER_DEFAULT);
        break;
      case SHADER_PIXEL:
        shader = new Shader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/voxel.fs").c_str(), SHADER_PIXEL);
        break;
      case SHADER_TILE:
        shader = new Shader(BuildPath("Game/Assets/Shaders/tile.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str(), SHADER_TILE);
        break;
      case SHADER_SPRITESHEET:
        shader = new Shader(BuildPath("Game/Assets/Shaders/sprite_sheet.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str(), SHADER_SPRITESHEET);
        break;
      case SHADER_PP_DEFAULT:
        shader = new Shader(BuildPath("Game/Assets/Shaders/ppPassThrough.vs").c_str(), BuildPath("Game/Assets/Shaders/ppPassThrough.fs").c_str(), SHADER_PP_DEFAULT);
        break;
      case SHADER_PP_EXTRACTLIGHT:
        shader = new Shader(BuildPath("Game/Assets/Shaders/ppPassThrough.vs").c_str(), BuildPath("Game/Assets/Shaders/ppExtractBrightness.fs").c_str(), SHADER_PP_EXTRACTLIGHT);
        break;
      case SHADER_PP_BLOOMCOMBINE:
        shader = new Shader(BuildPath("Game/Assets/Shaders/ppPassThrough.vs").c_str(), BuildPath("Game/Assets/Shaders/ppBloom.fs").c_str(), SHADER_PP_BLOOMCOMBINE);
        break;
      case SHADER_PP_HORIZONTALBLUR:
        shader = new Shader(BuildPath("Game/Assets/Shaders/ppHorizontalGaussianBlur.vs").c_str(), BuildPath("Game/Assets/Shaders/ppGaussianBlur.fs").c_str(), SHADER_PP_HORIZONTALBLUR);
        break;
      case SHADER_PP_VERTICALBLUR:
        shader = new Shader(BuildPath("Game/Assets/Shaders/ppVerticalGaussianBlur.vs").c_str(), BuildPath("Game/Assets/Shaders/ppGaussianBlur.fs").c_str(), SHADER_PP_VERTICALBLUR);
        break;
      case SHADER_PP_EXTRACTLIGHTDIRECTIONAL:
        shader = new Shader(BuildPath("Game/Assets/Shaders/ppExtractBrightnessDirectional.vs").c_str(), BuildPath("Game/Assets/Shaders/ppExtractBrightnessDirectional.fs").c_str(), SHADER_PP_EXTRACTLIGHTDIRECTIONAL);
        break;
      case SHADER_PP_AMBIENTCOLOR:
        shader = new Shader(BuildPath("Game/Assets/Shaders/ppPassThrough.vs").c_str(), BuildPath("Game/Assets/Shaders/ppAmbientColour.fs").c_str(), SHADER_PP_AMBIENTCOLOR);
        break;
      case SHADER_SHADOW_DEFAULT:
      shader = new Shader(BuildPath("Game/Assets/Shaders/shadow.vs").c_str(), BuildPath("Game/Assets/Shaders/shadow.fs").c_str(), SHADER_SHADOW_DEFAULT);
        break;
      case SHADER_SHADOW_SPRITESHEET:
      shader = new Shader(BuildPath("Game/Assets/Shaders/shadow_SpriteSheet.vs").c_str(), BuildPath("Game/Assets/Shaders/shadow.fs").c_str(), SHADER_SHADOW_SPRITESHEET);
        break;
    }
    if (shader != nullptr) {
      createdShaders[shaderID] = shader;
    } else {
      std::cout << "ERROR::SHADER::GETSHADER::FAILED TO CREATE SHADER" << std::endl;
      return nullptr;
    }
  }
  return createdShaders[shaderID];
}

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath, int id) {
  //1. Retrieve the vertex/fragment source code from filePath
  string vertexCode, fragmentCode;
  ifstream vShaderFile, fShaderFile;

  //Ensure ifstream objects can throw exceptions
  vShaderFile.exceptions(ifstream::badbit);
  fShaderFile.exceptions(ifstream::badbit);

  //Store the shader file names for comparisons later
  shaderID = id;

  try {
    //Open files for reading
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    stringstream vShaderStream, fShaderStream;

    //Read file's buffer contents into the streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    //Stream to string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
     
    int vsCodeLen = vertexCode.length();
    if (vsCodeLen > 2 && vertexCode[vsCodeLen-1] == '\c' && vertexCode[vsCodeLen] == '\r') {
      vertexCode.pop_back();
      vertexCode.pop_back();
      vertexCode.push_back('\r');
    }

    int fsCodeLen = fragmentCode.length();
    if (fsCodeLen > 2 && fragmentCode[fsCodeLen - 1] == '\c' && fragmentCode[fsCodeLen] == '\r') {
      fragmentCode.pop_back();
      fragmentCode.pop_back();
      fragmentCode.push_back('\r');
    }
  }
  catch (ifstream::failure e) {
    cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
  }
  const GLchar* vShaderCode = vertexCode.c_str();
  const GLchar* fShaderCode = fragmentCode.c_str();

  //2. Compile shaders
  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];

  //Vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  //Error check
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
  }

  //Fragmemt Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  //Error check
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
  }

  //Create Shader Program
  this->Program = glCreateProgram();
  glAttachShader(this->Program, vertex);
  glAttachShader(this->Program, fragment);
  glLinkProgram(this->Program);

  //Error check
  glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
    cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
  }
  

  //Delete shaders as they're linked
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::Use() {
  glUseProgram(this->Program);
}


int Shader::GetID() {
  return shaderID;
}