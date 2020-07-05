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
	int verticalAnimationPosition = animationPosition * ((float)Speed / ((float)SC_SCREEN_WIDTH / (float)SC_SCREEN_HEIGHT));
	if (horizontalAnimationPosition < 0)
		horizontalAnimationPosition = 0;
	if (verticalAnimationPosition < 0)
		verticalAnimationPosition = 0;
	bool animationFinished = false;
	if (animationDirection > 0)
		animationFinished = horizontalAnimationPosition > SC_SCREEN_WIDTH / 2 && verticalAnimationPosition > SC_SCREEN_HEIGHT / 2;
	else
		animationFinished = horizontalAnimationPosition == 0 && verticalAnimationPosition == 0;
	if (animating && animationFinished)
	{
		if (Listener != nullptr)
			Listener->OnAnimationEnded(this);
		animating = false;
	}
	int w = SC_SCREEN_WIDTH / 2;
	int h = SC_SCREEN_HEIGHT / 2;
	int x1 = w + horizontalAnimationPosition;
	int x2 = -horizontalAnimationPosition;
	int y1 = h + verticalAnimationPosition;
	int y2 = -verticalAnimationPosition;
	DrawBlackRect(renderer, x1, 0, w, SC_SCREEN_HEIGHT);
	DrawBlackRect(renderer, x2, 0, w, SC_SCREEN_HEIGHT);
	DrawBlackRect(renderer, 0, y1, SC_SCREEN_WIDTH, h);
	DrawBlackRect(renderer, 0, y2, SC_SCREEN_WIDTH, h);
}

void ShutterTransition::Open()
{
	animationPosition = 0;
	animationDirection = 1;
	animating = true;
}

void ShutterTransition::Close()
{
	animationPosition = (SC_SCREEN_WIDTH / 2) / Speed;
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
