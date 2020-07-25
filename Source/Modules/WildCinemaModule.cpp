#include "WildCinemaModule.h"
#include "Constants.h"
#include "RenderElements/StripesTransition.h"
#include "RenderElements/ShutterTransition.h"
#include "LukaModule.h"
#include "MusicPlayer.h"
#include <sstream>

using namespace sc;
using namespace std;

WildCinemaModule::WildCinemaModule()
{
}

WildCinemaModule::~WildCinemaModule()
{
}

void WildCinemaModule::Start(GameState& state, ModuleResult& result)
{
	text.SetText("UM CINEMA SELVAGEM APARECE!!!", 10);
	text.SetAnimated();
	cinema.LoadContentFromFile("Images/MovieTheater.png");
	cinema.CenterPivot();
	text.CenterPivot();
	text.TopPivot();
	x = SC_SCREEN_WIDTH + cinema.PivotX;
	MusicPlayer::Get()->PlayGameMusic();
	ShutterTransition* transition = new ShutterTransition;
	transition->EnableHorizontalAnimation = false;
	result.Transition = transition;
}

void WildCinemaModule::Update(GameState& state, ModuleResult& result)
{
}

void WildCinemaModule::Render(GameState& state, SDL_Renderer* renderer)
{
	background.RenderAt(renderer, 0, 0);
	if (!state.IsInModuleInTransition)
	{
		x -= 30;
		if (x < SC_SCREEN_WIDTH / 2)
			x = SC_SCREEN_WIDTH / 2;
		cinema.RenderAt(renderer, x, (SC_SCREEN_HEIGHT / 2) - 20);
		text.RenderAt(renderer, SC_SCREEN_WIDTH / 2, 180);
	}
	if (!text.IsAnimating() && !state.IsInModuleInTransition && !state.IsInModuleOutTransition)
		pressEnterIndicator.RenderAt(renderer, 0, 0);
}

void WildCinemaModule::Finish(GameState& state)
{
}

void WildCinemaModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		state.CurrentDialogue = DialogueTree::InitialDialogueTree();
		result.NextGameModule = new LukaModule();
		result.Transition = new StripesTransition;
	}
}
