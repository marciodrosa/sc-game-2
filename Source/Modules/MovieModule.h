#pragma once

#include "GameModule.h"
#include "RenderElements/BlinkingBackground.h"
#include "RenderElements/AnimatedText.h"
#include "RenderElements/AnimationListener.h"
#include "RenderElements/Sprite.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Module that shows the data of a movie. */
	class MovieModule : public GameModule, public AnimationListener
	{
	public:
		MovieModule(bool includeTransitionIn = false);
		virtual ~MovieModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
		void OnAnimationEnded(RenderElement* renderElement) override;

	private:
		Sprite movieImage;
		BlinkingBackground blinkingBackground;
		AnimatedText text;
		bool includeTransitionIn;
	};
}
