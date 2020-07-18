#include "PopUpRenderElement.h"
#include "ResourcesManager.h"
#include <cmath>

using namespace sc;
using namespace std;

#define POPUP_HORIZONTAL_MARGIN 10
#define POPUP_VERTICAL_MARGIN 5
#define SPACE_BETWEEN_HAND_AND_TEXT 5

PopUpRenderElement::PopUpRenderElement(const PopUpRenderElement& other)
{
}

PopUpRenderElement::PopUpRenderElement()
{
	SelectedOption = 0;
	handSprite = &ResourcesManager::Get()->HandSprite;
	animating = false;
	animationPhase = 0;
}

PopUpRenderElement::~PopUpRenderElement()
{
	vector<string> temp;
	SetContent("", temp);
}

void PopUpRenderElement::SetContent(std::string title, std::vector<std::string>& options, int maxWidth)
{
	this->title.SetText(title, 11, 0);
	for (AnimatedText* option : this->options)
	{
		delete option;
	}
	this->options.clear();
	for (string option : options)
	{
		AnimatedText* optionText = new AnimatedText;
		optionText->SetText(option, 11);
		optionText->CenterPivot();
		optionText->LeftPivot();
		this->options.push_back(optionText);
	}
	RecalculateSize();
}

void PopUpRenderElement::Animate()
{
	animating = true;
	animationPhase = 0;
}

bool PopUpRenderElement::IsAnimating()
{
	return animating;
}

void PopUpRenderElement::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	SDL_Rect bgRect;
	if (animating)
	{
		int horizontalSize = fmin(rect.w, animationPhase);
		int verticalSize = fmin(rect.h, animationPhase);
		if (horizontalSize == rect.w && verticalSize == rect.h)
			animating = false;
		else
		{
			bgRect.w = horizontalSize;
			bgRect.h = verticalSize;
			bgRect.x = (rect.x + (rect.w / 2)) - (horizontalSize / 2);
			bgRect.y = (rect.y + (rect.h / 2)) - (verticalSize / 2);
			animationPhase += 20;
		}
	}
	if (!animating)
		bgRect = rect;
	RenderBackground(renderer, bgRect);
	if (!animating)
		RenderOptions(renderer, rect);
}

void PopUpRenderElement::RenderBackground(SDL_Renderer* renderer, SDL_Rect& rect)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &rect);
}

void PopUpRenderElement::RenderOptions(SDL_Renderer* renderer, SDL_Rect& rect)
{
	int y = rect.y + POPUP_VERTICAL_MARGIN;
	for (int i = 0; i < options.size(); i++)
	{
		int x = rect.x + POPUP_HORIZONTAL_MARGIN + handSprite->Width + SPACE_BETWEEN_HAND_AND_TEXT;
		y += options[i]->Height / 2;
		options[i]->RenderAt(renderer, x, y);
		if (i == SelectedOption)
			handSprite->RenderAt(renderer, x - SPACE_BETWEEN_HAND_AND_TEXT, y);
		y += options[i]->Height / 2;
	}
}

void PopUpRenderElement::RecalculateSize()
{
	Width = 0;
	Height = 0;
	for (AnimatedText* option : this->options)
	{
		Height += option->Height;
		if (option->Width > Width)
			Width = option->Width;
	}
	Height += (POPUP_VERTICAL_MARGIN * 2);
	Width += (POPUP_HORIZONTAL_MARGIN * 2) + handSprite->Width + SPACE_BETWEEN_HAND_AND_TEXT;
}
