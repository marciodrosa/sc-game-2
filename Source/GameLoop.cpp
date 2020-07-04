#include "GameLoop.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "ResourcesManager.h"
#include "MusicPlayer.h"
#include "Constants.h"

using namespace sc;

GameLoop::GameLoop(GameState& state)
{
	sdlInitiated = false;
	this->gameState = &state;
	this->gameModule = nullptr;
	this->running = false;
	this->moduleInputEnabled = true;
}

GameLoop::~GameLoop()
{
	SetModule(nullptr);
	QuitSDLAndResources();
}

void GameLoop::Run()
{
	InitSDLAndResources();
	SDL_Window* window = SDL_CreateWindow("Segunda Cinefila", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SC_SCREEN_WIDTH, SC_SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	SDL_ShowCursor(0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	running = true;
	while (running)
	{
		unsigned int timeStart = SDL_GetTicks();
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);
		PoolEvents();
		if (gameModule != nullptr)
		{
			ModuleResult moduleResult;
			gameModule->Update(*gameState, render, moduleResult);
			HandleModuleResult(moduleResult);
		}
		RenderMargin();
		SDL_RenderPresent(render);
		unsigned int timeEnd = SDL_GetTicks();
		unsigned int frameTime = timeEnd < timeStart;
		if (frameTime < 33)
			SDL_Delay(33 - frameTime);
	}
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	render = nullptr;
}

void GameLoop::SetModule(GameModule* gameModule)
{
	if (this->gameModule != gameModule)
	{
		InitSDLAndResources();
		if (this->gameModule != nullptr)
		{
			this->gameModule->Finish(*gameState);
			delete this->gameModule;
		}
		this->gameModule = gameModule;
		moduleInputEnabled = true;
		if (this->gameModule != nullptr)
			this->gameModule->Start(*gameState);
	}
}

void GameLoop::RenderMargin()
{
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = SC_SCREEN_WIDTH;
	rect.h = SC_SCREEN_HEIGHT;
	SDL_RenderDrawRect(render, &rect);
}

void GameLoop::HandleModuleResult(ModuleResult& moduleResult)
{
	if (moduleResult.DisableInput)
		moduleInputEnabled = false;
	if (moduleResult.NextGameModule != nullptr)
		SetModule(moduleResult.NextGameModule);
	if (moduleResult.FinishGame)
		running = false;
}

void GameLoop::PoolEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			running = false;
		else if (event.type == SDL_KEYDOWN)
		{
			if (gameModule != nullptr && moduleInputEnabled)
			{
				ModuleResult moduleResult;
				gameModule->HandleInput(*gameState, event.key, moduleResult);
				HandleModuleResult(moduleResult);
			}
		}
	}
}

void GameLoop::InitSDLAndResources()
{
	if (!sdlInitiated)
	{
		sdlInitiated = true;
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		TTF_Init();
		Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
		ResourcesManager::Get()->LoadResources();
		MusicPlayer::Get()->LoadMusics();
	}
}

void GameLoop::QuitSDLAndResources()
{
	ResourcesManager::Release();
	MusicPlayer::Release();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}
