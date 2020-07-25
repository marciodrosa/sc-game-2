#include "CosmoNetVoteData.h"
#include <sstream>

using namespace sc;
using namespace std;

string CosmoNetVoteData::ToURL()
{
	stringstream ss;
	ss << "https://cosmonet.uc.r.appspot.com/vote/" << AuthorizationToken << "/" << Name << "/";
	stringstream moviesIdsAsString;
	for (unsigned long long movieId : MoviesIds)
	{
		if (moviesIdsAsString.str().size() > 0)
			moviesIdsAsString << ",";
		moviesIdsAsString << movieId;
	}
	ss << moviesIdsAsString.str();
	return ss.str();
}