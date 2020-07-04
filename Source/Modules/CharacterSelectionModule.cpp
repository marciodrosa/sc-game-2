#include "CharacterSelectionModule.h"
#include "IntroModule.h"
#include "Constants.h"
#include "ResourcesManager.h"
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;
using namespace sc;

CharacterSelectionModule::CharacterSelectionModule()
{
	selectionFinished = false;
}

CharacterSelectionModule::~CharacterSelectionModule()
{
	for (CharacterSelectionIcon* characterIcon : characterIcons)
	{
		delete characterIcon;
	}
}

void CharacterSelectionModule::Start(GameState& state)
{
	for (Character& character : state.Characters)
	{
		characterIcons.push_back(new CharacterSelectionIcon(&character));
	}
	mainLabelText.SetText("Selecione o seu cinéfilo:", 24);
	hands.Left = true;
	hands.Right = true;
	hands.Ok = true;
}

void CharacterSelectionModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	mainLabelText.Render(render, (SC_SCREEN_WIDTH - mainLabelText.GetWidth()) / 2, 10);
	int totalCharactersWidth = (characterIcons.size() * 42) - 10;
	int x = (SC_SCREEN_WIDTH - totalCharactersWidth) / 2;
	int y = (SC_SCREEN_HEIGHT / 2) - 16;
	for (CharacterSelectionIcon* characterIcon : characterIcons)
	{
		characterIcon->Render(state, render, x, y);
		x += 42;
	}
	DrawCharacterName(state, render);
	hands.Render(render, (SC_SCREEN_WIDTH - hands.GetWidth()) / 2, SC_SCREEN_HEIGHT - hands.GetHeight());
	if (selectionFinished)
		result.NextGameModule = new IntroModule;
}

void CharacterSelectionModule::DrawCharacterName(GameState& state, SDL_Renderer* render)
{
	characterNameText.SetText(state.Characters[state.SelectedCharacterIndex].Name, 24);
	characterNameText.Render(render, (SC_SCREEN_WIDTH - characterNameText.GetWidth()) / 2, (SC_SCREEN_HEIGHT / 2) + 26);
}

void CharacterSelectionModule::Finish(GameState& state)
{
}

void CharacterSelectionModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		result.DisableInput = true;
		characterIcons[state.SelectedCharacterIndex]->Blink(this);
		Mix_PlayChannel(1, ResourcesManager::Get()->SelectSound, 0);
	}
	else if (inputEvent.keysym.sym == SDLK_LEFT)
	{
		state.SelectedCharacterIndex--;
		if (state.SelectedCharacterIndex < 0)
			state.SelectedCharacterIndex = state.Characters.size() - 1;
		Mix_PlayChannel(1, ResourcesManager::Get()->NavigateSound, 0);
	}
	else if (inputEvent.keysym.sym == SDLK_RIGHT)
	{
		state.SelectedCharacterIndex++;
		if (state.SelectedCharacterIndex >= state.Characters.size())
			state.SelectedCharacterIndex = 0;
		Mix_PlayChannel(1, ResourcesManager::Get()->NavigateSound, 0);
	}
}

void CharacterSelectionModule::OnAnimationEnded()
{
	selectionFinished = true;
}
