#include "DialogueTree.h"

using namespace sc;
using namespace std;

DialogueLine::DialogueLine()
{
	Character = CharacterId::UNKNOW;
}

DialogueLine::DialogueLine(CharacterId character, std::string text)
{
	this->Character = character;
	this->Text = text;
}

DialogueLine::DialogueLine(CharacterId character, std::string text, std::string next)
{
	this->Character = character;
	this->Text = text;
	this->NextDialoguesKeys.push_back(next);
}

DialogueTree DialogueTree::InitialDialogueTree()
{
	DialogueTree Tree;
	Tree.FirstLineKey = "luka.welcome";
	Tree.CurrentDialogueLineKey = "luka.welcome";
	Tree.Lines["luka.welcome"] = DialogueLine(CharacterId::LUKA, "Miau. Seja bem vindo ao CINELUKA. O meu nome é Luka e eu sou uma gata. Qual é o seu nome, forasteiro?");
	Tree.Lines["luka.welcome"].NextDialoguesKeys.push_back("player.myNameIs");
	Tree.Lines["luka.welcome"].NextDialoguesKeys.push_back("player.willNotTellYou");
	Tree.Lines["player.myNameIs"] = DialogueLine(CharacterId::PLAYER, "Bem, o meu nome é...");
	Tree.Lines["player.willNotTellYou"] = DialogueLine(CharacterId::PLAYER, "Não te interessa o meu nome!", "luka.howHude");
	Tree.Lines["luka.howHude"] = DialogueLine(CharacterId::LUKA, "FFFSSST!! Que rude! Sinto muito, mas você não pode passar enquanto não me disser o seu nome.");
	Tree.Lines["luka.howHude"].NextDialoguesKeys.push_back("player.myNameIs");
	Tree.Lines["luka.howHude"].NextDialoguesKeys.push_back("player.willNotTellYou");
	return Tree;
}

DialogueTree DialogueTree::AfterNameDialogueTree()
{
	DialogueTree Tree;
	Tree.FirstLineKey = "luka.youAreAHuman";
	Tree.CurrentDialogueLineKey = "luka.youAreAHuman";
	Tree.Lines["luka.youAreAHuman"] = DialogueLine(CharacterId::LUKA, "GASP! Você é um humano?! Humanos não podem entrar no cinema. Vocês estão em meio a uma pandemia!", "luka.onlyCatsCanGetIn");
	Tree.Lines["luka.onlyCatsCanGetIn"] = DialogueLine(CharacterId::LUKA, "Nós, gatos, tomamos a administração dos cinemas enquanto vocês estão fora. Só gatos podem entrar, nós não pegamos Coronga.", "luka.humansAndDogsCantGetIn");
	Tree.Lines["luka.humansAndDogsCantGetIn"] = DialogueLine(CharacterId::LUKA, "Não permitimos nem humanos, nem cachorros. Exceto o Joey. O Joey é legal.");
	Tree.Lines["luka.humansAndDogsCantGetIn"].NextDialoguesKeys.push_back("player.whatNow");
	Tree.Lines["luka.humansAndDogsCantGetIn"].NextDialoguesKeys.push_back("player.IAmACat");
	Tree.Lines["player.IAmACat"] = DialogueLine(CharacterId::PLAYER, "Eu não sou um humano! Eu sou um gato! Miau, Miau.", "luka.youCantFoolMe");
	Tree.Lines["luka.youCantFoolMe"] = DialogueLine(CharacterId::LUKA, "Você não me engana, humano. Você tem nome de gente.");
	Tree.Lines["luka.youCantFoolMe"].NextDialoguesKeys.push_back("player.whatNow");
	Tree.Lines["luka.youCantFoolMe"].NextDialoguesKeys.push_back("player.IAmACat");
	Tree.Lines["player.whatNow"] = DialogueLine(CharacterId::PLAYER, "E agora? A Segunda Cinéfila está chegando...", "luka.IHaveAnIdea");
	Tree.Lines["luka.IHaveAnIdea"] = DialogueLine(CharacterId::LUKA, "Tenho uma ideia. Vou mostrar a você a programação da semana.", "luka.watchItFromHome");
	Tree.Lines["luka.watchItFromHome"] = DialogueLine(CharacterId::LUKA, "Então você e seus amigos podem votar no filme preferido e assistir no conforto do lar.", "luka.IWillBeThereToo");
	Tree.Lines["luka.IWillBeThereToo"] = DialogueLine(CharacterId::LUKA, "Eu mesmo estarei lá talvez, assistindo o filme da minha maneira preferida (dormindo).", "luka.themeOfTheWeek");
	Tree.Lines["luka.themeOfTheWeek"] = DialogueLine(CharacterId::LUKA, "O tema da semana é: FILMES COM GATOS... é o tema de todas as semanas aqui no CINELUKA, na verdade.", "luka.theseAreTheMovies");
	Tree.Lines["luka.theseAreTheMovies"] = DialogueLine(CharacterId::LUKA, "A seleção de filmes é a seguinte:");
	return Tree;
}

