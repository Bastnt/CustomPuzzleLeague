#ifndef CPL_GAMEPAD
#define CPL_GAMEPAD

#include <base/RepetitionClock.h>
#include <vector>
#include "event_gamepad.h"

class Gamepad
{
public:
	class AxeMapping 
	{
	public:
		float threshold;
		EventInputGamepad::Input on_positive_value;
		EventInputGamepad::Input on_negative_value;
		EventInputGamepad::Input previous_value;//Remembers the previous correct value for released event
		cocos2d::RepetitionClock clock;
		AxeMapping(float threshold = 1.1f, EventInputGamepad::Input on_positive_value_event = EventInputGamepad::Input::NONE,
			EventInputGamepad::Input on_negative_value_event = EventInputGamepad::Input::NONE, cocos2d::RepetitionClock clock = cocos2d::RepetitionClock());

		//Gets the current input based on threshold and provided value between -1.f and 1.f
		EventInputGamepad::Input GetInput(float current_axe_value) const;
	};

	//Actions of the buttons for the gamepad
	std::vector<EventInputGamepad::Input> button_mappings; 
	//Actions of the axes for the gamepad
	std::vector<AxeMapping> axe_mappings;
	//The name of the gamepad
	std::string name;

	//Basic constructor
	Gamepad(std::vector<EventInputGamepad::Input>, std::vector<Gamepad::AxeMapping>, std::string name);
};

#endif