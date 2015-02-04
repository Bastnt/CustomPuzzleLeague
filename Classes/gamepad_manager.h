#ifndef GAMEPAD_MANAGER
#define GAMEPAD_MANAGER

#include <2d/CCNode.h>
#include <base/Joystick.h>

#include <array>
#include <memory>
#include <chrono>

#include "gamepad.h"

//Handles the gamepads
class GamepadManager : public cocos2d::Node
{
	GamepadManager();
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamepadManager);
private:
	//The gamepads (16 is the max amount of recognized joysticks)
	std::array<std::unique_ptr<Gamepad>, 16U> gamepads;

	//Creates a gamepad based on the provided joystick (also changes the joystick!
	static std::unique_ptr<Gamepad> GamepadManager::ConstructDefaultGamepad(cocos2d::Joystick& joystick);

	//The clock for the sticks
	std::chrono::steady_clock clock_;
};

#endif