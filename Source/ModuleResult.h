#pragma once

namespace sc
{
	class GameModule;

	/** Object to be changed by the implementation of a module. */
	class ModuleResult
	{
	public:
		ModuleResult();
		GameModule* NextGameModule;
		bool FinishGame;
		bool DisableInput;
	};
}
