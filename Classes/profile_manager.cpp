#include "profile_manager.h"

#include <chrono>
#include <ctime>
#include <cstdio>
#include <CCFileUtils.h>

std::unique_ptr<ProfileManager> ProfileManager::instance_ = nullptr;

void ProfileManager::Init() 
{
	ProfileManager::instance_.reset(new ProfileManager());
}

void ProfileManager::Kill() 
{
	ProfileManager::instance_ = nullptr;
}

ProfileManager& ProfileManager::Instance() 
{
	return *instance_;
}

ProfileManager::ProfileManager() {}

//Loads the current profiles from profiles.json
void ProfileManager::LoadProfiles()
{
	profiles_.clear();
	if(cocos2d::FileUtils::getInstance()->isFileExist("profiles.json"))
	{
		std::string json_str = cocos2d::FileUtils::getInstance()->getStringFromFile("profiles.json");
		rapidjson::Document json;
		if(json.Parse<0>(json_str.c_str()).HasParseError() || !json.IsArray())
		{
			cocos2d::log("'profiles.json' is not an array or error while parsing at %u : %s.", json.GetErrorOffset(), json.GetParseError());
			return;
		}
		std::shared_ptr<Profile> loaded { nullptr };
		for(rapidjson::SizeType i = 0U, end_i = json.Size(); i < end_i; ++i)
		{
			loaded = std::make_shared<Profile>();
			if(LoadProfile(*loaded, json[i]))
			{
				profiles_[loaded->pseudo] = std::move(loaded);
			}
		}
	}
	else
	{
		cocos2d::log("Could not find 'profiles.json'.");
	}
}

//Save the profiles on profiles.json
void ProfileManager::SaveProfiles()
{
	rapidjson::GenericStringBuffer< rapidjson::UTF8<> > buffer;
	rapidjson::Writer< rapidjson::GenericStringBuffer< rapidjson::UTF8<> > > writer(buffer);

	writer.StartArray();
	for(const auto& profile : profiles_)
		SaveProfile(*(profile.second), writer);
	writer.EndArray();

	FILE* file;
	file = fopen("profiles.json","w");
	fprintf(file, "%s", buffer.GetString());
}

bool ProfileManager::LoadProfile(Profile& profile, const NodeValue& json)
{
	if(json.HasMember("pseudo") && json["pseudo"].IsString())
	{
		std::string pseudo = json["pseudo"].GetString();
		if(pseudo.empty())
			return false;
		profile.pseudo = std::move(pseudo);
	}
	else
		return false;
	
	if(json.HasMember("last_use") && json["last_use"].IsUint64())
	{
		std::time_t c_last_use = static_cast<std::time_t>(json["last_use"].GetUint64());
		profile.last_use =std::chrono::steady_clock::from_time_t(std::move(c_last_use));
	}
	else
		profile.last_use = std::chrono::steady_clock::now();
}

void ProfileManager::SaveProfile(const Profile& profile, Writer& writer)
{
	writer.StartObject();
                
    writer.String("pseudo");
    writer.String(profile.pseudo.c_str(), static_cast<rapidjson::SizeType>(profile.pseudo.length()));

	std::time_t c_last_use = std::chrono::steady_clock::to_time_t(profile.last_use);
	writer.String("last_use");
    writer.Uint64(c_last_use);

    writer.EndObject();
}