#include "AudioManager.h"

AudioManager::AudioManager()
{
	//-->SDL_Mix
	const Uint8 soundFlags{ MIX_INIT_MP3 };
	if (!(Mix_Init(soundFlags) & soundFlags)) throw std::exception("Error: SDL_image init");
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw std::exception("Unable to open SDL_Mixer sound systems");
	}

	//Title Music
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	menuMusic = Mix_LoadMUS("../../res/au/menu.mp3");
	gameMusic = Mix_LoadMUS("../../res/au/game_theme.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}


AudioManager::~AudioManager()
{
	Mix_CloseAudio();
	Mix_Quit();
}

void AudioManager::PlayMenuMusic()
{
	Mix_PlayMusic(menuMusic, 100);
}

void AudioManager::PlayGameMusic()
{
	Mix_PlayMusic(gameMusic, 100);
}

void AudioManager::PauseMenuMusic()
{
	Mix_VolumeMusic(0);
}

void AudioManager::ResumeMenuMusic()
{
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}
