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
}

AnimatedText::~AnimatedText()
{
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(animTextSurface);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
}

void AnimatedText::SetText(std::string text, int fontSize, int width, bool animated, int animationSpeed, AnimationListener* animationListener)
{
	if (text != targetText)
	{
		SDL_FreeSurface(textSurface);
		SDL_FreeSurface(animTextSurface);
		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(font);
		this->targetText = text;
		this->animationSpeed = animationSpeed;
		this->animated = animated;
		this->animationListener = animationListener;
		this->font = TTF_OpenFont("Fonts/CrimsonText-Bold.ttf", fontSize);
		this->width = width;
		if (animated)
			currentText = "";
		else
			currentText = targetText;
		textSurface = width > 0 ? TTF_RenderText_Blended_Wrapped(font, targetText.c_str(), color, width) : TTF_RenderText_Blended(font, targetText.c_str(), color);
		animTextSurface = nullptr;
		textTexture = nullptr;
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

int AnimatedText::GetWidth()
{
	return textSurface != nullptr ? textSurface->w : 0;
}

int AnimatedText::GetHeight()
{
	return textSurface != nullptr ? textSurface->h : 0;
}

void AnimatedText::Render(SDL_Renderer* render, int x, int y)
{
	if (targetText != "")
	{
		if (animated)
		{
			bool wasAnimating = IsAnimating();
			AnimateText();
			SDL_FreeSurface(animTextSurface);
			SDL_DestroyTexture(textTexture);
			animTextSurface = width > 0 ? TTF_RenderText_Blended_Wrapped(font, currentText.c_str(), color, width) : TTF_RenderText_Blended(font, currentText.c_str(), color);
			textTexture = SDL_CreateTextureFromSurface(render, animTextSurface);
			SDL_Rect destRect;
			destRect.x = x;
			destRect.y = y;
			destRect.w = animTextSurface->w;
			destRect.h = animTextSurface->h;
			SDL_RenderCopy(render, textTexture, nullptr, &destRect);
			if (wasAnimating && !IsAnimating() && animationListener != nullptr)
				animationListener->OnAnimationEnded();
		}
		else
		{
			if (textTexture == nullptr)
				textTexture = SDL_CreateTextureFromSurface(render, textSurface);
			SDL_Rect destRect;
			destRect.x = x;
			destRect.y = y;
			destRect.w = textSurface->w;
			destRect.h = textSurface->h;
			SDL_RenderCopy(render, textTexture, nullptr, &destRect);
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
