#include "EnterNameModule.h"
#include "LukaModule.h"
#include "Constants.h"
#include "ResourcesManager.h"
#include <sstream>

using namespace sc;
using namespace std;

EnterNameModule::EnterNameModule()
{
	currentName = nullptr;
}

EnterNameModule::~EnterNameModule()
{

}

void EnterNameModule::Start(GameState& state, ModuleResult& result)
{
	currentName = &state.PlayerName;
	label.SetText("Digite o seu nome:", 16);
	label.CenterPivot();
	RefreshNameLabel();
}

void EnterNameModule::Update(GameState& state, ModuleResult& result)
{

}

void EnterNameModule::Render(GameState& state, SDL_Renderer* renderer)
{
	label.RenderAt(renderer, SC_SCREEN_WIDTH / 2, 20);
	nameLabel.RenderAt(renderer, SC_SCREEN_WIDTH / 2, SC_SCREEN_HEIGHT / 2);
	if (currentName->size() > 0)
		pressEnterIndicator.RenderAt(renderer, 0, 0);
}

void EnterNameModule::Finish(GameState& state)
{

}

void EnterNameModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if ((inputEvent.keysym.sym >= 'A' && inputEvent.keysym.sym <= 'Z') || (inputEvent.keysym.sym >= 'a' && inputEvent.keysym.sym <= 'z'))
	{
		if (currentName->size() < 6)
		{
			Mix_PlayChannel(1, ResourcesManager::Get()->EnterSound, 0);
			stringstream ss;
			ss << *currentName << (char)toupper(inputEvent.keysym.sym);
			*currentName = ss.str();
			RefreshNameLabel();
		}
	}
	else if (inputEvent.keysym.sym == SDLK_BACKSPACE && currentName->size() > 0)
	{
		Mix_PlayChannel(1, ResourcesManager::Get()->EnterSound, 0);
		*currentName = currentName->substr(0, currentName->size() - 1);
		RefreshNameLabel();
	}
	else if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		if (currentName->size() > 0)
		{
			Mix_PlayChannel(1, ResourcesManager::Get()->SelectSound, 0);
			state.CurrentDialogue = DialogueTree::AfterNameDialogueTree();
			result.NextGameModule = new LukaModule();
		}
	}
}

void EnterNameModule::RefreshNameLabel()
{
	stringstream ss;
	for (int i = 0; i < 6; i++)
	{
		if (i < currentName->size())
			ss << (*currentName)[i];
		else
			ss << '_';
		if (i < 5)
			ss << ' ';
	}
	nameLabel.SetText(ss.str(), 20);
	nameLabel.CenterPivot();
}
