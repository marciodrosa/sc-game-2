#pragma once

#include <string>
#include <vector>

namespace sc
{
	/** Ids of the available characters. */
	enum CharacterId
	{
		FELIPE,
		JULIA,
		MARCIO,
		RAFA,
		GABI
	};

	/** Model class for a character. */
	class Character
	{
	public:
		CharacterId Id;
		std::string Name;
		std::string EndingLine;

		static std::vector<Character> GetCharacters();
	};
}

