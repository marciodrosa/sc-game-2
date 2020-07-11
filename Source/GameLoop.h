#pragma once

#include <iostream>
#include <SDL.h>
#include "GameModule.h"
#include "Models/GameState.h"
#include "ModuleResult.h"

namespace sc
{
	class ModuleTransition;

	/** Main game loop, handles the window and events. */
	class GameLoop
	{
	public:
		GameLoop(GameState& state);
		virtual ~GameLoop();
		void Run();
		void SetModule(GameModule* gameModule);

	private:
		GameState* gameState;
		GameModule* gameModule;
		GameModule* subModule;
		SDL_Renderer* render;
		bool running;
		bool sdlInitiated;
		bool moduleInputEnabled;
		ModuleTransition* transition;
		GameModule* pendingModuleAfterTransition;
		void SetSubModule(GameModule* subModule);
		void SetTransition(ModuleTransition* transition, bool in, GameModule* pendingModuleAfterTransition);
		void ConfigureViewport(SDL_Window* window);
		void Loop();
		void LoopUpdate();
		void UpdateTransition();
		void RenderMargin();
		void HandleModuleResult(ModuleResult& moduleResult);
		void PoolEvents();
		void InitSDLAndResources();
		void QuitSDLAndResources();
	};
}
