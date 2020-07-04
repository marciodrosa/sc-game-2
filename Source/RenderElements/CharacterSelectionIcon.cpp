#include "CharacterSelectionIcon.h"
#include "ResourcesManager.h"

using namespace sc;

CharacterSelectionIcon::CharacterSelectionIcon(Character* character)
{
	this->character = character;
	this->characterTexture = nullptr;
	this->selectionTexture = nullptr;
	this->blinking = false;
	this->blinksCount = 0;
	this->blinkAnimationListener = nullptr;
}

CharacterSelectionIcon::~CharacterSelectionIcon()
{
	SDL_DestroyTexture(characterTexture);
	SDL_DestroyTexture(selectionTexture);
}

void CharacterSelectionIcon::Render(GameState& state, SDL_Renderer* render, int x, int y)
{
	SDL_Surface* characterImage = ResourcesManager::Get()->GetCharacterSmallImage(character->Id);
	if (characterTexture == nullptr)
		characterTexture = SDL_CreateTextureFromSurface(render, characterImage);
	if (selectionTexture == nullptr)
		selectionTexture = SDL_CreateTextureFromSurface(render, ResourcesManager::Get()->CharacterCursorImage);
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = characterImage->w;
	destRect.h = characterImage->h;
	SDL_RenderCopy(render, characterTexture, nullptr, &destRect);
	bool isSelected = state.Characters[state.SelectedCharacterIndex].Id == this->character->Id;
	if (isSelected)
	{
		bool renderSelection = !blinking || (blinksCount % 2) == 0;
		if (renderSelection)
			SDL_RenderCopy(render, selectionTexture, nullptr, &destRect);
	}
	if (blinking)
	{
		blinksCount++;
		if (blinksCount > 30)
		{
			blinking = false;
			if (blinkAnimationListener != nullptr)
				blinkAnimationListener->OnAnimationEnded();
		}
	}
}

void CharacterSelectionIcon::Blink(AnimationListener* listener)
{
	blinking = true;
	blinkAnimationListener = listener;
	blinksCount = 0;
}
