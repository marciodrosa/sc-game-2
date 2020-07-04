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
	ss << Name << " (" << Year << ")" << endl;
	ss << "Dir. " << Director << ", com " << Stars << endl << endl << Synopsis;
	if (Platform.size() > 0)
		ss << endl << "(Disponível em: " << Platform << ")";
	return ss.str();
}

vector<Movie> Movie::GetMovies()
{
	vector<Movie> result;

	Movie destacamentoBlood;
	destacamentoBlood.Id = MovieId::DESTACAMENTO_BLOOD;
	destacamentoBlood.Name = "DESTACAMENTO BLOOD";
	destacamentoBlood.Year = "2020";
	destacamentoBlood.Director = "Spike Lee";
	destacamentoBlood.Stars = "Chadwick Boseman";
	destacamentoBlood.Synopsis = "Um grupo de veteranos da Guerra do Vietnã retornam ao país em busca dos restos mortais do seu comandante e de um tesouro que enterraram enquanto serviam lá.";
	destacamentoBlood.Platform = "Netflix";
	result.push_back(destacamentoBlood);

	Movie umPequenoFavor;
	umPequenoFavor.Id = MovieId::UM_PEQUENO_FAVOR;
	umPequenoFavor.Name = "UM PEQUENO FAVOR";
	umPequenoFavor.Year = "2018";
	umPequenoFavor.Director = "Paul Feig";
	umPequenoFavor.Stars = "Blake Lively";
	umPequenoFavor.Synopsis = "Stephanie é uma mãe solitária que se torna amiga de Emily, uma mulher poderosa e destemida. Um dia, Emily desaparece e Stephanie parte em busca de respostas por conta própria.";
	umPequenoFavor.Platform = "Prime";
	result.push_back(umPequenoFavor);

	Movie personalShopper;
	personalShopper.Id = MovieId::PERSONAL_SHOPPER;
	personalShopper.Name = "PERSONAL SHOPPER";
	personalShopper.Year = "2016";
	personalShopper.Director = "Olivier Assayas";
	personalShopper.Stars = "Kristen Stewart";
	personalShopper.Synopsis = "Maureen sofre após a morte do irmão gêmeo. Para aliviar sua dor, ela usa as habilidades como médium e tenta conectar-se com o seu espírito.";
	personalShopper.Platform = "Netflix";
	result.push_back(personalShopper);

	Movie nascidoEm4deJulho;
	nascidoEm4deJulho.Id = MovieId::NASCIDO_EM_4_DE_JULHO;
	nascidoEm4deJulho.Name = "NASCIDO EM 4 DE JULHO";
	nascidoEm4deJulho.Year = "1989";
	nascidoEm4deJulho.Director = "Oliver Stone";
	nascidoEm4deJulho.Stars = "Tom Cruise";
	nascidoEm4deJulho.Synopsis = "Ron Kovic fica paralisado na guerra do Vietnã, passa por um pesadelo em um hospital de veteranos e se torna um ativista político.";
	nascidoEm4deJulho.Platform = "Netflix";
	result.push_back(nascidoEm4deJulho);

	Movie psicopataAmericano;
	psicopataAmericano.Id = MovieId::PSICOPATA_AMERICANO;
	psicopataAmericano.Name = "PSICOPATA AMERICANO";
	psicopataAmericano.Year = "2000";
	psicopataAmericano.Director = "Mary Harron";
	psicopataAmericano.Stars = "Christian Bale";
	psicopataAmericano.Synopsis = "Em Nova York, em 1987, o belo jovem profissional Patrick Bateman tem uma segunda vida como um horrível assassino em série durante a noite.";
	psicopataAmericano.Platform = "Prime";
	result.push_back(psicopataAmericano);

	Movie embriagadoDeAmor;
	embriagadoDeAmor.Id = MovieId::EMBRIAGADO_DE_AMOR;
	embriagadoDeAmor.Name = "EMBRIAGADO DE AMOR";
	embriagadoDeAmor.Year = "2003";
	embriagadoDeAmor.Director = "Paul Thomas Anderson";
	embriagadoDeAmor.Stars = "Adam Sandler";
	embriagadoDeAmor.Synopsis = "O romance de Barry Egan e uma colega de trabalho da sua irmã é ameaçado quando Egan é vítima de um chantagista.";
	embriagadoDeAmor.IsExtra = true;
	result.push_back(embriagadoDeAmor);

	return result;
}
