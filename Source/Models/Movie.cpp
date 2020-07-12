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
	result.push_back(waspNetwork);

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
	result.push_back(oBarco);

	Movie amantesEternos;
	amantesEternos.Id = MovieId::AMANTES_ETERNOS;
	amantesEternos.Name = "Amantes Eternos";
	amantesEternos.OriginalName = "Only Lovers Left Alive";
	amantesEternos.Year = "2013";
	amantesEternos.Country = "Reino Unido";
	amantesEternos.Director = "Jim Jarmusch";
	amantesEternos.Stars = "Tilda Swinton, Tom Hiddleston";
	amantesEternos.Synopsis = "Conhe�a a hist�ria de amor e de reencontro entre o vampiros Adam, um m�sico que est� deprimido e cansado com o rumo que a sociedade tomou, e Eve.";
	amantesEternos.Platform = "Prime";
	amantesEternos.Image = "Images/AmantesEternos.png";
	result.push_back(amantesEternos);

	Movie edificioMaster;
	edificioMaster.Id = MovieId::EDIFICIO_MASTER;
	edificioMaster.Name = "Edif�cio Master";
	edificioMaster.Year = "2002";
	edificioMaster.Country = "Brasil";
	edificioMaster.Director = "Eduardo Coutinho";
	edificioMaster.Synopsis = "O filme registra o cotidiano dos moradores do Edif�cio Master, em Copacabana, e apresenta um rico painel de hist�rias.";
	edificioMaster.Platform = "Looke";
	edificioMaster.Image = "Images/EdificioMaster.png";
	result.push_back(edificioMaster);

	Movie laBamba;
	laBamba.Id = MovieId::LA_BAMBA;
	laBamba.Name = "La Bamba";
	laBamba.Year = "1987";
	laBamba.Country = "USA";
	laBamba.Director = "Luis Valdez";
	laBamba.Stars = "Lou Diamond Phillips, Esai Morales";
	laBamba.Synopsis = "Em 1958, o adolescente de Los Angeles Ritchie Valens torna-se um astro do rock da noite para o dia.";
	laBamba.Platform = "Netflix";
	laBamba.Image = "Images/LaBamba.png";
	result.push_back(laBamba);

	Movie highLife;
	highLife.Id = MovieId::HIGH_LIFE;
	highLife.Name = "High Life";
	highLife.Year = "2018";
	highLife.Country = "Fran�a, Reino Unido";
	highLife.Director = "Claire Denis";
	highLife.Stars = "Robert Pattinson, Juliette Binoche";
	highLife.Synopsis = "Um pai e sua filha tentam sobreviver isolados no espa�o sideral.";
	highLife.Image = "Images/HighLife.png";
	highLife.IsExtra = true;
	result.push_back(highLife);

	return result;
}
