#include "EndingModule.h"
#include "Constants.h"
#include "MusicPlayer.h"

using namespace std;
using namespace sc;

EndingModule::EndingModule()
{
}

EndingModule::~EndingModule()
{
}

void EndingModule::Start(GameState& state, ModuleResult& result)
{
	theEndLabelText.SetText("FIM", 20);
	theEndLabelText.CenterPivot();
	theEndLabelTextShadow.SetText("FIM", 20, 0, 0, 0, 0);
	theEndLabelTextShadow.CenterPivot();
	MusicPlayer::Get()->PlayTitleMusic();
}

void EndingModule::Update(GameState& state, ModuleResult& result)
{
}

void EndingModule::Render(GameState& state, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderFillRect(renderer, nullptr);
	theEndLabelTextShadow.RenderAt(renderer, (SC_SCREEN_WIDTH / 2) + 2, (SC_SCREEN_HEIGHT / 2) + 2);
	theEndLabelText.RenderAt(renderer, SC_SCREEN_WIDTH / 2, SC_SCREEN_HEIGHT / 2);
}

void EndingModule::Finish(GameState& state)
{
}

void EndingModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
		result.FinishModule = true;
}
