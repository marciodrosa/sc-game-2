#include "Sprite.h"
#include <SDL_image.h>

using namespace sc;
using namespace std;

Sprite::Sprite()
{
	surface = nullptr;
	texture = nullptr;
}

Sprite::~Sprite()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Sprite::LoadContentFromFile(std::string filePath)
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	surface = nullptr;
	texture = nullptr;
	surface = IMG_Load(filePath.c_str());
	if (surface != nullptr)
	{
		Width = surface->w;
		Height = surface->h;
	}
	else
	{
		Width = 0;
		Height = 0;
	}
}

void Sprite::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	if (surface != nullptr)
	{
		if (texture == nullptr)
			texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}
}
