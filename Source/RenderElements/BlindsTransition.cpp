#include "BlindsTransition.h"
#include "Constants.h"

using namespace sc;

BlindsTransition::BlindsTransition()
{
	BlindsAmount = 10;
	animating = false;
	animationPosition = 0;
	direction = 0;
	Width = SC_SCREEN_WIDTH;
	Height = SC_SCREEN_HEIGHT;
	Speed = 2;
}

BlindsTransition::~BlindsTransition()
{
}

void BlindsTransition::TransitionIn()
{
	animating = true;
	animationPosition = CalculateBlindSize();
	direction = -Speed;
}

void BlindsTransition::TransitionOut()
{
	animating = true;
	animationPosition = 0;
	direction = Speed;
}

bool BlindsTransition::TransitionAnimationEnded()
{
	return !animating;
}

void BlindsTransition::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int blindSize = CalculateBlindSize();
	for (int i = 0; i < BlindsAmount; i++)
	{
		SDL_Rect rect;
		rect.x = 0;
		rect.y = blindSize * i;
		rect.w = Width;
		rect.h = animationPosition;
		SDL_RenderFillRect(renderer, &rect);
	}
	if (animating)
		animationPosition += direction;
	if (animationPosition < 0)
		animationPosition = 0;
	if (animationPosition == 0 || animationPosition >= blindSize)
		animating = false;
}

int BlindsTransition::CalculateBlindSize()
{
	return Height / BlindsAmount;
}
