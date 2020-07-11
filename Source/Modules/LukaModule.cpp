#include "LukaModule.h"
#include "Constants.h"
#include "RenderElements/StripesTransition.h"
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
}

void LukaModule::Update(GameState& state, ModuleResult& result)
{
	DialogueLine& currentDialogueLine = state.CurrentDialogue.Lines[state.CurrentDialogueLineKey];
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
				state.CurrentDialogueLineKey = currentDialogueLine.NextDialoguesKeys[0];
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
			if (state.CurrentDialogueLineKey == "luka.theseAreTheMovies")
				; // go to the movies module
			else if (state.CurrentDialogueLineKey == "luka.shouldNotBeAProblem")
				; // go to the extra movies
			else if (state.CurrentDialogueLineKey == "luka.bye")
				; // go to end
			else
			{
				DialogueLine& currentDialogueLine = state.CurrentDialogue.Lines[state.CurrentDialogueLineKey];
				if (currentDialogueLine.NextDialoguesKeys.size() == 1 && state.CurrentDialogue.Lines[currentDialogueLine.NextDialoguesKeys[0]].Character == CharacterId::LUKA)
				{
					state.CurrentDialogueLineKey = currentDialogueLine.NextDialoguesKeys[0];
					RefreshDialogueLine(state);
				}
			}
		}
	}
}

void LukaModule::RefreshDialogueLine(GameState& state)
{
	if (state.CurrentDialogueLineKey == "")
		state.CurrentDialogueLineKey = state.CurrentDialogue.FirstLineKey;
	DialogueLine* dialogueLine = &state.CurrentDialogue.Lines[state.CurrentDialogueLineKey];
	if (dialogueLine->Character == CharacterId::PLAYER)
	{
		if (dialogueLine->NextDialoguesKeys.size() > 0)
		{
			string key = dialogueLine->NextDialoguesKeys[0];
			dialogueLine = &state.CurrentDialogue.Lines[key];
			if (dialogueLine->Character == CharacterId::LUKA)
				state.CurrentDialogueLineKey = key;
		}
	}
	if (dialogueLine->Character == CharacterId::LUKA)
	{
		stringstream ss;
		ss << "LUKA:\n\"" << dialogueLine->Text << "\"";
		text.SetText(ss.str(), 10, 280);
		text.SetAnimated();
		text.CenterPivot();
		text.TopPivot();
	}
}
