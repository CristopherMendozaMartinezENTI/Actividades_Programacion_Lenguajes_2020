#pragma once
#include "Types.h"

class AudioManager
{

private:
	Mix_Music* menuMusic;

public:
	AudioManager();
	~AudioManager();
	void PlayMenuMusic();
	void PauseMenuMusic();
	void ResumeMenuMusic();
};

