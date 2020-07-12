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
	for (pair<MovieId, SDL_Surface*> element : moviesImages)
	{
		SDL_FreeSurface(element.second);
	}
	for (pair<CharacterId, SDL_Surface*> element : charactersImages)
	{
		SDL_FreeSurface(element.second);
	}
	for (pair<CharacterId, SDL_Surface*> element : smallCharactersImages)
	{
		SDL_FreeSurface(element.second);
	}
	Mix_FreeChunk(NavigateSound);
	Mix_FreeChunk(SelectSound);
	Mix_FreeChunk(EnterSound);
	Mix_FreeChunk(StartSound);
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
	moviesImages[MovieId::WASP_NETWORK] = IMG_Load("Images/WaspNetwork.png");
	moviesImages[MovieId::O_BARCO] = IMG_Load("Images/OBarco.png");
	moviesImages[MovieId::AMANTES_ETERNOS] = IMG_Load("Images/AmantesEternos.png");
	moviesImages[MovieId::EDIFICIO_MASTER] = IMG_Load("Images/EdificioMaster.png");
	moviesImages[MovieId::LA_BAMBA] = IMG_Load("Images/LaBamba.png");
	moviesImages[MovieId::HIGH_LIFE] = IMG_Load("Images/HighLife.png");
	NavigateSound = Mix_LoadWAV("Audio/Navigate1.wav");
	SelectSound = Mix_LoadWAV("Audio/Select.wav");
	EnterSound = Mix_LoadWAV("Audio/Enter.wav");
	StartSound = Mix_LoadWAV("Audio/Start.wav");
}

SDL_Surface* ResourcesManager::GetMovieImage(MovieId id)
{
	return moviesImages[id];
}

SDL_Surface* ResourcesManager::GetCharacterImage(CharacterId id)
{
	return charactersImages[id];
}

SDL_Surface* ResourcesManager::GetCharacterSmallImage(CharacterId id)
{
	return smallCharactersImages[id];
}
