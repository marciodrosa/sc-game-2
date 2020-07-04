#pragma once

#include "GameModule.h"
#include "RenderElements/Hands.h"
#include "RenderElements/BlinkingBackground.h"
#include "RenderElements/AnimatedText.h"
#include "RenderElements/AnimationListener.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Module that shows the data of a movie. */
	class MovieModule : public GameModule, public AnimationListener
	{
	public:
		MovieModule();
		virtual ~MovieModule();
		void Start(GameState& state) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
		void OnAnimationEnded() override;

	private:
		SDL_Texture* movieTexture;
		Hands hands;
		BlinkingBackground blinkingBackground;
		AnimatedText text;
	};
}
