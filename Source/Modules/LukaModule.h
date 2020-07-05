#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include "RenderElements/Sprite.h"
#include <string>

namespace sc
{
	/** Module with Luka talking. */
	class LukaModule: public GameModule
	{
	public:
		LukaModule(std::string dialogue);
		virtual ~LukaModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
	private:
		Sprite luka;
		AnimatedText text;
		std::string dialogue;
	};
}
