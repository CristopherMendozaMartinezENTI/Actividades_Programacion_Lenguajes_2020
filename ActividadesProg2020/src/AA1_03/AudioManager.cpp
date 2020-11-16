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
	menuMusic = Mix_LoadMUS("../../res/au/mainTheme.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(menuMusic, -1);
}

AudioManager::~AudioManager()
{
	//Mix_CloseAudio();
	//Mix_Quit();
}

void AudioManager::PlayMenuMusic()
{
	Mix_PlayMusic(menuMusic, 100);
}

void AudioManager::PauseMenuMusic()
{
	Mix_PauseMusic();
}
