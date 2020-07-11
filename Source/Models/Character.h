#pragma once

#include <string>
#include <vector>

namespace sc
{
	/** Ids of the available characters. */
	enum CharacterId
	{
		LUKA,
		PLAYER,
		UNKNOW,
	};

	/** Model class for a character. */
	class Character
	{
	public:
		CharacterId Id;
		std::string Name;

		static std::vector<Character> GetCharacters();
	};
}

