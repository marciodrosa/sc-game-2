#pragma once

#include "AnimationListener.h"
#include "RenderElement.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace sc
{
	/** Text that can be render in the screen and animated to show one character each frame. */
	class AnimatedText: public RenderElement
	{
	public:
		AnimatedText();
		virtual ~AnimatedText();
		void SetText(std::string text, int fontSize, int width = 0, int r = 255, int g = 255, int b = 255);
		void SetAnimated(bool animated = true, int animationSpeed = 1);
		void ForceFinishAnimation();
		bool IsAnimating();
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;
		AnimationListener* Listener;
	private:
		void AnimateText();
		void RefreshText();
		SDL_Surface* textSurface;
		SDL_Surface* animTextSurface;
		SDL_Texture* textTexture;
		TTF_Font* font;
		std::string targetText;
		std::string currentText;
		int animationSpeed;
		int animated;
		int maxWidth;
		SDL_Color color;
	};
}
