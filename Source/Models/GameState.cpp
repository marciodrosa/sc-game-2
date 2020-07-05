#include "GameState.h"

using namespace sc;

GameState::GameState()
{
	SelectedCharacterIndex = 0;
	CurrentMovieIndex = 0;
	IsInModuleInTransition = false;
	IsInModuleOutTransition = false;
}
