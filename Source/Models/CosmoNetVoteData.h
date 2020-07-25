#pragma once

#include <string>
#include <vector>

namespace sc
{
	class CosmoNetVoteData
	{
	public:
		std::string ToURL();
		std::string Name;
		std::string AuthorizationToken;
		std::vector<unsigned long long> MoviesIds;
	};
}
