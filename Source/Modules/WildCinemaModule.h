#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include "RenderElements/Sprite.h"
#include "RenderElements/CautionBackground.h"
#include <string>

namespace sc
{
	/** Module that shows the cinema building. */
	class WildCinemaModule : public GameModule
	{
	public:
		WildCinemaModule();
		virtual ~WildCinemaModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
	private:
		CautionBackground background;
		Sprite cinema;
		AnimatedText text;
		int x;
	};
}
