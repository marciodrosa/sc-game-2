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
		Mix_Chunk* NavigateSound;
		Mix_Chunk* SelectSound;
		Mix_Chunk* EnterSound;
		Mix_Chunk* StartSound;
		Mix_Chunk* CosmoNetOkSound;

	private:
		static ResourcesManager* singleton;
	};
}
