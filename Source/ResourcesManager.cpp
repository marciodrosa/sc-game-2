#include "ResourcesManager.h"
#include <SDL_image.h>

using namespace sc;
using namespace std;

ResourcesManager* ResourcesManager::singleton = nullptr;

ResourcesManager::ResourcesManager()
{
	NavigateSound = nullptr;
	SelectSound = nullptr;
}

ResourcesManager::~ResourcesManager()
{
	Mix_FreeChunk(NavigateSound);
	Mix_FreeChunk(SelectSound);
	Mix_FreeChunk(EnterSound);
	Mix_FreeChunk(StartSound);
	Mix_FreeChunk(CosmoNetOkSound);
}

ResourcesManager* ResourcesManager::Get()
{
	if (singleton == nullptr)
		singleton = new ResourcesManager;
	return singleton;
}

void ResourcesManager::Release()
{
	if (singleton != nullptr)
	{
		delete singleton;
		singleton = nullptr;
	}
}

void ResourcesManager::LoadResources()
{
	HandSprite.LoadContentFromFile("Images/Hand.png");
	HandSprite.CenterPivot();
	HandSprite.RightPivot();
	NavigateSound = Mix_LoadWAV("Audio/Navigate1.wav");
	SelectSound = Mix_LoadWAV("Audio/Select2.wav");
	EnterSound = Mix_LoadWAV("Audio/Enter.wav");
	StartSound = Mix_LoadWAV("Audio/Start.wav");
	CosmoNetOkSound = Mix_LoadWAV("Audio/CosmoNetOk.wav");
}
