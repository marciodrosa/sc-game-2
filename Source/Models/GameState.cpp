#include "GameState.h"
#include <set>

using namespace sc;
using namespace std;

GameState::GameState()
{
	SelectedCharacterIndex = 0;
	CurrentMovieIndex = 0;
	IsInModuleInTransition = false;
	IsInModuleOutTransition = false;
	RingoAlreadyAppeared = false;
}

Movie* GameState::FindMovieById(MovieId id)
{
	for (Movie& movie : Movies)
	{
		if (movie.Id == id)
			return &movie;
	}
	return nullptr;
}

void GameState::ResetAvailableAndSelectedMovies()
{
	SelectedMovies.clear();
	AvailableMoviesToSelect.clear();
	for (Movie& movie : Movies)
	{
		AvailableMoviesToSelect.push_back(movie.Id);
	}
}

void GameState::MoveFromAvailableToSelectedMovies(int index)
{
	vector<MovieId> temp;
	for (int i = 0; i < AvailableMoviesToSelect.size(); i++)
	{
		if (i == index)
			SelectedMovies.push_back(AvailableMoviesToSelect[i]);
		else
			temp.push_back(AvailableMoviesToSelect[i]);
	}
	AvailableMoviesToSelect = temp;
}

void GameState::MoveFromSelectedToAvailableMovies(int index)
{
	vector<MovieId> temp;
	for (int i = 0; i < SelectedMovies.size(); i++)
	{
		if (i == index)
			AvailableMoviesToSelect.push_back(SelectedMovies[i]);
		else
			temp.push_back(SelectedMovies[i]);
	}
	SelectedMovies = temp;
}

void GameState::MoveSelectedMovieUp(int index)
{
	if (index > 0)
	{
		MovieId temp1 = SelectedMovies[index - 1];
		MovieId temp2 = SelectedMovies[index];
		SelectedMovies[index - 1] = temp2;
		SelectedMovies[index] = temp1;
	}
}

void GameState::MoveSelectedMovieDown(int index)
{
	if (index < SelectedMovies.size() - 1)
	{
		MovieId temp1 = SelectedMovies[index + 1];
		MovieId temp2 = SelectedMovies[index];
		SelectedMovies[index + 1] = temp2;
		SelectedMovies[index] = temp1;
	}
}
