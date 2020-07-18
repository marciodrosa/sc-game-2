#include "DialogueOptionSelectorModule.h"
#include "MovieModule.h"
#include "Constants.h"
#include "RenderElements/StripesTransition.h"
#include "RenderElements/BlindsTransition.h"
#include "ResourcesManager.h"
#include "EnterNameModule.h"
#include <sstream>

using namespace sc;
using namespace std;

DialogueOptionSelectorModule::DialogueOptionSelectorModule()
{
}

DialogueOptionSelectorModule::~DialogueOptionSelectorModule()
{
}

void DialogueOptionSelectorModule::Start(GameState& state, ModuleResult& result)
{
	vector<string> options;
	for (string key : state.DialogueOptions)
	{
		DialogueLine& line = state.CurrentDialogue.Lines[key];
		if (line.Character == CharacterId::PLAYER)
		{
			stringstream ss;
			ss << '"' << line.Text << '"';
			options.push_back(ss.str());
		}
	}
	popUp.SetContent("", options);
	popUp.CenterPivot();
	popUp.BottomPivot();
}

void DialogueOptionSelectorModule::Update(GameState& state, ModuleResult& result)
{
	popUp.SelectedOption = GetIndexOfCurrentSelectedOption(state);
}

void DialogueOptionSelectorModule::Render(GameState& state, SDL_Renderer* renderer)
{
	popUp.RenderAt(renderer, SC_SCREEN_WIDTH / 2, SC_SCREEN_HEIGHT - 5);
}

void DialogueOptionSelectorModule::Finish(GameState& state)
{
}

void DialogueOptionSelectorModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_UP)
		SetIndexOfCurrentSelectedOption(state, GetIndexOfCurrentSelectedOption(state) - 1);
	else if (inputEvent.keysym.sym == SDLK_DOWN)
		SetIndexOfCurrentSelectedOption(state, GetIndexOfCurrentSelectedOption(state) + 1);
	else if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		if (state.CurrentDialogue.CurrentDialogueLineKey == "player.myNameIs")
		{
			result.NextGameModule = new EnterNameModule;
			result.Transition = new BlindsTransition;
		}
		if (state.CurrentDialogue.CurrentDialogueLineKey == "player.reviewMovies")
		{
			state.CurrentMovieIndex = 0;
			result.NextGameModule = new MovieModule(true);
			result.Transition = new BlindsTransition;
		}
		else
			result.FinishModule = true;
	}
}

int DialogueOptionSelectorModule::GetIndexOfCurrentSelectedOption(GameState& state)
{
	for (int i = 0; i < state.DialogueOptions.size(); i++)
	{
		if (state.CurrentDialogue.CurrentDialogueLineKey == state.DialogueOptions[i])
			return i;
	}
	return 0;
}

void DialogueOptionSelectorModule::SetIndexOfCurrentSelectedOption(GameState& state, int newIndex)
{
	if (newIndex < 0)
		newIndex = state.DialogueOptions.size() - 1;
	if (newIndex >= state.DialogueOptions.size())
		newIndex = 0;
	state.CurrentDialogue.CurrentDialogueLineKey = state.DialogueOptions[newIndex];
}
