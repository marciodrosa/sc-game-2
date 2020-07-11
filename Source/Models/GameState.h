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
		int SelectedCharacterIndex;
		int CurrentMovieIndex;
		bool IsInModuleInTransition;
		bool IsInModuleOutTransition;
		DialogueTree CurrentDialogue;
		std::string CurrentDialogueLineKey;
		std::vector<std::string> DialogueOptions;
	};
}
