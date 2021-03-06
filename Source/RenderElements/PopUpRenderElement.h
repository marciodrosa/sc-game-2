#pragma once

#include "RenderElement.h"
#include "AnimatedText.h"
#include "Sprite.h"
#include <string>
#include <vector>

namespace sc
{
	class PopUpRenderElement : public RenderElement
	{
	private:
		PopUpRenderElement(const PopUpRenderElement& other);
	public:
		PopUpRenderElement();
		virtual ~PopUpRenderElement();
		void SetContent(std::string title, std::vector<std::string>& options, int maxWidth = 0);
		void Animate();
		bool IsAnimating();
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;
		int SelectedOption;
	private:
		void RenderBackground(SDL_Renderer* renderer, SDL_Rect& rect);
		void RenderOptions(SDL_Renderer* renderer, SDL_Rect& rect);
		void RecalculateSize();
		std::vector<AnimatedText*> options;
		AnimatedText title;
		Sprite* handSprite;
		bool animating;
		int animationPhase;
	};
}
