#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include "RenderElements/PressEnterIndicator.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Module that shows an intro text. */
	class IntroModule : public GameModule
	{
	public:
		IntroModule();
		virtual ~IntroModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;

	private:
		AnimatedText text;
		AnimatedText textShadow;
		PressEnterIndicator pressEnterIndicator;
	};
}
