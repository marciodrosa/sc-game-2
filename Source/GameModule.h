#pragma once

#include "Models/GameState.h"
#include "ModuleResult.h"
#include <SDL.h>

namespace sc
{
	/** Interfaces for modules to be pluged to the game loop. */
	class GameModule
	{
	public:
		virtual void Start(GameState& state) = 0;
		virtual void Update(GameState& state, ModuleResult& result) = 0;
		virtual void Render(GameState& state, SDL_Renderer* renderer) = 0;
		virtual void Finish(GameState& state) = 0;
		virtual void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) = 0;
	};
}
