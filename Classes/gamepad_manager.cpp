#include "gamepad_manager.h"

#include <base/EventListenerJoystick.h>
#include <base/EventJoystick.h>
#include <base/Joystick.h>
#include <base/CCEventDispatcher.h>
#include <base/CCDirector.h>

#include "event_gamepad.h"

bool GamepadManager::init()
{
	if(!Node::init())
		return false;

	//Initializes with empty gamepads
	for(std::size_t i = 0U; i < 16; ++i)
		gamepads[i] = nullptr;
	
	auto listener = cocos2d::EventListenerJoystick::create();

	listener->onConnect = [this] (cocos2d::EventJoystick* event)
	{
		//Creates the gamepad based on its name
		cocos2d::Joystick& joy { event->getJoystick() };
		std::string name { joy.getName() };
		gamepads[joy.getIndex()] = GamepadManager::ConstructDefaultGamepad(joy);

		//Sends event
		EventGamepad gamepad_event { static_cast<std::size_t>(joy.getIndex()), EventGamepad::Type::CONNECT };
		cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&gamepad_event);
	};

	listener->onDisconnect = [this] (cocos2d::EventJoystick* event)
	{
		//Sends event
		cocos2d::Joystick& joy { event->getJoystick() };		
		EventGamepad gamepad_event { static_cast<std::size_t>(joy.getIndex()), EventGamepad::Type::DISCONNECT };
		cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&gamepad_event);

		//Deletes the gamepad
		gamepads[joy.getIndex()].reset();
	};

	listener->onButtonPressed = [this] (cocos2d::EventButtonJoystick* event)
	{
		cocos2d::Joystick& joy { event->getJoystick() };
		std::size_t index { event->getIndexButton() };
		EventInputGamepad::Input input { gamepads[joy.getIndex()]->button_mappings[index] };
		if(input != EventInputGamepad::Input::NONE)
		{
			EventInputGamepad gamepad_event { static_cast<std::size_t>(joy.getIndex()), EventGamepad::Type::PRESSED, input };
			cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&gamepad_event);
		}
	};

	listener->onButtonReleased = [this] (cocos2d::EventButtonJoystick* event)
	{
		cocos2d::Joystick& joy { event->getJoystick() };
		std::size_t index { event->getIndexButton() };
		EventInputGamepad::Input input { gamepads[joy.getIndex()]->button_mappings[index] };
		if(input != EventInputGamepad::Input::NONE)
		{
			EventInputGamepad gamepad_event { static_cast<std::size_t>(joy.getIndex()), EventGamepad::Type::RELEASED, input };
			cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&gamepad_event);
		}
	};

	listener->onAxeMoved = [this] (cocos2d::EventAxeJoystick* event)
	{
		cocos2d::Joystick& joy { event->getJoystick() };
		std::size_t index { event->getIndexAxe() };
		float axe_value { joy.axes[event->getIndexAxe()].value };
		Gamepad::AxeMapping& axe_mapping { gamepads[joy.getIndex()]->axe_mappings[index] };
		EventInputGamepad::Input input { axe_mapping.GetInput(axe_value) };
		if(input != EventInputGamepad::Input::NONE)
		{
			axe_mapping.previous_value = input;
			if(!axe_mapping.clock.IsStarted())
			{
				axe_mapping.clock.Start(clock_.now());
				EventInputGamepad gamepad_event { static_cast<std::size_t>(joy.getIndex()), EventGamepad::Type::PRESSED, input };
				cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&gamepad_event);
			}
			else if(axe_mapping.clock.ConsiderInput(clock_.now()))
			{
				EventInputGamepad gamepad_event { static_cast<std::size_t>(joy.getIndex()), EventGamepad::Type::PRESSED, input };
				cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&gamepad_event);
			}
		}
		else if(axe_mapping.clock.IsStarted())
		{
			axe_mapping.clock.Stop();
			EventInputGamepad gamepad_event { static_cast<std::size_t>(joy.getIndex()), EventGamepad::Type::RELEASED, axe_mapping.previous_value };
			cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&gamepad_event);
		}
	};
	
	listener->onAxeNeutralized = [this] (cocos2d::EventAxeJoystick* event)
	{
		cocos2d::Joystick& joy { event->getJoystick() };
		std::size_t index { event->getIndexAxe() };
		float axe_value { joy.axes[event->getIndexAxe()].value };
		Gamepad::AxeMapping& axe_mapping { gamepads[joy.getIndex()]->axe_mappings[index] };
		if(axe_mapping.clock.IsStarted())
		{
			axe_mapping.clock.Stop();
			EventInputGamepad gamepad_event { static_cast<std::size_t>(joy.getIndex()), EventGamepad::Type::RELEASED, axe_mapping.previous_value };
			cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&gamepad_event);
		}
	};

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

GamepadManager::GamepadManager() {}

std::unique_ptr<Gamepad> GamepadManager::ConstructDefaultGamepad(cocos2d::Joystick& joy)
{
	using In = EventInputGamepad::Input;

	//if(name == "Pilote de joystick PC Microsoft")
	std::vector<EventInputGamepad::Input> button_mappings { 
		In::VALIDATION_SWAP, //A
		In::CANCEL_SWAP, //B
		In::NONE, 
		In::NONE, 
		In::SCROLL, //L
		In::SCROLL, //R
		In::NONE, 
		In::VALIDATION_PAUSE, //START
		In::NONE, 
		In::NONE, 
		In::UP, //POV_UP
		In::RIGHT, //POV_RIGHT
		In::DOWN, //POV_DOWN
		In::LEFT //POV_LEFT
	};

	std::vector<Gamepad::AxeMapping> axe_mappings {
		{ .4f, In::RIGHT, In::LEFT, {true, cocos2d::RepetitionClock::Milli(700), cocos2d::RepetitionClock::Milli(150)}},
		{ .4f, In::DOWN, In::UP, {true, cocos2d::RepetitionClock::Milli(700), cocos2d::RepetitionClock::Milli(150)}},
		{ 1.1f, In::NONE, In::NONE, {}},
		{ 1.1f, In::NONE, In::NONE, {}},
		{ 1.1f, In::NONE, In::NONE, {}},
	};

	//Changing the repetition clocks for the POV buttons:
	for(std::size_t i = 10U; i < 14; ++i)
	{
		joy.repetition_clocks[i].Setup(true, cocos2d::RepetitionClock::Milli(700), cocos2d::RepetitionClock::Milli(150));
	}

	return std::make_unique<Gamepad>(std::move(button_mappings), std::move(axe_mappings), joy.getName());
}