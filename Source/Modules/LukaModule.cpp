#include "LukaModule.h"
#include "Constants.h"
#include "RenderElements/StripesTransition.h"
#include <sstream>

using namespace sc;
using namespace std;

LukaModule::LukaModule(string dialogue)
{
	this->dialogue = dialogue;

	// Miau. Seja bem vindo ao CINELUKA. O meu nome � Luka e eu sou uma gata. Qual � o seu nome, forasteiro?

	// GASP! Voc� � um humano, <nome>? Humanos n�o podem entrar no cinema, voc�s est�o em meio a uma pandemia!

	// (Talvez voc�s n�o tenham notado, mas n�s, gatos, aproveitamos sua aus�ncia e tomamos o cinema para n�s. N�o pegamos COVID-19, ent�o t� sussa.)

	// Uhmm, ent�o voc� est� preocupado com a SEGUNDA CIN�FILA? Ora, mas n�o seja por isso. Vamos fazer o seguinte, vou mostrar a voc� os filmes em cartaz
	// e voc� e seus amigos votam nos preferidos. Ent�o voc�s assistem o filme em casa.
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
