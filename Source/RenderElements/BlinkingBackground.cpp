#include "BlinkingBackground.h"
#include "Constants.h"
#include <stdlib.h> 

using namespace sc;

BlinkingBackground::BlinkingBackground()
{

}

BlinkingBackground::~BlinkingBackground()
{

}

void BlinkingBackground::Render(SDL_Renderer* render)
{
	SDL_SetRenderDrawColor(render, RandomComponent(), RandomComponent(), RandomComponent(), 255);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = SC_SCREEN_WIDTH;
	rect.h = SC_SCREEN_HEIGHT;
	SDL_RenderFillRect(render, &rect);
}

int BlinkingBackground::RandomComponent()
{
	return rand() % 150;
}
