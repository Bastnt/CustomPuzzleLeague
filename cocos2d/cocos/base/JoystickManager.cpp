#include "base/JoystickManager.h"

USING_NS_CC;

std::unique_ptr<JoystickManager> JoystickManager::instance_ = nullptr;

JoystickManager& JoystickManager::Instance()
{
	if(!instance_)
		instance_ = std::make_unique<JoystickManager>(private_structure{});
	return *instance_;
}

void JoystickManager::Kill() 
{
    if (instance_)
		instance_ = nullptr;
}

JoystickManager::JoystickManager(const private_structure &) {}

void JoystickManager::PollEvents()
{

}
