#pragma once

#include <SDL.h>

namespace sc
{
	/** A blinking background that can be rendered. */
	class BlinkingBackground
	{
	public:
		BlinkingBackground();
		virtual ~BlinkingBackground();
		void Render(SDL_Renderer* render);
	private:
		int RandomComponent();
	};
}
