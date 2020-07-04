#pragma once

#include <SDL.h>
#include "Models/Character.h"
#include "Models/GameState.h"
#include "AnimationListener.h"

namespace sc
{
	/** Icon draw of a character. */
	class CharacterSelectionIcon
	{
	public:
		CharacterSelectionIcon(Character* character);
		virtual ~CharacterSelectionIcon();
		void Render(GameState& state, SDL_Renderer* render, int x, int y);
		void Blink(AnimationListener* listener);

	private:
		SDL_Texture* characterTexture;
		SDL_Texture* selectionTexture;
		Character* character;
		AnimationListener* blinkAnimationListener;
		bool blinking;
		int blinksCount;
	};
}
