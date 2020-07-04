#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include <SDL.h>
#include <SDL_ttf.h>

namespace sc
{
	/** Module that shows the title of the game. */
	class TitleModule : public GameModule
	{
	public:
		TitleModule();
		virtual ~TitleModule();
		void Start(GameState& state) override;
		void Update(GameState& state, SDL_Renderer* render, ModuleResult& result) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;

	private:
		SDL_Surface* logoImage;
		SDL_Texture* logoTexture;
		AnimatedText text;
	};
}
