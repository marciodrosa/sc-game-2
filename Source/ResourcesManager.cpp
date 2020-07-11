#include "ResourcesManager.h"
#include <SDL_image.h>

using namespace sc;
using namespace std;

ResourcesManager* ResourcesManager::singleton = nullptr;

ResourcesManager::ResourcesManager()
{
	CharacterCursorImage = nullptr;
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
	SDL_FreeSurface(CharacterCursorImage);
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
	moviesImages[MovieId::DESTACAMENTO_BLOOD] = IMG_Load("Images/DestacamentoBlood.png");
	moviesImages[MovieId::UM_PEQUENO_FAVOR] = IMG_Load("Images/UmPequenoFavor.png");
	moviesImages[MovieId::NASCIDO_EM_4_DE_JULHO] = IMG_Load("Images/NascidoEm4DeJulho.png");
	moviesImages[MovieId::PERSONAL_SHOPPER] = IMG_Load("Images/PersonalShopper.png");
	moviesImages[MovieId::PSICOPATA_AMERICANO] = IMG_Load("Images/PsicopataAmericano.png");
	moviesImages[MovieId::EMBRIAGADO_DE_AMOR] = IMG_Load("Images/EmbriagadoDeAmor.png");
	CharacterCursorImage = IMG_Load("Images/CharacterCursor.png");
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
