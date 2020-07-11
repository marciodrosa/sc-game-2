#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include "RenderElements/Sprite.h"
#include <string>
#include <vector>

namespace sc
{
	/** Module used to select a dialogue option. */
	class DialogueOptionSelectorModule : public GameModule
	{
	public:
		DialogueOptionSelectorModule();
		virtual ~DialogueOptionSelectorModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
	private:
		std::vector<AnimatedText> options;
		Sprite* handSprite;
		int GetIndexOfCurrentSelectedOption(GameState& state);
		void SetIndexOfCurrentSelectedOption(GameState& state, int newIndex);
	};
}
