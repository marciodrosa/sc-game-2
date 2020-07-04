#include "ExtraModule.h"
#include "Constants.h"
#include "MovieModule.h"
#include "MusicPlayer.h"
#include <SDL_image.h>
#include <sstream>

using namespace std;
using namespace sc;

ExtraModule::ExtraModule()
{
}

ExtraModule::~ExtraModule()
{
}

void ExtraModule::Start(GameState& state)
{
	text.SetText("EXTRA x1", 20);
	hands.Left = true;
	hands.Right = true;
	hands.Ok = true;
	MusicPlayer::Get()->PlayExtraMusic();
}

void ExtraModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	blinkingBackground.Render(render);
	text.Render(render, (SC_SCREEN_WIDTH - text.GetWidth()) / 2, (SC_SCREEN_HEIGHT - text.GetHeight()) / 2);
	hands.Render(render, (SC_SCREEN_WIDTH - hands.GetWidth()) / 2, SC_SCREEN_HEIGHT - hands.GetHeight());
}

void ExtraModule::Finish(GameState& state)
{
}

void ExtraModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RIGHT || inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		result.NextGameModule = new MovieModule;
	}
	else if (inputEvent.keysym.sym == SDLK_LEFT)
	{
		state.CurrentMovieIndex--;
		if (state.CurrentMovieIndex < 0)
			state.CurrentMovieIndex = 0;
		else
			result.NextGameModule = new MovieModule;
	}
}
