#pragma once

#include "AnimationListener.h"
#include "ModuleTransition.h"

namespace sc
{
	/** Transition animation similar to a shutter. */
	class ShutterTransition: public ModuleTransition
	{
	public:
		ShutterTransition();
		virtual ~ShutterTransition();
		void TransitionIn() override;
		void TransitionOut() override;
		bool TransitionAnimationEnded() override;
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;
		void Open();
		void Close();
		AnimationListener* Listener;
		int Speed;
	private:
		void DrawBlackRect(SDL_Renderer* renderer, int x, int y, int w, int h);
		bool animating;
		int animationDirection;
		int animationPosition;
	};
}
