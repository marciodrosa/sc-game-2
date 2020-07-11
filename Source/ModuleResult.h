#pragma once

namespace sc
{
	class GameModule;
	class ModuleTransition;

	/** Object to be changed by the implementation of a module. */
	class ModuleResult
	{
	public:
		ModuleResult();
		GameModule* NextGameModule;
		GameModule* SubModule;
		ModuleTransition* Transition;
		bool FinishModule;
		bool DisableInput;
		bool EnableInput;
	};
}
