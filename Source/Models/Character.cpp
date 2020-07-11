#include "Character.h"

using namespace std;
using namespace sc;

vector<Character> Character::GetCharacters()
{
	vector<Character> result;
	
	Character luka;
	luka.Id = CharacterId::LUKA;
	luka.Name = "Luka";
	result.push_back(luka);

	Character player;
	player.Id = CharacterId::PLAYER;
	player.Name = "";
	result.push_back(player);

	return result;
}
