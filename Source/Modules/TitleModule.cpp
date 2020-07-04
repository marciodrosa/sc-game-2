#include "TitleModule.h"
#include "CharacterSelectionModule.h"
#include "Constants.h"
#include "MusicPlayer.h"
#include "ResourcesManager.h"
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace sc;

TitleModule::TitleModule()
{
	logoImage = nullptr;
	logoTexture = nullptr;
}

TitleModule::~TitleModule()
{
	SDL_FreeSurface(logoImage);
	SDL_DestroyTexture(logoTexture);
}

void TitleModule::Start(GameState& state)
{
	logoImage = IMG_Load("Images/Logo.png");
	text.SetText("Comandos: teclas para esquerda, direita e Enter", 11, 300);
	MusicPlayer::Get()->PlayTitleMusic();
}

void TitleModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	if (logoTexture == nullptr)
		logoTexture = SDL_CreateTextureFromSurface(render, logoImage);
	SDL_Rect destRect;
	destRect.x = 0;
	destRect.y = 0;
	destRect.w = SC_SCREEN_WIDTH;
	destRect.h = SC_SCREEN_HEIGHT;
	SDL_RenderCopy(render, logoTexture, nullptr, &destRect);
	text.Render(render, (SC_SCREEN_WIDTH - text.GetWidth()) / 2, 200);
}

void TitleModule::Finish(GameState& state)
{
}

void TitleModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		Mix_PlayChannel(1, ResourcesManager::Get()->StartSound, 0);
		result.NextGameModule = new CharacterSelectionModule;
	}
}
