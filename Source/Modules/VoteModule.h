#pragma once

#include "GameModule.h"
#include "RenderElements/AnimatedText.h"
#include "RenderElements/Sprite.h"
#include "PopUpModule.h"
#include <vector>
#include <map>

namespace sc
{
	/** Enum with IDs of all UI elements of the VoteModule. */
	enum VoteActionIds
	{
		AVAILABLE_MOVIE_1,
		AVAILABLE_MOVIE_2,
		AVAILABLE_MOVIE_3,
		AVAILABLE_MOVIE_4,
		AVAILABLE_MOVIE_5,
		AVAILABLE_MOVIE_6,
		AVAILABLE_MOVIE_7,
		AVAILABLE_MOVIE_8,
		AVAILABLE_MOVIE_9,
		AVAILABLE_MOVIE_10,
		PICKED_MOVIE_1,
		PICKED_MOVIE_2,
		PICKED_MOVIE_3,
		PICKED_MOVIE_4,
		PICKED_MOVIE_5,
		PICKED_MOVIE_6,
		PICKED_MOVIE_7,
		PICKED_MOVIE_8,
		PICKED_MOVIE_9,
		PICKED_MOVIE_10,
		OPTIONS,
		RESTART_LIST,
		REVIEW_PRESENTATION,
		ABORT_VOTE,
		YES,
		NO,
		SEND,
		PICKED_MOVIE_OPTIONS,
		REMOVE_PICKED_MOVIE,
		SORT_PICKED_MOVIE_UP,
		SORT_PICKED_MOVIE_DOWN,
		CANCEL,
	};

	/** Module that allows the player to select and create the list of favorite movies. */
	class VoteModule : public GameModule, public PopUpListener
	{
	public:
		VoteModule();
		virtual ~VoteModule();
		void Start(GameState& state, ModuleResult& result) override;
		void Update(GameState& state, ModuleResult& result) override;
		void Render(GameState& state, SDL_Renderer* renderer) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
		void OnPopUpOptionSelected(int popUpId, PopUpOption& option, GameState& state, ModuleResult& result) override;
	private:
		void RefreshAll(GameState& state);
		void RefreshModel(GameState& state);
		void RefreshOptionsTexts(GameState& state);
		void ResetCursor();
		void RefreshCursor();
		void DeleteOptionsTexts();
		std::string GetLabelForLeftColumnTitle(GameState& state);
		std::string GetLabelForRightColumnTitle(GameState& state);
		Movie* GetFocusedMovie(GameState& state);
		int GetFocusedMovieIndex(GameState& state);
		std::vector<VoteActionIds> optionsAtLeft;
		std::vector<VoteActionIds> optionsAtRight;
		int cursorIndex;
		bool cursorAtRight;
		AnimatedText leftColumnTitle;
		AnimatedText rightColumnTitle;
		Sprite* cursor;
		std::map<VoteActionIds, AnimatedText*> optionsTexts;
	};
}
