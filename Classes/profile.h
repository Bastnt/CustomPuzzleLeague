#ifndef __PROFILE_H_CPL__
#define __PROFILE_H_CPL__

#include <string>
#include <unordered_map>
#include <chrono>

class Profile
{
public:
	//The identifier and pseudonym of the profile
	std::string pseudo;
	//The last time the profile has been used to play with or created if never
	std::chrono::steady_clock::time_point last_used;
	//The last time the profile has been used to play with or created if never
	std::chrono::steady_clock::time_point last_used;
};

#endif