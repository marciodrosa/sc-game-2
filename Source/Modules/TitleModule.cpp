#include "TitleModule.h"
#include "IntroModule.h"
#include "Constants.h"
#include "MusicPlayer.h"
#include "ResourcesManager.h"
#include "RenderElements/BlindsTransition.h"
#include "RenderElements/ShutterTransition.h"
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace sc;

TitleModule::TitleModule()
{
	backgroundX = 0;
}

TitleModule::~TitleModule()
{
}

void TitleModule::Start(GameState& state, ModuleResult& result)
{
	pressEnterIndicator.SetLabel("Pressione ENTER para come�ar");
	logo.LoadContentFromFile("Images/LogoText.png");
	background.LoadContentFromFile("Images/LogoBG.png");
	MusicPlayer::Get()->PlayTitleMusic();
	ShutterTransition* shutterTransition = new ShutterTransition;
	shutterTransition->EnableVerticalAnimation = false;
	result.Transition = shutterTransition;
}

void TitleModule::Update(GameState& state, ModuleResult& result)
{
}

void TitleModule::Render(GameState& state, SDL_Renderer* renderer)
{
	background.RenderAt(renderer, backgroundX, 0);
	background.RenderAt(renderer, backgroundX + background.Width, 0);
	backgroundX--;
	if (backgroundX < -background.Width)
		backgroundX = 0;
	logo.RenderAt(renderer, 0, 0);
	if (!state.IsInModuleInTransition && !state.IsInModuleOutTransition)
		pressEnterIndicator.RenderAt(renderer, 0, 0);
}

void TitleModule::Finish(GameState& state)
{
}

void TitleModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		Mix_PlayChannel(1, ResourcesManager::Get()->StartSound, 0);
		result.NextGameModule = new IntroModule;
		result.Transition = new BlindsTransition;
	}
}

void TitleModule::OnAnimationEnded(RenderElement* renderElement)
{

}
