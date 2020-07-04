#pragma once

#include "AnimationListener.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace sc
{
	/** Text that can be render in the screen and animated to show one character each frame. */
	class AnimatedText
	{
	public:
		AnimatedText();
		virtual ~AnimatedText();
		void SetText(std::string text, int fontSize, int width = 0, bool animated = false, int animationSpeed = 1, AnimationListener* animationListener = nullptr);
		void ForceFinishAnimation();
		bool IsAnimating();
		int GetWidth();
		int GetHeight();
		void Render(SDL_Renderer* render, int x, int y);
	private:
		void AnimateText();
		SDL_Surface* textSurface;
		SDL_Surface* animTextSurface;
		SDL_Texture* textTexture;
		TTF_Font* font;
		std::string targetText;
		std::string currentText;
		int animationSpeed;
		int animated;
		int width;
		SDL_Color color;
		AnimationListener* animationListener;
	};
}
