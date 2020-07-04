#include "MovieModule.h"
#include "Constants.h"
#include "ResourcesManager.h"
#include "EndingModule.h"
#include "ExtraModule.h"
#include "MusicPlayer.h"
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;
using namespace sc;

MovieModule::MovieModule()
{
	movieTexture = nullptr;
}

MovieModule::~MovieModule()
{
	SDL_DestroyTexture(movieTexture);
}

void MovieModule::Start(GameState& state)
{
	Movie& movie = state.Movies[state.CurrentMovieIndex];
	hands.Left = state.CurrentMovieIndex > 0;
	hands.Right = state.CurrentMovieIndex < state.Movies.size() - 1;
	hands.Ok = state.CurrentMovieIndex == state.Movies.size() - 1;
	text.SetText(movie.GetFullDescription(), 11, 160, true, 1, this);
	if (movie.IsExtra)
		MusicPlayer::Get()->PlayExtraMusic();
	else
		MusicPlayer::Get()->PlayGameMusic();
}

void MovieModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	Movie& movie = state.Movies[state.CurrentMovieIndex];
	if (movie.IsExtra)
		blinkingBackground.Render(render);
	SDL_Surface* movieImage = ResourcesManager::Get()->GetMovieImage(movie.Id);
	if (movieTexture == nullptr)
		movieTexture = SDL_CreateTextureFromSurface(render, movieImage);
	SDL_Rect destRect;
	destRect.x = 10;
	destRect.y = (SC_SCREEN_HEIGHT - movieImage->h) / 2;
	destRect.w = movieImage->w;
	destRect.h = movieImage->h;
	SDL_RenderCopy(render, movieTexture, nullptr, &destRect);
	text.Render(render, destRect.x + destRect.w + 10, (SC_SCREEN_HEIGHT - text.GetHeight()) / 2);
	hands.Render(render, 20, SC_SCREEN_HEIGHT - hands.GetHeight() - 20);
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
				result.NextGameModule = new EndingModule;
			}
			else
			{
				if (state.Movies[state.CurrentMovieIndex].IsExtra)
					result.NextGameModule = new ExtraModule;
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

void MovieModule::OnAnimationEnded()
{

}
