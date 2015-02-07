#ifndef __PROFILE_MANAGER_H_CPL__
#define __PROFILE_MANAGER_H_CPL__

#include <memory>

//Parses the themes and contains data about 'em
class ProfileManager
{
	ProfileManager();
	//Singleton
	static std::unique_ptr<ProfileManager> instance_;
public:
	//Initializes the instance
	static void Init();
	//Kills the instance
	static void Kill();
	//Getter of the instance
	static ProfileManager& Instance();
};

#endif