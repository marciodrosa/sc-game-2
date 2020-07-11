#pragma once

#include <string>
#include <vector>
#include <map>
#include "Character.h"

namespace sc
{
	class DialogueLine
	{
	public:
		DialogueLine();
		DialogueLine(CharacterId character, std::string text);
		DialogueLine(CharacterId character, std::string text, std::string next);
		CharacterId Character;
		std::string Text;
		std::vector<std::string> NextDialoguesKeys;
	};

	class DialogueTree
	{
	public:
		std::string FirstLineKey;
		std::map<std::string, DialogueLine> Lines;
		static DialogueTree InitialDialogueTree();
		static DialogueTree ExtraMovieDialogueTree();
		static DialogueTree VotingDialogueTree();
		static DialogueTree EndingDialogueTree();
	};
}
