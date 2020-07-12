#include "LukaModule.h"
#include "MovieModule.h"
#include "EndingModule.h"
#include "Constants.h"
#include "MusicPlayer.h"
#include "RenderElements/StripesTransition.h"
#include "RenderElements/BlindsTransition.h"
#include "RenderElements/ShutterTransition.h"
#include "DialogueOptionSelectorModule.h"
#include <sstream>

using namespace sc;
using namespace std;

LukaModule::LukaModule()
{
}

LukaModule::~LukaModule()
{
}

void LukaModule::Start(GameState& state, ModuleResult& result)
{
	RefreshDialogueLine(state);
	luka.LoadContentFromFile("Images/Luka.png");
	luka.CenterPivot();
	luka.TopPivot();
	result.Transition = new StripesTransition;
	MusicPlayer::Get()->PlayGameMusic();
}

void LukaModule::Update(GameState& state, ModuleResult& result)
{
	DialogueLine& currentDialogueLine = state.CurrentDialogue.Lines[state.CurrentDialogue.CurrentDialogueLineKey];
	if (currentDialogueLine.Character == CharacterId::PLAYER)
		RefreshDialogueLine(state);
	else if (!text.IsAnimating())
	{
		if (currentDialogueLine.NextDialoguesKeys.size() > 0)
		{
			bool isNextDialogueLineFromPlayer = state.CurrentDialogue.Lines[currentDialogueLine.NextDialoguesKeys[0]].Character == CharacterId::PLAYER;
			if (isNextDialogueLineFromPlayer)
			{
				state.DialogueOptions = currentDialogueLine.NextDialoguesKeys;
				state.CurrentDialogue.CurrentDialogueLineKey = currentDialogueLine.NextDialoguesKeys[0];
				result.SubModule = new DialogueOptionSelectorModule;
			}
		}
	}
}

void LukaModule::Render(GameState& state, SDL_Renderer* renderer)
{
	luka.RenderAt(renderer, SC_SCREEN_WIDTH / 2, 10);
	if (!state.IsInModuleInTransition)
		text.RenderAt(renderer, SC_SCREEN_WIDTH / 2, luka.Height + 20);
}

void LukaModule::Finish(GameState& state)
{
}

void LukaModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		if (text.IsAnimating())
			text.ForceFinishAnimation();
		else
		{
			if (state.CurrentDialogue.CurrentDialogueLineKey == "luka.theseAreTheMovies")
			{
				result.NextGameModule = new MovieModule(true);
				result.Transition = new BlindsTransition;
			}
			else if (state.CurrentDialogue.CurrentDialogueLineKey == "luka.bye" || state.CurrentDialogue.CurrentDialogueLineKey == "luka.byeWithoutVote")
			{
				result.NextGameModule = new EndingModule;
				result.Transition = new ShutterTransition;
			}
			else
			{
				DialogueLine& currentDialogueLine = state.CurrentDialogue.Lines[state.CurrentDialogue.CurrentDialogueLineKey];
				if (currentDialogueLine.NextDialoguesKeys.size() == 1 && state.CurrentDialogue.Lines[currentDialogueLine.NextDialoguesKeys[0]].Character == CharacterId::LUKA)
				{
					state.CurrentDialogue.CurrentDialogueLineKey = currentDialogueLine.NextDialoguesKeys[0];
					RefreshDialogueLine(state);
				}
			}
		}
	}
}

void LukaModule::RefreshDialogueLine(GameState& state)
{
	DialogueLine* dialogueLine = &state.CurrentDialogue.Lines[state.CurrentDialogue.CurrentDialogueLineKey];
	if (dialogueLine->Character == CharacterId::PLAYER)
	{
		if (dialogueLine->NextDialoguesKeys.size() > 0)
		{
			string key = dialogueLine->NextDialoguesKeys[0];
			dialogueLine = &state.CurrentDialogue.Lines[key];
			if (dialogueLine->Character == CharacterId::LUKA)
				state.CurrentDialogue.CurrentDialogueLineKey = key;
		}
	}
	if (dialogueLine->Character == CharacterId::LUKA)
	{
		stringstream ss;
		ss << "LUKA:\n\"" << dialogueLine->Text << "\"";
		text.SetText(ss.str(), 10, 280);
		text.SetAnimated(true, 2);
		text.CenterPivot();
		text.TopPivot();
	}
}
