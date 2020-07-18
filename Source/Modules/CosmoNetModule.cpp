#include "CosmoNetModule.h"
#include "RenderElements/ShutterTransition.h"
#include "Constants.h"

using namespace sc;
using namespace std;

CosmoNetModule::CosmoNetModule()
{

}

CosmoNetModule::~CosmoNetModule()
{

}

void CosmoNetModule::Start(GameState& state, ModuleResult& result)
{
	logo.LoadContentFromFile("Images/CosmoNet.png");
	logo.CenterPivot();
	titleLabel.SetText("CosmoNet", 22);
	titleLabel.CenterPivot();
	titleLabel.TopPivot();
	statusLabel.SetText("Conectando à rede....", 11);
	statusLabel.CenterPivot();
	statusLabel.TopPivot();
	ShutterTransition* transition = new ShutterTransition;
	transition->EnableVerticalAnimation = false;
	result.Transition = transition;
	transition->Listener = this;
}

void CosmoNetModule::Update(GameState& state, ModuleResult& result)
{

}

void CosmoNetModule::Render(GameState& state, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 122, 255, 255);
	SDL_RenderFillRect(renderer, nullptr);
	logo.RenderAt(renderer, SC_SCREEN_WIDTH / 2, (SC_SCREEN_HEIGHT / 2) - 20);
	titleLabel.RenderAt(renderer, SC_SCREEN_WIDTH / 2, (SC_SCREEN_HEIGHT / 2) + (logo.Height / 2));
	if (!state.IsInModuleInTransition && !state.IsInModuleOutTransition)
		statusLabel.RenderAt(renderer, SC_SCREEN_WIDTH / 2, 200);
}

void CosmoNetModule::Finish(GameState& state)
{

}

void CosmoNetModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
}

void CosmoNetModule::OnAnimationEnded(RenderElement* renderElement)
{

}
