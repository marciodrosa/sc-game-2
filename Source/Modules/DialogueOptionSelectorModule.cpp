#include "DialogueOptionSelectorModule.h"
#include "Constants.h"
#include "RenderElements/StripesTransition.h"
#include "ResourcesManager.h"
#include "EnterNameModule.h"
#include "RenderElements/StripesTransition.h"
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
	for (string key : state.DialogueOptions)
	{
		DialogueLine& line = state.CurrentDialogue.Lines[key];
		if (line.Character == CharacterId::PLAYER)
		{
			stringstream ss;
			ss << '"' << line.Text << '"';
			options.push_back(AnimatedText());
			options.back().SetText(ss.str(), 11);
			options.back().CenterPivot();
			options.back().LeftPivot();
		}
	}
	handSprite = &ResourcesManager::Get()->HandSprite;
}

void DialogueOptionSelectorModule::Update(GameState& state, ModuleResult& result)
{
}

void DialogueOptionSelectorModule::Render(GameState& state, SDL_Renderer* renderer)
{
	int y = SC_SCREEN_HEIGHT - 20;
	for (int i = options.size() - 1; i >= 0; i--)
	{
		AnimatedText& option = options[i];
		option.RenderAt(renderer, 30, y);
		if (state.CurrentDialogueLineKey == state.DialogueOptions[i])
			handSprite->RenderAt(renderer, 25, y);
		y -= option.Height;
	}
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
		if (state.CurrentDialogueLineKey == "player.myNameIs")
		{
			result.NextGameModule = new EnterNameModule;
			result.Transition = new StripesTransition;
		}
		else
			result.FinishModule = true;
	}
}

int DialogueOptionSelectorModule::GetIndexOfCurrentSelectedOption(GameState& state)
{
	for (int i = 0; i < state.DialogueOptions.size(); i++)
	{
		if (state.CurrentDialogueLineKey == state.DialogueOptions[i])
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
	state.CurrentDialogueLineKey = state.DialogueOptions[newIndex];
}
