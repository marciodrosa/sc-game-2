#pragma once

#include "AnimationListener.h"
#include "RenderElement.h"

namespace sc
{
	/** Transition animation similar to a shutter. */
	class ShutterTransition: public RenderElement
	{
	public:
		ShutterTransition();
		virtual ~ShutterTransition();
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;
		void Open();
		AnimationListener* Listener;
		int Speed;
	private:
		void DrawBlackRect(SDL_Renderer* renderer, int x, int y, int w, int h);
		bool opening;
		int location;
	};
}
