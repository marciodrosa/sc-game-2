#include "BlinkingBackground.h"
#include "Constants.h"
#include <stdlib.h> 

using namespace sc;

BlinkingBackground::BlinkingBackground()
{
	Width = SC_SCREEN_WIDTH;
	Height = SC_SCREEN_HEIGHT;
}

BlinkingBackground::~BlinkingBackground()
{

}

void BlinkingBackground::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	SDL_SetRenderDrawColor(renderer, RandomComponent(), RandomComponent(), RandomComponent(), 255);
	SDL_RenderFillRect(renderer, &rect);
}

int BlinkingBackground::RandomComponent()
{
	return rand() % 150;
}
