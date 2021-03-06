#pragma once

#include <string>
#include <vector>

namespace sc
{
	/** Ids of the available movies. */
	enum MovieId
	{
		WASP_NETWORK,
		O_BARCO,
		AS_BRUXAS_DE_EASTWICK,
		EDIFICIO_MASTER,
		O_INFORMANTE,
		HIGH_LIFE
	};

	/** Movie model data. */
	class Movie
	{
	public:
		Movie();
		MovieId Id;
		std::string Name;
		std::string OriginalName;
		std::string Year;
		std::string Country;
		std::string Director;
		std::string Stars;
		std::string Synopsis;
		std::string Platform;
		std::string Image;
		bool IsExtra;
		unsigned long long CosmoNetId;

		std::string GetFullDescription();

		static std::vector<Movie> GetMovies();
	};
}