#include "profile_manager.h"

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