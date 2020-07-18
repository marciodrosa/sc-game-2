#include "VoteModule.h"
#include "MovieModule.h"
#include "LukaModule.h"
#include "CosmoNetModule.h"
#include "Constants.h"
#include "ResourcesManager.h"
#include "RenderElements/ShutterTransition.h"
#include <sstream>

using namespace sc;
using namespace std;

VoteModule::VoteModule()
{
	cursorIndex = 0;
	cursorAtRight = false;
	cursor = nullptr;
}

VoteModule::~VoteModule()
{
	DeleteOptionsTexts();
}

void VoteModule::Start(GameState& state, ModuleResult& result)
{
	cursor = &ResourcesManager::Get()->HandSprite;
	RefreshAll(state);
}

void VoteModule::Update(GameState& state, ModuleResult& result)
{
}

void VoteModule::Render(GameState& state, SDL_Renderer* renderer)
{
	leftColumnTitle.RenderAt(renderer, 10, 10);
	rightColumnTitle.RenderAt(renderer, (SC_SCREEN_WIDTH / 2) + 10, 10);
	int y = leftColumnTitle.Height + 20;
	for (int i = 0; i < optionsAtLeft.size(); i++)
	{
		VoteActionIds option = optionsAtLeft[i];
		AnimatedText* optionText = optionsTexts[option];
		optionText->RenderAt(renderer, 25, y);
		if (!cursorAtRight && cursorIndex == i)
			cursor->RenderAt(renderer, 20, y + (optionText->Height / 2));
		y += optionText->Height;
	}
	y = rightColumnTitle.Height + 20;
	for (int i = 0; i < optionsAtRight.size(); i++)
	{
		VoteActionIds option = optionsAtRight[i];
		AnimatedText* optionText = optionsTexts[option];
		optionText->RenderAt(renderer, (SC_SCREEN_WIDTH / 2) + 25, y);
		if (cursorAtRight && cursorIndex == i)
			cursor->RenderAt(renderer, (SC_SCREEN_WIDTH / 2) + 20, y + (optionText->Height / 2));
		y += optionText->Height;
	}
}

void VoteModule::Finish(GameState& state)
{
}

void VoteModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_UP)
	{
		cursorIndex--;
		if (cursorIndex < 0)
			cursorIndex = 0;
	}
	else if (inputEvent.keysym.sym == SDLK_DOWN)
	{
		int max = cursorAtRight ? optionsAtRight.size() - 1 : optionsAtLeft.size() - 1;
		cursorIndex++;
		if (cursorIndex > max)
			cursorIndex = max;
	}
	else if (inputEvent.keysym.sym == SDLK_LEFT)
	{
		if (cursorAtRight)
		{
			cursorAtRight = false;
			cursorIndex = 0;
		}
	}
	else if (inputEvent.keysym.sym == SDLK_RIGHT)
	{
		if (!cursorAtRight && optionsAtRight.size() > 0)
		{
			cursorAtRight = true;
			cursorIndex = 0;
		}
	}
	else if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		VoteActionIds actionId = cursorAtRight ? optionsAtRight[cursorIndex] : optionsAtLeft[cursorIndex];
		if (actionId >= VoteActionIds::AVAILABLE_MOVIE_1 && actionId <= AVAILABLE_MOVIE_10)
		{
			state.MoveFromAvailableToSelectedMovies(GetFocusedMovieIndex(state));
			RefreshAll(state);
		}
		else if (actionId >= VoteActionIds::PICKED_MOVIE_1 && actionId <= PICKED_MOVIE_10)
		{
			Movie* focusedMovie = GetFocusedMovie(state);
			vector<PopUpOption> popUpOptions;
			popUpOptions.push_back(PopUpOption(VoteActionIds::REMOVE_PICKED_MOVIE, "Remover da lista"));
			popUpOptions.push_back(PopUpOption(VoteActionIds::SORT_PICKED_MOVIE_UP, "Mover para cima"));
			popUpOptions.push_back(PopUpOption(VoteActionIds::SORT_PICKED_MOVIE_DOWN, "Mover para baixo"));
			popUpOptions.push_back(PopUpOption(VoteActionIds::CANCEL, "Cancelar"));
			result.SubModule = new PopUpModule(VoteActionIds::PICKED_MOVIE_OPTIONS, focusedMovie->Name, popUpOptions, this);
		}
		else if (actionId == VoteActionIds::OPTIONS)
		{
			vector<PopUpOption> popUpOptions;
			popUpOptions.push_back(PopUpOption(VoteActionIds::RESTART_LIST, "Reiniciar lista"));
			popUpOptions.push_back(PopUpOption(VoteActionIds::REVIEW_PRESENTATION, "Rever apresentação"));
			popUpOptions.push_back(PopUpOption(VoteActionIds::ABORT_VOTE, "Não quero votar agora"));
			popUpOptions.push_back(PopUpOption(VoteActionIds::CANCEL, "Cancelar"));
			result.SubModule = new PopUpModule(VoteActionIds::OPTIONS, "", popUpOptions, this);
		}
		else if (actionId == VoteActionIds::SEND)
		{
			vector<PopUpOption> popUpOptions;
			popUpOptions.push_back(PopUpOption(VoteActionIds::YES, "Sim"));
			popUpOptions.push_back(PopUpOption(VoteActionIds::NO, "Não"));
			result.SubModule = new PopUpModule(VoteActionIds::SEND, "Enviar votos para o sistema COSMONET?", popUpOptions, this);
		}
	}
}

