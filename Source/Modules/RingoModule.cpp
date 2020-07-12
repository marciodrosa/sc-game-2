#include "RingoModule.h"
#include "MovieModule.h"
#include "Constants.h"
#include "RenderElements/StripesTransition.h"
#include "RenderElements/ShutterTransition.h"
#include "DialogueOptionSelectorModule.h"
#include "MusicPlayer.h"
#include <sstream>

using namespace sc;
using namespace std;

RingoModule::RingoModule()
{
}

RingoModule::~RingoModule()
{
}

void RingoModule::Start(GameState& state, ModuleResult& result)
{
	state.CurrentDialogue = DialogueTree::ExtraMovieDialogueTree();
	RefreshDialogueLine(state);
	ringo.LoadContentFromFile("Images/Ringo.png");
	ringo.CenterPivot();
	ringo.TopPivot();
	result.Transition = new ShutterTransition;
	MusicPlayer::Get()->PlayExtraMusic();
	state.RingoAlreadyAppeared = true;
}

void RingoModule::Update(GameState& state, ModuleResult& result)
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

void RingoModule::Render(GameState& state, SDL_Renderer* renderer)
{
	background.RenderAt(renderer, 0, 0);
	ringo.RenderAt(renderer, SC_SCREEN_WIDTH / 2, 10);
	if (!state.IsInModuleInTransition)
		text.RenderAt(renderer, SC_SCREEN_WIDTH / 2, ringo.Height + 20);
}

void RingoModule::Finish(GameState& state)
{
}

void RingoModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		if (text.IsAnimating())
			text.ForceFinishAnimation();
		else
		{
			if (state.CurrentDialogue.CurrentDialogueLineKey == "ringo.thisIsTheMovie")
			{
				result.NextGameModule = new MovieModule;
				result.Transition = new StripesTransition;
			}
			else
			{
				DialogueLine& currentDialogueLine = state.CurrentDialogue.Lines[state.CurrentDialogue.CurrentDialogueLineKey];
				if (currentDialogueLine.NextDialoguesKeys.size() == 1 && state.CurrentDialogue.Lines[currentDialogueLine.NextDialoguesKeys[0]].Character == CharacterId::RINGO)
				{
					state.CurrentDialogue.CurrentDialogueLineKey = currentDialogueLine.NextDialoguesKeys[0];
					RefreshDialogueLine(state);
				}
			}
		}
	}
}

void RingoModule::RefreshDialogueLine(GameState& state)
{
	DialogueLine* dialogueLine = &state.CurrentDialogue.Lines[state.CurrentDialogue.CurrentDialogueLineKey];
	if (dialogueLine->Character == CharacterId::PLAYER)
	{
		if (dialogueLine->NextDialoguesKeys.size() > 0)
		{
			string key = dialogueLine->NextDialoguesKeys[0];
			dialogueLine = &state.CurrentDialogue.Lines[key];
			if (dialogueLine->Character == CharacterId::RINGO)
				state.CurrentDialogue.CurrentDialogueLineKey = key;
		}
	}
	if (dialogueLine->Character == CharacterId::RINGO)
	{
		stringstream ss;
		ss << "RINGO:\n\"" << dialogueLine->Text << "\"";
		text.SetText(ss.str(), 10, 280);
		text.SetAnimated(true, 2);
		text.CenterPivot();
		text.TopPivot();
	}
}
