#include "ModuleResult.h"

using namespace sc;

ModuleResult::ModuleResult()
{
	NextGameModule = nullptr;
	FinishModule = false;
	DisableInput = false;
	EnableInput = false;
}
