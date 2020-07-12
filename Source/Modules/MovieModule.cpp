#include "MovieModule.h"
#include "Constants.h"
#include "ResourcesManager.h"
#include "EndingModule.h"
#include "RingoModule.h"
#include "LukaModule.h"
#include "MusicPlayer.h"
#include "RenderElements/ShutterTransition.h"
#include "RenderElements/BlindsTransition.h"
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;
using namespace sc;

MovieModule::MovieModule(bool includeTransitionIn)
{
	this->includeTransitionIn = includeTransitionIn;
}

MovieModule::~MovieModule()
{
}

void MovieModule::Start(GameState& state, ModuleResult& result)
{
	Movie& movie = state.Movies[state.CurrentMovieIndex];
	text.SetText(movie.GetFullDescription(), 11, 160);
	text.SetAnimated();
	text.Listener = this;
	text.CenterPivot();
	text.LeftPivot();
	movieImage.LoadContentFromFile(movie.Image);
	movieImage.CenterPivot();
	movieImage.LeftPivot();
	if (movie.IsExtra)
		MusicPlayer::Get()->PlayExtraMusic();
	else
		MusicPlayer::Get()->PlayGameMusic();
	if (includeTransitionIn)
		result.Transition = new BlindsTransition;
}

void MovieModule::Update(GameState& state, ModuleResult& result)
{
}

void MovieModule::Render(GameState& state, SDL_Renderer* renderer)
{
	Movie& movie = state.Movies[state.CurrentMovieIndex];
	if (movie.IsExtra)
		blinkingBackground.RenderAt(renderer, 0, 0);
	movieImage.RenderAt(renderer, 10, SC_SCREEN_HEIGHT / 2);
	text.RenderAt(renderer, movieImage.Width + 20, SC_SCREEN_HEIGHT / 2);
}

void MovieModule::Finish(GameState& state)
{
}

void MovieModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	Mix_PlayChannel(1, ResourcesManager::Get()->EnterSound, 0);
	if (text.IsAnimating())
		text.ForceFinishAnimation();
	else
	{
		if (inputEvent.keysym.sym == SDLK_RIGHT || inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
		{
			state.CurrentMovieIndex++;
			if (state.CurrentMovieIndex >= state.Movies.size())
			{
				state.CurrentMovieIndex = state.Movies.size() - 1;
				state.CurrentDialogue = DialogueTree::VotingDialogueTree();
				result.NextGameModule = new LukaModule;
				result.Transition = new ShutterTransition;
			}
			else
			{
				if (state.Movies[state.CurrentMovieIndex].IsExtra && !state.RingoAlreadyAppeared)
					result.NextGameModule = new RingoModule;
				else
					result.NextGameModule = new MovieModule;
			}
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
}

void MovieModule::OnAnimationEnded(RenderElement* renderElement)
{

}
