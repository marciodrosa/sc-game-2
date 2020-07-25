#include "Movie.h"
#include <sstream>

using namespace sc;
using namespace std;

Movie::Movie()
{
	IsExtra = false;
}

string Movie::GetFullDescription()
{
	stringstream ss;
	ss << Name << " (";
	if (OriginalName.size() > 0)
		ss << OriginalName << " - ";
	ss << Country << " - " << Year << ")" << endl;
	ss << "Dir. " << Director;
	if (Stars.size() > 0)
		ss << ", com " << Stars;
	ss << endl << endl << Synopsis;
	if (Platform.size() > 0)
		ss << endl << "(Dispon�vel em: " << Platform << ")";
	return ss.str();
}

vector<Movie> Movie::GetMovies()
{
	vector<Movie> result;

	Movie waspNetwork;
	waspNetwork.Id = MovieId::WASP_NETWORK;
	waspNetwork.Name = "WASP Network";
	waspNetwork.Year = "2019";
	waspNetwork.Country = "Fran�a, Brasil, Espanha, B�lgica";
	waspNetwork.Director = "Olivier Assayas";
	waspNetwork.Stars = "Penelope Cruz, Ana de Armas, Wagner Moura";
	waspNetwork.Synopsis = "Piloto cubano deixa a fam�lia em Cuba, desertando para os EUA. Mas ele n�o � o ambicioso empreendedor que aparenta ser.";
	waspNetwork.Platform = "Netflix";
	waspNetwork.Image = "Images/WaspNetwork.png";
	waspNetwork.CosmoNetId = 5642368648740864;
	result.push_back(waspNetwork);

	Movie highLife;
	highLife.Id = MovieId::HIGH_LIFE;
	highLife.Name = "High Life";
	highLife.Year = "2018";
	highLife.Country = "Fran�a, Reino Unido";
	highLife.Director = "Claire Denis";
	highLife.Stars = "Robert Pattinson, Juliette Binoche";
	highLife.Synopsis = "Um pai e sua filha tentam sobreviver isolados no espa�o sideral.";
	highLife.Platform = "Google Play";
	highLife.Image = "Images/HighLife.png";
	highLife.CosmoNetId = 5638358357245952;
	result.push_back(highLife);

	Movie oBarco;
	oBarco.Id = MovieId::O_BARCO;
	oBarco.Name = "O Barco";
	oBarco.OriginalName = "Das Boot";
	oBarco.Year = "1981";
	oBarco.Country = "Alemanha";
	oBarco.Director = "Wolfgang Petersen";
	oBarco.Stars = "Jurgen Prochnow, Herbert Gronemeyer";
	oBarco.Synopsis = "A perigosa viagem de ida e volta de uma embarca��o alem� entre La Rochelle, na Fran�a ocupada, e a Espanha em 1941.";
	oBarco.Platform = "Netflix";
	oBarco.Image = "Images/OBarco.png";
	oBarco.CosmoNetId = 5636645067948032;
	result.push_back(oBarco);

	Movie asBruxasDeEastwick;
	asBruxasDeEastwick.Id = MovieId::AS_BRUXAS_DE_EASTWICK;
	asBruxasDeEastwick.Name = "As Bruxas de Eastwick";
	asBruxasDeEastwick.OriginalName = "The Witches of Eastwick";
	asBruxasDeEastwick.Year = "1987";
	asBruxasDeEastwick.Country = "USA";
	asBruxasDeEastwick.Director = "George Miller";
	asBruxasDeEastwick.Stars = "Jack Nicholson, Cher";
	asBruxasDeEastwick.Synopsis = "Tr�s mulheres entediadas est�o sempre imaginando o homem ideal, at� que conhecem o misterioso rica�o Daryl Van Horne.";
	asBruxasDeEastwick.Platform = "Google Play";
	asBruxasDeEastwick.Image = "Images/AsBruxasDeEastwick.png";
	asBruxasDeEastwick.CosmoNetId = 5646488461901824;
	result.push_back(asBruxasDeEastwick);

	Movie edificioMaster;
	edificioMaster.Id = MovieId::EDIFICIO_MASTER;
	edificioMaster.Name = "Edif�cio Master";
	edificioMaster.Year = "2002";
	edificioMaster.Country = "Brasil";
	edificioMaster.Director = "Eduardo Coutinho";
	edificioMaster.Synopsis = "O filme registra o cotidiano dos moradores do Edif�cio Master, em Copacabana, e apresenta um rico painel de hist�rias.";
	edificioMaster.Platform = "Looke";
	edificioMaster.Image = "Images/EdificioMaster.png";
	edificioMaster.CosmoNetId = 5702893864747008;
	result.push_back(edificioMaster);

	Movie oInformante;
	oInformante.Id = MovieId::O_INFORMANTE;
	oInformante.Name = "O Informante";
	oInformante.OriginalName = "The Insider";
	oInformante.Year = "1999";
	oInformante.Country = "USA";
	oInformante.Director = "Michael Mann";
	oInformante.Stars = "Al Pacino, Russell Crowe";
	oInformante.Synopsis = "O produtor de TV Lowell Bergman desconfia do ex-executivo da ind�stria do tabaco Jeffrey Wigand ap�s uma entrevista.";
	oInformante.Image = "Images/OInformante.png";
	oInformante.CosmoNetId = 5631671361601536;
	oInformante.IsExtra = true;
	result.push_back(oInformante);

	return result;
}
