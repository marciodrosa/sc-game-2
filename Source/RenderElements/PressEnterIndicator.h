#pragma once

#include "RenderElement.h"
#include "AnimatedText.h"
#include <string>

namespace sc
{
	class PressEnterIndicator : public RenderElement
	{
	public:
		PressEnterIndicator();
		virtual ~PressEnterIndicator();
		void SetLabel(std::string label);
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;
	private:
		AnimatedText labelText;
		bool blinkStateShow;
		int blinkFramesCount;
	};
}
