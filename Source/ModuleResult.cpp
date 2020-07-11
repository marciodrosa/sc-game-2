#include "ModuleResult.h"

using namespace sc;

ModuleResult::ModuleResult()
{
	NextGameModule = nullptr;
	SubModule = nullptr;
	FinishModule = false;
	DisableInput = false;
	EnableInput = false;
}
