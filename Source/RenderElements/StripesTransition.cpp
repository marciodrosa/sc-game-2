#include "StripesTransition.h"
#include "Constants.h"

using namespace sc;

StripesTransition::StripesTransition()
{
	StripesAmount = 14;
	animating = false;
	animationPosition = 0;
	direction = 0;
	Width = SC_SCREEN_WIDTH;
	Height = SC_SCREEN_HEIGHT;
	Speed = 10;
}

StripesTransition::~StripesTransition()
{
}

void StripesTransition::TransitionIn()
{
	animating = true;
	animationPosition = 0;
	direction = Speed;
}

void StripesTransition::TransitionOut()
{
	animating = true;
	animationPosition = Width;
	direction = -Speed;
}

bool StripesTransition::TransitionAnimationEnded()
{
	return !animating;
}

void StripesTransition::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int stripeHeight = Height / StripesAmount;
	for (int i = 0; i < StripesAmount; i++)
	{
		SDL_Rect rect;
		rect.x = animationPosition;
		if (i % 2 == 0)
			rect.x = -rect.x;
		rect.y = stripeHeight * i;
		rect.w = Width;
		rect.h = stripeHeight;
		SDL_RenderFillRect(renderer, &rect);
	}
	if (animating)
		animationPosition += direction;
	if (animationPosition < 0)
		animationPosition = 0;
	if (animationPosition == 0 || animationPosition >= Width)
		animating = false;
}
