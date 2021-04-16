#pragma once
#include "Types.h"

class AudioManager
{

private:
	Mix_Music* menuMusic;
	Mix_Music* gameMusic;

public:
	AudioManager();
	~AudioManager();
	void PlayMenuMusic();
	void PlayGameMusic();
	void PauseMenuMusic();
	void ResumeMenuMusic();
};

