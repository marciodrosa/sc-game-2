#pragma once

namespace sc
{
	class RenderElement;

	/** Interface to listen to callbacks for animations. */
	class AnimationListener
	{
	public:
		virtual void OnAnimationEnded(RenderElement* renderElement) = 0;
	};
}
