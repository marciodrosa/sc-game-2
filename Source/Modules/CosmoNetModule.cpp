#include "CosmoNetModule.h"
#include "LukaModule.h"
#include "RenderElements/ShutterTransition.h"
#include "RenderElements/BlindsTransition.h"
#include "Constants.h"
#include "ResourcesManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#define CURL_STATICLIB
#include <curl\curl.h>

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
	statusLabel.SetText("Enviando votos ao sistema....", 11);
	statusLabel.CenterPivot();
	statusLabel.TopPivot();
	ShutterTransition* transition = new ShutterTransition;
	transition->EnableVerticalAnimation = false;
	transition->Listener = this;
	result.Transition = transition;
}

void CosmoNetModule::Update(GameState& state, ModuleResult& result)
{
}

void CosmoNetModule::Render(GameState& state, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 122, 255, 255);
	SDL_RenderFillRect(renderer, nullptr);
	logo.RenderAt(renderer, SC_SCREEN_WIDTH / 2, (SC_SCREEN_HEIGHT / 2) - 20);
	titleLabel.RenderAt(renderer, SC_SCREEN_WIDTH / 2, (SC_SCREEN_HEIGHT / 2) + (logo.Height / 2));
	statusLabel.RenderAt(renderer, SC_SCREEN_WIDTH / 2, 200);
	if (dataSent && !state.IsInModuleInTransition && !state.IsInModuleOutTransition)
		pressEnterIndicator.RenderAt(renderer, 0, 0);
}

void CosmoNetModule::Finish(GameState& state)
{

}

void CosmoNetModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		if (dataSent)
		{
			Mix_PlayChannel(1, ResourcesManager::Get()->EnterSound, 0);
			state.CurrentDialogue = DialogueTree::EndingDialogueTree();
			result.NextGameModule = new LukaModule;
			result.Transition = new BlindsTransition;
		}
	}
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
#include <fstream>
void CosmoNetModule::SendVotesDataToCosmoNet(CosmoNetVoteData& data)
{
	CURLcode res = CURLE_FAILED_INIT;
	CURL* curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, data.ToURL().c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	dataSent = true;
	if (res == CURLE_OK)
		statusLabel.SetText("Votos enviados!", 11);
	else
		statusLabel.SetText("Ocorreu algum problema, tente mais tarde.", 11);
	statusLabel.CenterPivot();
	statusLabel.TopPivot();
	Mix_PlayChannel(1, ResourcesManager::Get()->CosmoNetOkSound, 0);
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
