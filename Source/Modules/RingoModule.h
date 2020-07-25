#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include "RenderElements/Sprite.h"
#include "RenderElements/BlinkingBackground.h"
#include "RenderElements/PressEnterIndicator.h"
#include <string>

namespace sc
{
	/** Module with Ringo talking. */
	class RingoModule : public GameModule
	{
	public:
		RingoModule();
		virtual ~RingoModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
	private:
		BlinkingBackground background;
		Sprite ringo;
		AnimatedText text;
		PressEnterIndicator pressEnterIndicator;
		void RefreshDialogueLine(GameState& state);
	};
}
