#include "LukaModule.h"
#include "Constants.h"
#include "RenderElements/StripesTransition.h"
#include <sstream>

using namespace sc;
using namespace std;

LukaModule::LukaModule(string dialogue)
{
	this->dialogue = dialogue;

	// Miau. Seja bem vindo ao CINELUKA. O meu nome é Luka e eu sou uma gata. Qual é o seu nome, forasteiro?

	// GASP! Você é um humano, <nome>? Humanos não podem entrar no cinema, vocês estão em meio a uma pandemia!

	// (Talvez vocês não tenham notado, mas nós, gatos, aproveitamos sua ausência e tomamos o cinema para nós. Não pegamos COVID-19, então tá sussa.)

	// Uhmm, então você está preocupado com a SEGUNDA CINÉFILA? Ora, mas não seja por isso. Vamos fazer o seguinte, vou mostrar a você os filmes em cartaz
	// e você e seus amigos votam nos preferidos. Então vocês assistem o filme em casa.
}

LukaModule::~LukaModule()
{
}

void LukaModule::Start(GameState& state, ModuleResult& result)
{
	stringstream ss;
	ss << "Luka: \"" << dialogue << "\"";
	text.SetText(ss.str(), 10, 280);
	text.SetAnimated();
	luka.LoadContentFromFile("Images/Luka.png");
	luka.CenterPivot();
	luka.TopPivot();
	text.CenterPivot();
	text.TopPivot();
	result.Transition = new StripesTransition;
}

void LukaModule::Update(GameState& state, ModuleResult& result)
{
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
}
