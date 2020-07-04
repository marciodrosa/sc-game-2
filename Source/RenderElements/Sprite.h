#pragma once

#include "RenderElement.h"
#include <string>

namespace sc
{
	/** Render element that draws an image. */
	class Sprite: public RenderElement
	{
	public:
		Sprite();
		virtual ~Sprite();
		void LoadContentFromFile(std::string filePath);
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;

	private:
		SDL_Surface* surface;
		SDL_Texture* texture;
	};
}
