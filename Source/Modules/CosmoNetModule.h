#pragma once

#include "GameModule.h"
#include "RenderElements/Sprite.h"
#include "RenderElements/AnimatedText.h"

namespace sc
{
	/** Module that sends the selected movies over the internet to the CosmoNet. */
	class CosmoNetModule : public GameModule, public AnimationListener
	{
	public:
		CosmoNetModule();
		virtual ~CosmoNetModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
		void OnAnimationEnded(RenderElement* renderElement) override;
	private:
		Sprite logo;
		AnimatedText titleLabel;
		AnimatedText statusLabel;
	};
}
