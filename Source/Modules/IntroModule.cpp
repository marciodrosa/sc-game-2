#include "IntroModule.h"
#include "Constants.h"
#include "MovieModule.h"
#include "MusicPlayer.h"
#include "ResourcesManager.h"
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

void IntroModule::Start(GameState& state)
{
	stringstream ss;
	ss << "É chegado o momento em que a escolha mais "
		<< "importante dos próximos dias deve ser feita: "
		<< "o filme da semana da SEGUNDA CINÉFILA." << endl << endl
		<< "Consulte os filmes a seguir e vote "
		<< "com sabedoria.";
	text.SetText(ss.str(), 14, 300);
	hands.Ok = true;
	MusicPlayer::Get()->PlayGameMusic();
}

void IntroModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	text.Render(render, (SC_SCREEN_WIDTH - text.GetWidth()) / 2, (SC_SCREEN_HEIGHT - text.GetHeight()) / 2);
	hands.Render(render, (SC_SCREEN_WIDTH - hands.GetWidth()) / 2, SC_SCREEN_HEIGHT - hands.GetHeight());
}

void IntroModule::Finish(GameState& state)
{
}

void IntroModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		result.NextGameModule = new MovieModule;
		Mix_PlayChannel(1, ResourcesManager::Get()->EnterSound, 0);
	}
}
