#include "EndingModule.h"
#include "Constants.h"
#include "ResourcesManager.h"
#include "MovieModule.h"
#include "MusicPlayer.h"
#include <SDL_image.h>
#include <sstream>

using namespace std;
using namespace sc;

EndingModule::EndingModule()
{
	characterTexture = nullptr;
}

EndingModule::~EndingModule()
{
	SDL_DestroyTexture(characterTexture);
}

void EndingModule::Start(GameState& state)
{
	Character& character = state.Characters[state.SelectedCharacterIndex];
	stringstream endingLabel;
	stringstream characterLabel;
	endingLabel << "E assim, com muita sabedoria, " << character.Name << " fez a escolha de seus filmes favoritos para a SEGUNDA CINÉFILA vindoura.";
	characterLabel << '"' << character.EndingLine << '"';
	mainLabelText.SetText(endingLabel.str(), 11, SC_SCREEN_WIDTH - 20);
	characterLabelText.SetText(characterLabel.str(), 11, SC_SCREEN_WIDTH - 20);
	theEndLabelText.SetText("FIM", 11, 0);
	hands.Left = true;
	hands.Ok = true;
	MusicPlayer::Get()->PlayTitleMusic();
}

void EndingModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	Character& Character = state.Characters[state.SelectedCharacterIndex];
	SDL_Surface* characterImage = ResourcesManager::Get()->GetCharacterImage(Character.Id);
	if (characterTexture == nullptr)
		characterTexture = SDL_CreateTextureFromSurface(render, characterImage);
	mainLabelText.Render(render, (SC_SCREEN_WIDTH - mainLabelText.GetWidth()) / 2, 10);
	SDL_Rect destRect;
	destRect.x = (SC_SCREEN_WIDTH / 2) - (characterImage->w / 2);
	destRect.y = (SC_SCREEN_HEIGHT / 2) - (characterImage->h / 2);
	destRect.w = characterImage->w;
	destRect.h = characterImage->h;
	SDL_RenderCopy(render, characterTexture, nullptr, &destRect);
	int y = destRect.y + destRect.h + 10;
	characterLabelText.Render(render, (SC_SCREEN_WIDTH - characterLabelText.GetWidth()) / 2, y);
	theEndLabelText.Render(render, (SC_SCREEN_WIDTH - theEndLabelText.GetWidth()) / 2, y + characterLabelText.GetHeight() + 10);
	hands.Render(render, (SC_SCREEN_WIDTH - hands.GetWidth()) -10, SC_SCREEN_HEIGHT - hands.GetHeight());
}

void EndingModule::Finish(GameState& state)
{
}

void EndingModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
		result.FinishGame = true;
	else if (inputEvent.keysym.sym == SDLK_LEFT)
		result.NextGameModule = new MovieModule;
}
