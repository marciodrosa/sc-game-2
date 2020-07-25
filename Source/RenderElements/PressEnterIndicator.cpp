#include "PressEnterIndicator.h"
#include "Constants.h"

using namespace sc;

#define ENTER_INDICATOR_MARGIN 10

PressEnterIndicator::PressEnterIndicator()
{
	Width = SC_SCREEN_WIDTH;
	Height = SC_SCREEN_HEIGHT;
	blinkStateShow = true;
	blinkFramesCount = 0;
}

PressEnterIndicator::~PressEnterIndicator()
{

}

void PressEnterIndicator::SetLabel(std::string label)
{
	labelText.SetText(label, 10);
	labelText.CenterPivot();
	labelText.RightPivot();
}

void PressEnterIndicator::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	if (blinkStateShow)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect dotRect;
		dotRect.w = 8;
		dotRect.h = 10;
		dotRect.x = rect.w - dotRect.w - ENTER_INDICATOR_MARGIN;
		dotRect.y = rect.h - dotRect.h - ENTER_INDICATOR_MARGIN;
		SDL_RenderFillRect(renderer, &dotRect);
		labelText.RenderAt(renderer, dotRect.x - 5, dotRect.y + (dotRect.h / 2));
	}
	blinkFramesCount++;
	if (blinkFramesCount == 15)
	{
		blinkFramesCount = 0;
		blinkStateShow = !blinkStateShow;
	}
}
