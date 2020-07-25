#include "PopUpModule.h"
#include "Constants.h"
#include "ResourcesManager.h"

using namespace sc;
using namespace std;

PopUpOption::PopUpOption(int id, string text)
{
	this->Id = id;
	this->Text = text;
}

PopUpModule::PopUpModule(int id, string title, vector<PopUpOption>& options, PopUpListener* listener)
{
	Listener = listener;
	this->id = id;
	this->options = options;
	vector<string> optionsStrings;
	for (PopUpOption& option : options)
	{
		optionsStrings.push_back(option.Text);
	}
	popUp.SetContent(title, optionsStrings);
	popUp.CenterPivot();
}

PopUpModule::~PopUpModule()
{
}

void PopUpModule::Start(GameState& state, ModuleResult& result)
{
	popUp.Animate();
}

void PopUpModule::Update(GameState& state, ModuleResult& result)
{
}

void PopUpModule::Render(GameState& state, SDL_Renderer* renderer)
{
	popUp.RenderAt(renderer, SC_SCREEN_WIDTH / 2, SC_SCREEN_HEIGHT / 2);
}

void PopUpModule::Finish(GameState& state)
{
}

void PopUpModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (!popUp.IsAnimating())
	{
		if (inputEvent.keysym.sym == SDLK_UP)
		{
			Mix_PlayChannel(1, ResourcesManager::Get()->NavigateSound, 0);
			popUp.SelectedOption--;
			if (popUp.SelectedOption < 0)
				popUp.SelectedOption = 0;
		}
		else if (inputEvent.keysym.sym == SDLK_DOWN)
		{
			Mix_PlayChannel(1, ResourcesManager::Get()->NavigateSound, 0);
			popUp.SelectedOption++;
			if (popUp.SelectedOption >= options.size())
				popUp.SelectedOption = options.size() - 1;
		}
		else if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
		{
			Mix_PlayChannel(1, ResourcesManager::Get()->SelectSound, 0);
			int index = popUp.SelectedOption;
			if (Listener != nullptr)
				Listener->OnPopUpOptionSelected(id, options[index], state, result);
			if (result.NextGameModule == nullptr)
				result.FinishModule = true;
		}
	}
}
