#ifndef __PROFILE_MANAGER_H_CPL__
#define __PROFILE_MANAGER_H_CPL__

#include <memory>
#include <vector>
#include <map>

#include "profile.h"
#include <cocos2d\external\json\document.h>
#include <cocos2d\external\json\stringbuffer.h>
#include <cocos2d\external\json\prettywriter.h>

//Holds the profiles and is in charge of saving/loading them
class ProfileManager
{
	//Basic constructor
	ProfileManager();
	//Singleton
	static std::unique_ptr<ProfileManager> instance_;
	//Profiles
	std::map<std::string, std::shared_ptr<Profile> > profiles_;
	using NodeValue = rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> >;
	using Writer = rapidjson::Writer< rapidjson::GenericStringBuffer< rapidjson::UTF8<> > >;
	//Try to load a profile from profiles.json
	bool LoadProfile(Profile& profile, const NodeValue& json);
	//Save a profile
	void SaveProfile(const Profile& profile, Writer& writer);
public:
	//Initializes the instance
	static void Init();
	//Kills the instance
	static void Kill();
	//Getter of the instance
	static ProfileManager& Instance();
	
	//Loads the current profiles from profiles.json
	void LoadProfiles();
	//Save the profiles on profiles.json
	void SaveProfiles();
};

#endif