void VoteModule::OnPopUpOptionSelected(int popUpId, PopUpOption& option, GameState& state, ModuleResult& result)
{
	switch (popUpId)
	{
	case VoteActionIds::OPTIONS:
		switch (option.Id)
		{
		case VoteActionIds::RESTART_LIST:
			state.ResetAvailableAndSelectedMovies();
			RefreshAll(state);
			ResetCursor();
			break;
		case VoteActionIds::REVIEW_PRESENTATION:
			state.CurrentMovieIndex = 0;
			result.NextGameModule = new MovieModule(true);
			break;
		case VoteActionIds::ABORT_VOTE:
			state.CurrentDialogue = DialogueTree::EndingDialogueTree();
			result.NextGameModule = new LukaModule();
			break;
		case VoteActionIds::CANCEL:
			break;
		}
		break;
	case VoteActionIds::PICKED_MOVIE_OPTIONS:
		switch (option.Id)
		{
		case VoteActionIds::REMOVE_PICKED_MOVIE:
			state.MoveFromSelectedToAvailableMovies(GetFocusedMovieIndex(state));
			RefreshAll(state);
			break;
		case VoteActionIds::SORT_PICKED_MOVIE_UP:
			state.MoveSelectedMovieUp(GetFocusedMovieIndex(state));
			RefreshAll(state);
			break;
		case VoteActionIds::SORT_PICKED_MOVIE_DOWN:
			state.MoveSelectedMovieDown(GetFocusedMovieIndex(state));
			RefreshAll(state);
			break;
		case VoteActionIds::CANCEL:
			break;
		}
		break;
	case VoteActionIds::SEND:
		switch (option.Id)
		{
		case VoteActionIds::YES:
			result.NextGameModule = new CosmoNetModule;
			{
				ShutterTransition * transition = new ShutterTransition;
				transition->EnableVerticalAnimation = false;
				result.Transition = transition;
			}
			break;
		case VoteActionIds::NO:
			break;
		}
		break;
	}
}

void VoteModule::RefreshAll(GameState& state)
{
	RefreshModel(state);
	RefreshOptionsTexts(state);
	RefreshCursor();
}

void VoteModule::RefreshModel(GameState& state)
{
	optionsAtLeft.clear();
	optionsAtRight.clear();
	for (int i = 0, j = VoteActionIds::AVAILABLE_MOVIE_1; i < state.AvailableMoviesToSelect.size(); i++, j++)
	{
		optionsAtLeft.push_back((VoteActionIds)j);
	}
	if (state.AvailableMoviesToSelect.size() == 0)
		optionsAtLeft.push_back(VoteActionIds::SEND);
	optionsAtLeft.push_back(VoteActionIds::OPTIONS);
	for (int i = 0, j = VoteActionIds::PICKED_MOVIE_1; i < state.SelectedMovies.size(); i++, j++)
	{
		optionsAtRight.push_back((VoteActionIds)j);
	}
}

