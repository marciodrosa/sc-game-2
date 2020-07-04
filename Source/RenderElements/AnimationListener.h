#pragma once

namespace sc
{
	/** Interface to listen to callbacks for animations. */
	class AnimationListener
	{
	public:
		virtual void OnAnimationEnded() = 0;
	};
}
