#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include <string>
#include <vector>

namespace sc
{
	/** Module used to type a name. */
	class EnterNameModule : public GameModule
	{
	public:
		EnterNameModule();
		virtual ~EnterNameModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
	private:
		AnimatedText label;
		AnimatedText nameLabel;
		std::string* currentName;
		void RefreshNameLabel();
	};
}