void VoteModule::RefreshOptionsTexts(GameState& state)
{
	DeleteOptionsTexts();
	optionsTexts.clear();
	optionsTexts[VoteActionIds::OPTIONS] = new AnimatedText();
	optionsTexts[VoteActionIds::OPTIONS]->SetText("Opções", 11);
	optionsTexts[VoteActionIds::SEND] = new AnimatedText();
	optionsTexts[VoteActionIds::SEND]->SetText("Enviar!", 11);
	for (int i = 0, j = VoteActionIds::AVAILABLE_MOVIE_1; i < state.AvailableMoviesToSelect.size(); i++, j++)
	{
		Movie* movie = state.FindMovieById(state.AvailableMoviesToSelect[i]);
		stringstream optionDescription;
		optionDescription << " - " << movie->Name;
		optionsTexts[(VoteActionIds)j] = new AnimatedText();
		optionsTexts[(VoteActionIds)j]->SetText(optionDescription.str(), 11);
	}
	for (int i = 0, j = VoteActionIds::PICKED_MOVIE_1; i < state.SelectedMovies.size(); i++, j++)
	{
		Movie* movie = state.FindMovieById(state.SelectedMovies[i]);
		stringstream optionDescription;
		optionDescription << (i + 1) << ". " << movie->Name;
		optionsTexts[(VoteActionIds)j] = new AnimatedText();
		optionsTexts[(VoteActionIds)j]->SetText(optionDescription.str(), 11);
	}
	leftColumnTitle.SetText(GetLabelForLeftColumnTitle(state), 11, (SC_SCREEN_WIDTH / 2) - 20);
	rightColumnTitle.SetText(GetLabelForRightColumnTitle(state), 11, (SC_SCREEN_WIDTH / 2) - 20);
}

void VoteModule::ResetCursor()
{
	cursorAtRight = false;
	cursorIndex = 0;
}

void VoteModule::RefreshCursor()
{
	if (cursorAtRight && optionsAtRight.size() == 0)
		ResetCursor();
	else
	{
		int max = cursorAtRight ? optionsAtRight.size() - 1 : optionsAtLeft.size() - 1;
		if (cursorIndex > max)
			cursorIndex = max;
	}
}

void VoteModule::DeleteOptionsTexts()
{
	for (auto iterator : optionsTexts)
	{
		delete iterator.second;
	}
}

string VoteModule::GetLabelForLeftColumnTitle(GameState& state)
{
	stringstream ss;
	ss << "DISPONÍVEIS:";
	if (state.AvailableMoviesToSelect.size() > 0)
		ss << " (selecione para escolher o filme #" << (state.SelectedMovies.size() + 1) << ")";
	else
		ss << endl << "-";
	return ss.str();
}

string VoteModule::GetLabelForRightColumnTitle(GameState& state)
{
	stringstream ss;
	ss << "ESCOLHIDOS:";
	if (state.SelectedMovies.size() > 0)
		ss << " (selecione para editar)";
	return ss.str();
}

Movie* VoteModule::GetFocusedMovie(GameState& state)
{
	VoteActionIds actionId = cursorAtRight ? optionsAtRight[cursorIndex] : optionsAtLeft[cursorIndex];
	if (actionId >= VoteActionIds::AVAILABLE_MOVIE_1 && actionId <= AVAILABLE_MOVIE_10)
		return state.FindMovieById(state.AvailableMoviesToSelect[GetFocusedMovieIndex(state)]);
	else if (actionId >= VoteActionIds::PICKED_MOVIE_1 && actionId <= PICKED_MOVIE_10)
		return state.FindMovieById(state.SelectedMovies[GetFocusedMovieIndex(state)]);
	return nullptr;
}

int VoteModule::GetFocusedMovieIndex(GameState& state)
{
	VoteActionIds actionId = cursorAtRight ? optionsAtRight[cursorIndex] : optionsAtLeft[cursorIndex];
	if (actionId >= VoteActionIds::AVAILABLE_MOVIE_1 && actionId <= AVAILABLE_MOVIE_10)
		return actionId - AVAILABLE_MOVIE_1;
	else if (actionId >= VoteActionIds::PICKED_MOVIE_1 && actionId <= PICKED_MOVIE_10)
		return actionId - PICKED_MOVIE_1;
	return 0;
}
