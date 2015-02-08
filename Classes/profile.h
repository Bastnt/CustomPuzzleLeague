#ifndef __PROFILE_H_CPL__
#define __PROFILE_H_CPL__

#include <string>
#include <chrono>

class ProfileManager;

class Profile
{
public:
	//The identifier and pseudonym of the profile
	std::string pseudo;

	//The last time the profile was used or created
	std::chrono::steady_clock::time_point last_use;

	//Basic constructor
	Profile(std::string name = "");

	friend class ProfileManager;
};

#endif