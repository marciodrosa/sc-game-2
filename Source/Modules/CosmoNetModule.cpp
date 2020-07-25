#include "CosmoNetModule.h"
#include "LukaModule.h"
#include "RenderElements/ShutterTransition.h"
#include "RenderElements/BlindsTransition.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace sc;
using namespace std;

CosmoNetModule::CosmoNetModule()
{
	dataSent = false;
}

CosmoNetModule::~CosmoNetModule()
{

}

void CosmoNetModule::Start(GameState& state, ModuleResult& result)
{
	this->gameState = &state;
	logo.LoadContentFromFile("Images/CosmoNet.png");
	logo.CenterPivot();
	titleLabel.SetText("CosmoNet", 22);
	titleLabel.CenterPivot();
	titleLabel.TopPivot();
	statusLabel.SetText("Conectando à rede....", 11);
	statusLabel.CenterPivot();
	statusLabel.TopPivot();
	ShutterTransition* transition = new ShutterTransition;
	transition->EnableVerticalAnimation = false;
	transition->Listener = this;
	result.Transition = transition;
}

void CosmoNetModule::Update(GameState& state, ModuleResult& result)
{
	if (dataSent && !gameState->IsInModuleOutTransition)
	{
		state.CurrentDialogue = DialogueTree::EndingDialogueTree();
		result.NextGameModule = new LukaModule;
		result.Transition = new BlindsTransition;
	}
}

void CosmoNetModule::Render(GameState& state, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 122, 255, 255);
	SDL_RenderFillRect(renderer, nullptr);
	logo.RenderAt(renderer, SC_SCREEN_WIDTH / 2, (SC_SCREEN_HEIGHT / 2) - 20);
	titleLabel.RenderAt(renderer, SC_SCREEN_WIDTH / 2, (SC_SCREEN_HEIGHT / 2) + (logo.Height / 2));
	if (!state.IsInModuleInTransition && !state.IsInModuleOutTransition)
		statusLabel.RenderAt(renderer, SC_SCREEN_WIDTH / 2, 200);
}

void CosmoNetModule::Finish(GameState& state)
{

}

void CosmoNetModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
}

void CosmoNetModule::OnAnimationEnded(RenderElement* renderElement)
{
	SendVotesToCosmoNet();
}

void CosmoNetModule::SendVotesToCosmoNet()
{
	CosmoNetVoteData data = CreateCosmoNetVoteData();
	SendVotesDataToCosmoNet(data);
}

void CosmoNetModule::SendVotesDataToCosmoNet(CosmoNetVoteData& data)
{
	stringstream command;
	command << "curl -X POST " << data.ToURL();
	system(command.str().c_str());
	dataSent = true;
}

CosmoNetVoteData CosmoNetModule::CreateCosmoNetVoteData()
{
	CosmoNetVoteData Data;
	Data.Name = gameState->PlayerName;
	Data.AuthorizationToken = GetCosmoNetKey();
	Data.MoviesIds = GetListOfSelectedMoviesIds();
	return Data;
}

string CosmoNetModule::GetCosmoNetKey()
{
	string key;
	ifstream fileStream;
	fileStream.open("cosmonet.key");
	if (fileStream.is_open())
	{
		getline(fileStream, key);
		fileStream.close();
	}
	return key;
}

vector<unsigned long long> CosmoNetModule::GetListOfSelectedMoviesIds()
{
	vector<unsigned long long> result;
	for (MovieId selectedMovieId : gameState->SelectedMovies)
	{
		Movie* movie = gameState->FindMovieById(selectedMovieId);
		result.push_back(movie->CosmoNetId);
	}
	return result;
}
