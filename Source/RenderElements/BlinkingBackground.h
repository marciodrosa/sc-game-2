#pragma once

#include "RenderElement.h"

namespace sc
{
	/** A blinking background that can be rendered. */
	class BlinkingBackground: public RenderElement
	{
	public:
		BlinkingBackground();
		virtual ~BlinkingBackground();
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;
	private:
		int RandomComponent();
	};
}
