#pragma once

#include "GameModule.h"
#include "RenderElements/PopUpRenderElement.h"
#include <vector>
#include <string>

namespace sc
{
	/** Option to be available in the PopUpModule. */
	class PopUpOption
	{
	public:
		PopUpOption(int id, std::string text);
		std::string Text;
		int Id;
	};

	/** Interface for listeners to the PopUpModule. */
	class PopUpListener
	{
	public:
		virtual void OnPopUpOptionSelected(int popUpId, PopUpOption& option, GameState& state, ModuleResult& result) = 0;
	};

	/** Module that a simple pop up with options in the center of the screen. */
	class PopUpModule : public GameModule
	{
	public:
		PopUpModule(int id, std::string title, std::vector<PopUpOption>& options, PopUpListener* listener = nullptr);
		virtual ~PopUpModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
		PopUpListener* Listener;
	private:
		PopUpRenderElement popUp;
		std::vector<PopUpOption> options;
		int id;
	};
}
