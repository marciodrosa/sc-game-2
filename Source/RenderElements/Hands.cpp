#include "Hands.h"
#include "ResourcesManager.h"

using namespace sc;

Hands::Hands()
{
	rightTexture = nullptr;
	leftTexture = nullptr;
	okTexture = nullptr;
	Left = false;
	Right = false;
	Ok = false;
}

Hands::~Hands()
{
	SDL_DestroyTexture(rightTexture);
	SDL_DestroyTexture(leftTexture);
	SDL_DestroyTexture(okTexture);
}

int Hands::GetWidth()
{
	int count = 0;
	if (Right)
		count++;
	if (Left)
		count++;
	if (Ok)
		count++;
	return count * 20;
}

int Hands::GetHeight()
{
	return 20;
}

void Hands::Render(SDL_Renderer* render, int x, int y)
{
	if (rightTexture == nullptr && Right)
		rightTexture = SDL_CreateTextureFromSurface(render, ResourcesManager::Get()->HandRightImage);
	if (leftTexture == nullptr && Left)
		leftTexture = SDL_CreateTextureFromSurface(render, ResourcesManager::Get()->HandLeftImage);
	if (okTexture == nullptr && Ok)
		okTexture = SDL_CreateTextureFromSurface(render, ResourcesManager::Get()->HandOkImage);
	SDL_Rect destRect;
	destRect.x = x + 2;
	destRect.y = y + 2;
	destRect.w = 16;
	destRect.h = 16;
	if (Left)
	{
		SDL_RenderCopy(render, leftTexture, nullptr, &destRect);
		destRect.x += 20;
	}
	if (Right)
	{
		SDL_RenderCopy(render, rightTexture, nullptr, &destRect);
		destRect.x += 20;
	}
	if (Ok)
		SDL_RenderCopy(render, okTexture, nullptr, &destRect);
}
