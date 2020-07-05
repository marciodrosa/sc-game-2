#pragma once

#include "ModuleTransition.h"

namespace sc
{
	/** Transition with stripes animation. */
	class StripesTransition : public ModuleTransition
	{
	public:
		StripesTransition();
		virtual ~StripesTransition();
		void TransitionIn() override;
		void TransitionOut() override;
		bool TransitionAnimationEnded() override;
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;
		int StripesAmount;
		int Speed;
	private:
		bool animating;
		int animationPosition;
		int direction;
	};
}
