#pragma once
#include <string>
#include <GLHeaders.h>

class AudioManager {
private:
	static AudioManager* instance;
	Mix_Chunk* bgm;
	Mix_Chunk* SEF1;
	Mix_Chunk* SEF2;
	//GameObject* mGameObj;

	AudioManager();
	~AudioManager();

public:
	static AudioManager* GetInstance();
	static void Release();

	//Starts playing music
	void PlayMusic(std::string filename, int loop = -1, float volumeFactor = 1.0f);
	void PlaySEFhit(std::string filename, int loop = -1, float volumeFactor = 1.0f);
	void PlaySEFshoot(std::string filename, int loop = -1, float volumeFactor = 1.0f);
	//Pauses the current music
	void PauseMusic();
	//Resume playing the music
	void ResumeMusic();
	//Stops playing the music
	void StopMusic();
	//Starts sound effect, plays til the end and stops
	//void PlaySoundEffect(std::string filename, int loop = 0, int channel = 0);


};
