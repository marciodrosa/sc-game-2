#include "ShutterTransition.h"
#include "Constants.h"

using namespace sc;

ShutterTransition::ShutterTransition()
{
	opening = false;
	Listener = nullptr;
	location = 0;
	Width = SC_SCREEN_WIDTH;
	Height = SC_SCREEN_HEIGHT;
	Speed = 5;
}

ShutterTransition::~ShutterTransition()
{
}

void ShutterTransition::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	if (opening)
	{
		location += Speed;
		if (location > SC_SCREEN_WIDTH / 2)
		{
			if (Listener != nullptr)
				Listener->OnAnimationEnded(this);
			opening = false;
		}
	}
	int w = SC_SCREEN_WIDTH / 2;
	int h = SC_SCREEN_HEIGHT / 2;
	int x1 = w + location;
	int x2 = -location;
	int y1 = h + location;
	int y2 = -location;
	DrawBlackRect(renderer, x1, 0, w, SC_SCREEN_HEIGHT);
	DrawBlackRect(renderer, x2, 0, w, SC_SCREEN_HEIGHT);
	DrawBlackRect(renderer, 0, y1, SC_SCREEN_WIDTH, h);
	DrawBlackRect(renderer, 0, y2, SC_SCREEN_WIDTH, h);
}

void ShutterTransition::Open()
{
	location = 0;
	opening = true;
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
