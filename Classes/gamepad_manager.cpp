#include "gamepad_manager.h"

#include <base/EventListenerJoystick.h>
#include <base/EventJoystick.h>
#include <base/CCEventDispatcher.h>
#include <base/CCDirector.h>
#include <base/JoystickManager.h>

#include "event_gamepad.h"

GamepadManager::GamepadManager()
{
	//Initializes gamepads from existing joysticks
	for(std::size_t i = 0U; i < 16U; ++i)
	{
		if(cocos2d::JoystickManager::Instance().joysticks[i])
		{
			//Creates gamepad
			cocos2d::Joystick& joy { *cocos2d::JoystickManager::Instance().joysticks[i] };
			gamepads[i] = GamepadManager::ConstructDefaultGamepad(joy);

			//Sends event
			EventGamepad gamepad_event { static_cast<std::size_t>(joy.getIndex()), EventGamepad::Type::CONNECT };
			cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&gamepad_event);
		}
		else
			gamepads[i] = nullptr;
	}

	
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

	//Highest priority
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}

std::unique_ptr<Gamepad> GamepadManager::ConstructDefaultGamepad(cocos2d::Joystick& joy)
{
	using In = EventInputGamepad::Input;

	if(joy.getName() == "Pilote de joystick PC Microsoft")
	{
		//Xbox One and Xbox 360 Controllers
		std::vector<EventInputGamepad::Input> button_mappings 
		{ 
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

		std::vector<Gamepad::AxeMapping> axe_mappings 
		{
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
	else //default unrecognized gamepad!!
	{
		cocos2d::log("Unrecognized gamepad '%s', set default, dumb, inputs", joy.getName());
		std::vector<EventInputGamepad::Input> button_mappings 
		{ 
			In::VALIDATION_PAUSE,
			In::VALIDATION_SWAP,
			In::SCROLL,
			In::UP, 
			In::RIGHT, 
			In::DOWN, 
			In::LEFT,
			In::CANCEL_SWAP,
		};
		if(joy.button_states.size() <= button_mappings.size())
		{
			//Takes as much as possible
			button_mappings.resize(joy.button_states.size());
		}
		else
		{
			//Fill the rest with useless input
			button_mappings.reserve(joy.button_states.size());
			while(button_mappings.size() < button_mappings.capacity())
				button_mappings.push_back(In::NONE);
		}

		std::vector<Gamepad::AxeMapping> axe_mappings 
		{ 
			{ .4f, In::RIGHT, In::LEFT, {true, cocos2d::RepetitionClock::Milli(700), cocos2d::RepetitionClock::Milli(150)}},
			{ .4f, In::DOWN, In::UP, {true, cocos2d::RepetitionClock::Milli(700), cocos2d::RepetitionClock::Milli(150)}},
		};
		if(joy.axes.size() <= axe_mappings.size())
		{
			//Takes as much as possible
			axe_mappings.resize(joy.axes.size());
		}
		else
		{
			//Fill the rest with useless input
			axe_mappings.reserve(joy.axes.size());
			while(axe_mappings.size() < axe_mappings.capacity())
				axe_mappings.emplace_back(1.1f, In::NONE, In::NONE, cocos2d::RepetitionClock());
		}

		return std::make_unique<Gamepad>(std::move(button_mappings), std::move(axe_mappings), joy.getName());
	}
}