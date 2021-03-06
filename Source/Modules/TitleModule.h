#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include "RenderElements/Sprite.h"
#include "RenderElements/PressEnterIndicator.h"
#include <SDL.h>
#include <SDL_ttf.h>

namespace sc
{
	/** Module that shows the title of the game. */
	class TitleModule : public GameModule, public AnimationListener
	{
	public:
		TitleModule();
		virtual ~TitleModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
		void OnAnimationEnded(RenderElement* renderElement) override;

	private:
		Sprite background;
		Sprite logo;
		PressEnterIndicator pressEnterIndicator;
		int backgroundX;
	};
}
