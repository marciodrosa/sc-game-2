#pragma once

#include "GameModule.h"
#include "RenderElements/CharacterSelectionIcon.h"
#include "RenderElements/AnimationListener.h"
#include "RenderElements/Hands.h"
#include "RenderElements/AnimatedText.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Module that shows the character selection screen. */
	class CharacterSelectionModule : public GameModule, public AnimationListener
	{
	public:
		CharacterSelectionModule();
		virtual ~CharacterSelectionModule();
		void Start(GameState& state) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
		void OnAnimationEnded(RenderElement* renderElement) override;

	private:
		void DrawCharacterName(GameState& state, SDL_Renderer* render);
		AnimatedText mainLabelText;
		AnimatedText characterNameText;
		std::vector<CharacterSelectionIcon*> characterIcons;
		Hands hands;
		bool selectionFinished;
	};
}
