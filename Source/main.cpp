#include <iostream>
#include <SDL.h>
#include <stdlib.h>
#include<time.h> 
#include "GameLoop.h"
#include "Models/GameState.h"
#include "Models/Character.h"
#include "Modules/TitleModule.h"
#include "Models/Movie.h"

using namespace sc;

int main(int argc, char* argv[])
{
	srand(time(0));
	GameState gameState;
	gameState.Characters = Character::GetCharacters();
	gameState.Movies = Movie::GetMovies();
	GameLoop gameLoop(gameState);
	gameLoop.SetModule(new TitleModule);
	gameLoop.Run();
	return 0;
}
