#include "ShutterTransition.h"
#include "Constants.h"

using namespace sc;

ShutterTransition::ShutterTransition()
{
	animating = false;
	Listener = nullptr;
	animationPosition = 0;
	animationDirection = 0;
	Width = SC_SCREEN_WIDTH;
	Height = SC_SCREEN_HEIGHT;
	Speed = 10;
}

ShutterTransition::~ShutterTransition()
{
}

void ShutterTransition::TransitionIn()
{
	Open();
}

void ShutterTransition::TransitionOut()
{
	Close();
}

bool ShutterTransition::TransitionAnimationEnded()
{
	return !animating;
}

void ShutterTransition::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	if (animating)
		animationPosition += animationDirection;
	int horizontalAnimationPosition = animationPosition * Speed;
	int verticalAnimationPosition = animationPosition * ((float)Speed / ((float)Width / (float)Height));
	if (horizontalAnimationPosition < 0)
		horizontalAnimationPosition = 0;
	if (verticalAnimationPosition < 0)
		verticalAnimationPosition = 0;
	bool animationFinished = false;
	if (animationDirection > 0)
		animationFinished = horizontalAnimationPosition > Width / 2 && verticalAnimationPosition > Height / 2;
	else
		animationFinished = horizontalAnimationPosition == 0 && verticalAnimationPosition == 0;
	if (animating && animationFinished)
	{
		if (Listener != nullptr)
			Listener->OnAnimationEnded(this);
		animating = false;
	}
	int w = Width / 2;
	int h = Height / 2;
	int x1 = w + horizontalAnimationPosition;
	int x2 = -horizontalAnimationPosition;
	int y1 = h + verticalAnimationPosition;
	int y2 = -verticalAnimationPosition;
	DrawBlackRect(renderer, x1, 0, w, Height);
	DrawBlackRect(renderer, x2, 0, w, Height);
	DrawBlackRect(renderer, 0, y1, Width, h);
	DrawBlackRect(renderer, 0, y2, Width, h);
}

void ShutterTransition::Open()
{
	animationPosition = 0;
	animationDirection = 1;
	animating = true;
}

void ShutterTransition::Close()
{
	animationPosition = (Width / 2) / Speed;
	animationDirection = -1;
	animating = true;
}

void ShutterTransition::DrawBlackRect(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderFillRect(renderer, &rect);
}
