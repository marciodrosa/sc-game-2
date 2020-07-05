#pragma once

#include "RenderElement.h"

namespace sc
{
	/** Special kind of RenderElement that can be used as a transition animation between modules. */
	class ModuleTransition: public RenderElement
	{
	public:
		ModuleTransition();
		virtual ~ModuleTransition();
		virtual void TransitionIn() = 0;
		virtual void TransitionOut() = 0;
		virtual bool TransitionAnimationEnded() = 0;
	};
}
