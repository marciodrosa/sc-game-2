#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

namespace sc
{
	/** Utility class to play musics. */
	class MusicPlayer
	{
	private:
		MusicPlayer();
	public:
		virtual ~MusicPlayer();
		static MusicPlayer* Get();
		static void Release();
		void LoadMusics();
		void PlayTitleMusic();
		void PlayGameMusic();
		void PlayExtraMusic();

	private:
		static MusicPlayer* singleton;
		Mix_Music* titleMusic;
		Mix_Music* gameMusic;
		Mix_Music* extraMusic;
		Mix_Music* playingMusic;
		void PlayMusic(Mix_Music* music);
	};
}
