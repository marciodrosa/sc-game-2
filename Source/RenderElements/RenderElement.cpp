#include "RenderElement.h"

using namespace sc;

RenderElement::RenderElement()
{
	Width = 0;
	Height = 0;
	PivotX = 0;
	PivotY = 0;
}

RenderElement::~RenderElement()
{
}

void RenderElement::CenterPivot()
{
	PivotX = Width / 2;
	PivotY = Height / 2;
}

void RenderElement::LeftPivot()
{
	PivotX = 0;
}

void RenderElement::RightPivot()
{
	PivotX = Width;
}

void RenderElement::TopPivot()
{
	PivotY = 0;
}

void RenderElement::BottomPivot()
{
	PivotY = Height;
}

SDL_Rect RenderElement::GetRect(int x, int y)
{
	SDL_Rect rect;
	rect.x = x - PivotX;
	rect.y = y - PivotY;
	rect.w = Width;
	rect.h = Height;
	return rect;
}

void RenderElement::RenderAt(SDL_Renderer* renderer, int x, int y)
{
	SDL_Rect rect = GetRect(x, y);
	Render(renderer, rect);
}
