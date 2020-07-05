#include "CautionBackground.h"
#include "Constants.h"

using namespace sc;
using namespace std;

CautionBackground::CautionBackground()
{
	animationFrame = 0;
	colors.push_back(CreateColor(0, 0, 0));
	colors.push_back(CreateColor(90, 0, 0));
	colors.push_back(CreateColor(180, 0, 0));
	frames.push_back(0);
	frames.push_back(0);
	frames.push_back(0);
	frames.push_back(1);
	frames.push_back(1);
	frames.push_back(1);
	frames.push_back(2);
	frames.push_back(2);
	frames.push_back(2);
	frames.push_back(1);
	frames.push_back(1);
	frames.push_back(1);
	Width = SC_SCREEN_WIDTH;
	Height = SC_SCREEN_HEIGHT;
}

CautionBackground::~CautionBackground()
{
}

void CautionBackground::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	SDL_Color& color = colors[frames[animationFrame]];
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
	animationFrame = (animationFrame + 1) % frames.size();
}

SDL_Color CautionBackground::CreateColor(int r, int g, int b)
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	return color;
}
