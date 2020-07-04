#include "MusicPlayer.h"
#include <SDL_image.h>

using namespace sc;
using namespace std;

MusicPlayer* MusicPlayer::singleton = nullptr;

MusicPlayer::MusicPlayer()
{
	titleMusic = nullptr;
	gameMusic = nullptr;
	extraMusic = nullptr;
	playingMusic = nullptr;
}

MusicPlayer::~MusicPlayer()
{
	Mix_FreeMusic(titleMusic);
	Mix_FreeMusic(gameMusic);
	Mix_FreeMusic(extraMusic);
}

MusicPlayer* MusicPlayer::Get()
{
	if (singleton == nullptr)
		singleton = new MusicPlayer;
	return singleton;
}

void MusicPlayer::Release()
{
	if (singleton != nullptr)
	{
		delete singleton;
		singleton = nullptr;
	}
}

void MusicPlayer::LoadMusics()
{
	titleMusic = Mix_LoadMUS("Audio/Title.ogg");
	gameMusic = Mix_LoadMUS("Audio/Game.ogg");
	extraMusic = Mix_LoadMUS("Audio/Extra.ogg");
}

void MusicPlayer::PlayTitleMusic()
{
	PlayMusic(titleMusic);
}

void MusicPlayer::PlayGameMusic()
{
	PlayMusic(gameMusic);
}

void MusicPlayer::PlayExtraMusic()
{
	PlayMusic(extraMusic);
}

void MusicPlayer::PlayMusic(Mix_Music* music)
{
	if (music != playingMusic)
	{
		Mix_PlayMusic(music, -1);
		playingMusic = music;
	}
}
