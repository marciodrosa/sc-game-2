#pragma once

#include <SDL.h>

namespace sc
{
	/** Draws the hands (left, right and/or ok). */
	class Hands
	{
	public:
		Hands();
		virtual ~Hands();
		bool Right;
		bool Left;
		bool Ok;
		int GetWidth();
		int GetHeight();
		void Render(SDL_Renderer* render, int x, int y);

	private:
		SDL_Texture* rightTexture;
		SDL_Texture* leftTexture;
		SDL_Texture* okTexture;
	};
}
