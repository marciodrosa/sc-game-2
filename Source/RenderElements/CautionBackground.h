#pragma once

#include "RenderElement.h"
#include <vector>

namespace sc
{
	class CautionBackground : public RenderElement
	{
	public:
		CautionBackground();
		~CautionBackground();
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;
	private:
		std::vector<SDL_Color> colors;
		std::vector<int> frames;
		int animationFrame;
		SDL_Color CreateColor(int r, int g, int b);
	};
}
