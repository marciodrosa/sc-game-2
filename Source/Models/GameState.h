#pragma once

#include <string>
#include <vector>
#include "Character.h"
#include "Movie.h"

namespace sc
{
	/** Main game state model. */
	class GameState
	{
	public:
		GameState();
		std::vector<Character> Characters;
		std::vector<Movie> Movies;
		int SelectedCharacterIndex;
		int CurrentMovieIndex;
	};
}
