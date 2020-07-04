#pragma once

#include "GameModule.h"
#include "RenderElements/Hands.h"
#include "RenderElements/BlinkingBackground.h"
#include "RenderElements/AnimatedText.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Module that shows a EXTRA exclamation in the screen. */
	class ExtraModule : public GameModule
	{
	public:
		ExtraModule();
		virtual ~ExtraModule();
		void Start(GameState& state) override;
		void Update(GameState& state, SDL_Renderer* render, ModuleResult& result) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;

	private:
		AnimatedText text;
		Hands hands;
		BlinkingBackground blinkingBackground;
	};
}
