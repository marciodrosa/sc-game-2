#include "AnimatedText.h"

using namespace sc;

AnimatedText::AnimatedText()
{
	this->textSurface = nullptr;
	this->animTextSurface = nullptr;
	this->textTexture = nullptr;
	this->font = nullptr;
	this->color.r = 255;
	this->color.g = 255;
	this->color.b = 255;
	this->color.a = 255;
	Listener = nullptr;
}

AnimatedText::~AnimatedText()
{
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(animTextSurface);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
}

void AnimatedText::SetText(std::string text, int fontSize, int width, int r, int g, int b)
{
	TTF_CloseFont(font);
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->targetText = text;
	this->font = TTF_OpenFont("Fonts/CrimsonText-Bold.ttf", fontSize);
	this->maxWidth = width;
	if (animated)
		currentText = "";
	else
		currentText = targetText;
	textSurface = width > 0 ? TTF_RenderText_Blended_Wrapped(font, targetText.c_str(), color, width) : TTF_RenderText_Blended(font, targetText.c_str(), color);
	Width = textSurface->w;
	Height = textSurface->h;
	animTextSurface = nullptr;
	textTexture = nullptr;
	RefreshText();
}

void AnimatedText::SetAnimated(bool animated, int animationSpeed)
{
	this->animationSpeed = animationSpeed;
	if (this->animated != animated)
	{
		this->animated = animated;
		if (animated)
			currentText = "";
		else
			currentText = targetText;
		RefreshText();
	}
}

void AnimatedText::ForceFinishAnimation()
{
	currentText = targetText;
}

bool AnimatedText::IsAnimating()
{
	return targetText != currentText;
}

void AnimatedText::Render(SDL_Renderer* renderer, SDL_Rect& rect)
{
	if (targetText != "")
	{
		if (animated)
		{
			bool wasAnimating = IsAnimating();
			AnimateText();
			SDL_FreeSurface(animTextSurface);
			SDL_DestroyTexture(textTexture);
			animTextSurface = maxWidth > 0 ? TTF_RenderText_Blended_Wrapped(font, currentText.c_str(), color, maxWidth) : TTF_RenderText_Blended(font, currentText.c_str(), color);
			textTexture = SDL_CreateTextureFromSurface(renderer, animTextSurface);
			SDL_Rect destRect;
			destRect.x = rect.x;
			destRect.y = rect.y;
			destRect.w = animTextSurface->w;
			destRect.h = animTextSurface->h;
			SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);
			if (wasAnimating && !IsAnimating() && Listener != nullptr)
				Listener->OnAnimationEnded(nullptr);
		}
		else
		{
			if (textTexture == nullptr)
				textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			SDL_RenderCopy(renderer, textTexture, nullptr, &rect);
		}
	}
}

void AnimatedText::AnimateText()
{
	int newSize = currentText.size() + animationSpeed;
	if (newSize > targetText.size())
		currentText = targetText;
	else
		currentText = targetText.substr(0, newSize);
}

void AnimatedText::RefreshText()
{
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(animTextSurface);
	SDL_DestroyTexture(textTexture);
	textSurface = maxWidth > 0 ? TTF_RenderText_Blended_Wrapped(font, targetText.c_str(), color, maxWidth) : TTF_RenderText_Blended(font, targetText.c_str(), color);
	Width = textSurface->w;
	Height = textSurface->h;
	animTextSurface = nullptr;
	textTexture = nullptr;
}
