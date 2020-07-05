#include "WildCinemaModule.h"
#include "Constants.h"
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
}

void WildCinemaModule::Update(GameState& state, ModuleResult& result)
{
}

void WildCinemaModule::Render(GameState& state, SDL_Renderer* renderer)
{
	x -= 30;
	if (x < SC_SCREEN_WIDTH / 2)
		x = SC_SCREEN_WIDTH / 2;
	background.RenderAt(renderer, 0, 0);
	cinema.RenderAt(renderer, x, (SC_SCREEN_HEIGHT / 2) - 20);
	text.RenderAt(renderer, SC_SCREEN_WIDTH / 2, 180);
}

void WildCinemaModule::Finish(GameState& state)
{
}

void WildCinemaModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
}
