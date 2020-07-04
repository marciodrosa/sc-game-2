#pragma once

#include <string>
#include <vector>

namespace sc
{
	/** Ids of the available movies. */
	enum MovieId
	{
		DESTACAMENTO_BLOOD,
		UM_PEQUENO_FAVOR,
		PERSONAL_SHOPPER,
		NASCIDO_EM_4_DE_JULHO,
		PSICOPATA_AMERICANO,
		EMBRIAGADO_DE_AMOR
	};

	/** Movie model data. */
	class Movie
	{
	public:
		Movie();
		MovieId Id;
		std::string Name;
		std::string Year;
		std::string Director;
		std::string Stars;
		std::string Synopsis;
		std::string Platform;
		bool IsExtra;

		std::string GetFullDescription();

		static std::vector<Movie> GetMovies();
	};
}