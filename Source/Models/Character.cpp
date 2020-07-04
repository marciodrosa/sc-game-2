#include "Character.h"

using namespace std;
using namespace sc;

vector<Character> Character::GetCharacters()
{
	vector<Character> result;
	
	Character felipe;
	felipe.Id = CharacterId::FELIPE;
	felipe.Name = "Felipe";
	felipe.EndingLine = "Nenhum filme de espadinha, aprovei!";
	result.push_back(felipe);

	Character julia;
	julia.Id = CharacterId::JULIA;
	julia.Name = "Júlia";
	julia.EndingLine = "Senti falta de algum filme com o Redmayne, mas bacana fora isso.";
	result.push_back(julia);

	Character marcio;
	marcio.Id = CharacterId::MARCIO;
	marcio.Name = "Márcio";
	marcio.EndingLine = "Vencedores não perdem!";
	result.push_back(marcio);

	Character rafa;
	rafa.Id = CharacterId::RAFA;
	rafa.Name = "Rafa";
	rafa.EndingLine = "Agora bora jogar de novo para listar os filmes no Letterboxd.";
	result.push_back(rafa);

	Character gabi;
	gabi.Id = CharacterId::GABI;
	gabi.Name = "Gabi";
	gabi.EndingLine = "Só filmes bons? Não é a Segunda Cinéfila que eu conheço...";
	result.push_back(gabi);

	return result;
}
