#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include "Models/Character.h"
#include "Models/Movie.h"
#include "RenderElements/Sprite.h"

namespace sc
{
	/** Singleton utility class that loads and handles resources files and data. */
	class ResourcesManager
	{
	private:
		ResourcesManager();
	public:
		virtual ~ResourcesManager();
		static ResourcesManager* Get();
		static void Release();
		void LoadResources();
		Sprite HandSprite;
		SDL_Surface* GetMovieImage(MovieId id);
		SDL_Surface* GetCharacterImage(CharacterId id);
		SDL_Surface* GetCharacterSmallImage(CharacterId id);
		Mix_Chunk* NavigateSound;
		Mix_Chunk* SelectSound;
		Mix_Chunk* EnterSound;
		Mix_Chunk* StartSound;

	private:
		std::map<MovieId, SDL_Surface*> moviesImages;
		std::map<CharacterId, SDL_Surface*> charactersImages;
		std::map<CharacterId, SDL_Surface*> smallCharactersImages;
		static ResourcesManager* singleton;
	};
}
