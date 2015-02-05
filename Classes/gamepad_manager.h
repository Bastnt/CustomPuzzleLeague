#ifndef GAMEPAD_MANAGER
#define GAMEPAD_MANAGER

#include <base/Joystick.h>

#include <array>
#include <memory>
#include <chrono>

#include "gamepad.h"

//Handles the gamepads and sends event
class GamepadManager
{
public:
	GamepadManager();
	
private:
	//The gamepads (16 is the max amount of recognized joysticks)
	std::array<std::unique_ptr<Gamepad>, 16U> gamepads;

	//Creates a gamepad based on the provided joystick (also changes the joystick!
	static std::unique_ptr<Gamepad> GamepadManager::ConstructDefaultGamepad(cocos2d::Joystick& joystick);
	//The clock for the sticks
	std::chrono::steady_clock clock_;
};

#endif