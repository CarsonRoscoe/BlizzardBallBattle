#include "AudioManager.h"
#include <iostream>
#include <string>
#include "SpriteRendererManager.h"

AudioManager* AudioManager::instance;

AudioManager* AudioManager::GetInstance()
{
	if (instance == NULL)
		instance = new AudioManager();
	return instance;
}

void AudioManager::Release() {
	delete instance;
	instance = NULL;
}

AudioManager::AudioManager() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	bgm = Mix_LoadWAV(BuildPath("Game/Assets/Audio/mario_.wav").c_str());
	SEF1 = Mix_LoadWAV(BuildPath("Game/Assets/Audio/hit1.wav").c_str());
	SEF2 = Mix_LoadWAV(BuildPath("Game/Assets/Audio/hit2.wav").c_str());
}

AudioManager::~AudioManager() {
	Mix_Quit();
}

void AudioManager::PlayMusic(std::string filename, int loops, float volumeFactor) {
	Mix_PlayChannel(1, bgm, 0);
	Mix_Volume(1, 10 * volumeFactor);
}
void AudioManager::PlaySEFshoot(std::string filename, int loops, float volumeFactor) {
	Mix_PlayChannel(2, SEF1, 0);
	Mix_Volume(2, 128 * volumeFactor);
}

void AudioManager::PlaySEFhit(std::string filename, int loops, float volumeFactor) {
	Mix_PlayChannel(3, SEF2, 0);
	Mix_Volume(3, 35 * volumeFactor);
}

void AudioManager::PauseMusic() {
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::ResumeMusic() {
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::StopMusic() {
	Mix_CloseAudio();
}
