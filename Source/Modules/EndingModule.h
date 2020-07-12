#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Ending module with the "The End" label. */
	class EndingModule : public GameModule
	{
	public:
		EndingModule();
		virtual ~EndingModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;

	private:
		AnimatedText theEndLabelText;
		AnimatedText theEndLabelTextShadow;
	};
}
