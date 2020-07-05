#include "IntroModule.h"
#include "Constants.h"
#include "MusicPlayer.h"
#include "ResourcesManager.h"
#include "RenderElements/BlindsTransition.h"
#include "RenderElements/ShutterTransition.h"
#include "WildCinemaModule.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <sstream>

using namespace std;
using namespace sc;

IntroModule::IntroModule()
{
}

IntroModule::~IntroModule()
{
}

void IntroModule::Start(GameState& state, ModuleResult& result)
{
	stringstream ss;
	ss << "2020." << endl << endl
		<< "Uma epidemia devasta o mundo e assola os cinéfilos, que passam a viver em quarentena, fora de seu habitat natural. "
		<< "Há poucas esperanças." << endl << endl
		<< "Até que, um dia....";
	text.SetText(ss.str(), 14, 300);
	text.SetAnimated(true);
	text.CenterPivot();
	textShadow.SetText(ss.str(), 14, 300, 0, 0, 0);
	textShadow.SetAnimated(true);
	textShadow.CenterPivot();
	result.Transition = new BlindsTransition;
}

void IntroModule::Update(GameState& state, ModuleResult& result)
{
}

void IntroModule::Render(GameState& state, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
	SDL_RenderFillRect(renderer, nullptr);
	if (!state.IsInModuleInTransition)
	{
		textShadow.RenderAt(renderer, (SC_SCREEN_WIDTH / 2) + 2, (SC_SCREEN_HEIGHT / 2) + 2);
		text.RenderAt(renderer, SC_SCREEN_WIDTH / 2, SC_SCREEN_HEIGHT / 2);
	}
}

void IntroModule::Finish(GameState& state)
{
}

void IntroModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		result.NextGameModule = new WildCinemaModule;
		ShutterTransition* transition = new ShutterTransition;
		transition->EnableHorizontalAnimation = false;
		result.Transition = transition;
		Mix_PlayChannel(1, ResourcesManager::Get()->EnterSound, 0);
	}
}
