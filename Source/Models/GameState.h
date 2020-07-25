#pragma once

#include <string>
#include <vector>
#include "Character.h"
#include "Movie.h"
#include "DialogueTree.h"

namespace sc
{
	/** Main game state model. */
	class GameState
	{
	public:
		GameState();
		std::vector<Character> Characters;
		std::vector<Movie> Movies;
		std::string PlayerName;
		int SelectedCharacterIndex;
		int CurrentMovieIndex;
		bool IsInModuleInTransition;
		bool IsInModuleOutTransition;
		DialogueTree CurrentDialogue;
		std::vector<std::string> DialogueOptions;
		std::vector<MovieId> AvailableMoviesToSelect;
		std::vector<MovieId> SelectedMovies;
		bool RingoAlreadyAppeared;
		Movie* FindMovieById(MovieId id);
		void ResetAvailableAndSelectedMovies();
		void MoveFromAvailableToSelectedMovies(int index);
		void MoveFromSelectedToAvailableMovies(int index);
		void MoveSelectedMovieUp(int index);
		void MoveSelectedMovieDown(int index);
	};
}
