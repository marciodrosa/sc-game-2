#pragma once

#include "ModuleTransition.h"

namespace sc
{
	/** Transition with blinds animation. */
	class BlindsTransition: public ModuleTransition
	{
	public:
		BlindsTransition();
		virtual ~BlindsTransition();
		void TransitionIn() override;
		void TransitionOut() override;
		bool TransitionAnimationEnded() override;
		void Render(SDL_Renderer* renderer, SDL_Rect& rect) override;
		int BlindsAmount;
		int Speed;
	private:
		bool animating;
		int animationPosition;
		int direction;
		int CalculateBlindSize();
	};
}