DialogueTree DialogueTree::ExtraMovieDialogueTree()
{
	DialogueTree Tree;
	Tree.FirstLineKey = "ringo.extraMovie";
	Tree.CurrentDialogueLineKey = "ringo.extraMovie";
	Tree.Lines["ringo.extraMovie"] = DialogueLine(CharacterId::RINGO, "Olá. Eu sou Ringo, o projecionista. Desci aqui para informá-lo que, além da programação normal, há um FILME EXTRA.", "ringo.notAvailableInLegalMeans");
	Tree.Lines["ringo.notAvailableInLegalMeans"] = DialogueLine(CharacterId::RINGO, "Esse filme, porém, não está disponível no país por meios legais.", "ringo.someoneNeedsToDownloadTheMovie");
	Tree.Lines["ringo.someoneNeedsToDownloadTheMovie"] = DialogueLine(CharacterId::RINGO, "Então alguém tem que se disponibilizar para baixar da DEEP WEB ou coisa parecida.", "ringo.shouldNotBeAProblem");
	Tree.Lines["ringo.shouldNotBeAProblem"] = DialogueLine(CharacterId::RINGO, "O que não deve ser um problema para vocês, humanos, que fazem coisas bem mais moralmente duvidosas. Como passar cheque sem fundo etc.", "ringo.thisIsTheMovie");
	Tree.Lines["ringo.thisIsTheMovie"] = DialogueLine(CharacterId::RINGO, "O filme é o seguinte:");
	return Tree;
}

DialogueTree DialogueTree::VotingDialogueTree()
{
	DialogueTree Tree;
	Tree.FirstLineKey = "luka.seeOnlyMoviesWithCats";
	Tree.CurrentDialogueLineKey = "luka.seeOnlyMoviesWithCats";
	Tree.Lines["luka.seeOnlyMoviesWithCats"] = DialogueLine(CharacterId::LUKA, "Viu? Apenas filmes com gatos. Robert Pattinson, Ana de Armas etc.", "luka.doYouWantToVote");
	Tree.Lines["luka.doYouWantToVote"] = DialogueLine(CharacterId::LUKA, "Agora que eu apresentei a você os filmes selecionados, gostaria de computar os votos dos seus favoritos e enviar pelo sistema COSMONET?");
	Tree.Lines["luka.doYouWantToVote"].NextDialoguesKeys.push_back("player.yesIWantToVoteNow");
	Tree.Lines["luka.doYouWantToVote"].NextDialoguesKeys.push_back("player.reviewMovies");
	Tree.Lines["luka.doYouWantToVote"].NextDialoguesKeys.push_back("player.noIDontWantToVote");
	Tree.Lines["player.yesIWantToVoteNow"] = DialogueLine(CharacterId::PLAYER, "Sim, gostaria de votar agora.");
	Tree.Lines["player.reviewMovies"] = DialogueLine(CharacterId::PLAYER, "Primeiro eu gostaria de rever a apresentação dos filmes.");
	Tree.Lines["player.noIDontWantToVote"] = DialogueLine(CharacterId::PLAYER, "Não, vou votar outra hora.", "luka.byeWithoutVote");
	Tree.Lines["luka.byeWithoutVote"] = DialogueLine(CharacterId::LUKA, "Ok, você pode jogar o game mais tarde e votar. Por hora, muito obrigada por nos visitar, mas agora vaza. Bons filmes (em casa)!");
	return Tree;
}

DialogueTree DialogueTree::EndingDialogueTree()
{
	DialogueTree Tree;
	Tree.FirstLineKey = "luka.bye";
	Tree.CurrentDialogueLineKey = "luka.bye";
	Tree.Lines["luka.bye"] = DialogueLine(CharacterId::LUKA, "Muito obrigada por nos visitar, mas agora vaza. Bons filmes (em casa)!");
	return Tree;
}
