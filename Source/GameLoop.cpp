#include "GameLoop.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "ResourcesManager.h"
#include "MusicPlayer.h"
#include "Constants.h"
#include "RenderElements/ModuleTransition.h"

using namespace sc;

GameLoop::GameLoop(GameState& state)
{
	sdlInitiated = false;
	this->gameState = &state;
	this->gameModule = nullptr;
	this->subModule = nullptr;
	this->running = false;
	this->moduleInputEnabled = true;
	this->transition = nullptr;
	this->pendingModuleAfterTransition = nullptr;
}

GameLoop::~GameLoop()
{
	SetModule(nullptr);
	SetSubModule(nullptr);
	SetTransition(nullptr, false, nullptr);
	if (pendingModuleAfterTransition != nullptr)
		delete pendingModuleAfterTransition;
	QuitSDLAndResources();
}

void GameLoop::Run()
{
	InitSDLAndResources();
	SDL_Window* window = SDL_CreateWindow("Segunda Cinefila", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SC_SCREEN_WIDTH, SC_SCREEN_HEIGHT, 0);// SDL_WINDOW_FULLSCREEN);
	SDL_ShowCursor(0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	ConfigureViewport(window);
	Loop();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	render = nullptr;
}

void GameLoop::SetModule(GameModule* gameModule)
{
	if (this->gameModule != gameModule)
	{
		SetSubModule(nullptr);
		InitSDLAndResources();
		if (this->gameModule != nullptr)
		{
			this->gameModule->Finish(*gameState);
			delete this->gameModule;
		}
		this->gameModule = gameModule;
		moduleInputEnabled = true;
		if (this->gameModule != nullptr)
		{
			ModuleResult moduleResult;
			this->gameModule->Start(*gameState, moduleResult);
			HandleModuleResult(moduleResult);
		}
	}
}

void GameLoop::SetSubModule(GameModule* subModule)
{
	if (this->subModule != subModule)
	{
		if (this->subModule != nullptr)
		{
			this->subModule->Finish(*gameState);
			delete this->subModule;
		}
		this->subModule = subModule;
		moduleInputEnabled = true;
		if (this->subModule != nullptr)
		{
			ModuleResult moduleResult;
			this->subModule->Start(*gameState, moduleResult);
			HandleModuleResult(moduleResult);
		}
	}
}

void GameLoop::SetTransition(ModuleTransition* transition, bool in, GameModule* pendingModuleAfterTransition)
{
	gameState->IsInModuleInTransition = false;
	gameState->IsInModuleOutTransition = false;
	if (this->transition != nullptr)
		delete transition;
	this->transition = transition;
	this->pendingModuleAfterTransition = pendingModuleAfterTransition;
	if (transition != nullptr)
	{
		if (in)
		{
			gameState->IsInModuleInTransition = true;
			transition->TransitionIn();
		}
		else
		{
			gameState->IsInModuleOutTransition = true;
			transition->TransitionOut();
		}
	}
}

void GameLoop::ConfigureViewport(SDL_Window* window)
{
	SDL_Rect viewport;
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	viewport.x = (windowWidth - SC_SCREEN_WIDTH) / 2;
	viewport.y = (windowHeight - SC_SCREEN_HEIGHT) / 2;
	viewport.w = SC_SCREEN_WIDTH;
	viewport.h = SC_SCREEN_HEIGHT;
	SDL_RenderSetViewport(render, &viewport);
}

void GameLoop::Loop()
{
	running = true;
	while (running)
	{
		LoopUpdate();
	}
}

void GameLoop::LoopUpdate()
{
	unsigned int timeStart = SDL_GetTicks();
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	PoolEvents();
	GameModule* moduleToUpdate = subModule != nullptr ? subModule : gameModule;
	if (moduleToUpdate != nullptr)
	{
		ModuleResult moduleResult;
		moduleToUpdate->Update(*gameState, moduleResult);
		if (moduleToUpdate == subModule)
		{
			SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
			gameModule->Render(*gameState, render);
		}
		moduleToUpdate->Render(*gameState, render);
		HandleModuleResult(moduleResult);
		UpdateTransition();
	}
	RenderMargin();
	SDL_RenderPresent(render);
	unsigned int timeEnd = SDL_GetTicks();
	unsigned int frameTime = timeEnd < timeStart;
	if (frameTime < 33)
		SDL_Delay(33 - frameTime);
}

void GameLoop::UpdateTransition()
{
	if (transition != nullptr)
	{
		transition->RenderAt(render, 0, 0);
		if (transition->TransitionAnimationEnded())
		{
			GameModule* NextModule = pendingModuleAfterTransition;
			SetTransition(nullptr, false, nullptr);
			if (NextModule != nullptr)
				SetModule(NextModule);
		}
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
	if (moduleResult.EnableInput)
		moduleInputEnabled = true;
	if (moduleResult.NextGameModule != nullptr)
	{
		if (moduleResult.Transition == nullptr)
			SetModule(moduleResult.NextGameModule);
		else
			SetTransition(moduleResult.Transition, false, moduleResult.NextGameModule);
	}
	else if (moduleResult.Transition != nullptr)
		SetTransition(moduleResult.Transition, true, nullptr);
	if (moduleResult.FinishModule)
	{
		if (subModule != nullptr)
			SetSubModule(nullptr);
		else
			running = false;
	}
	if (moduleResult.SubModule != nullptr && moduleResult.NextGameModule == nullptr)
		SetSubModule(moduleResult.SubModule);
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
			GameModule* moduleToReceiveInput = subModule != nullptr ? subModule : gameModule;
			if (moduleToReceiveInput != nullptr && moduleInputEnabled && transition == nullptr)
			{
				ModuleResult moduleResult;
				moduleToReceiveInput->HandleInput(*gameState, event.key, moduleResult);
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
