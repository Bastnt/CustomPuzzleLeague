#include "gamepad.h"

Gamepad::AxeMapping::AxeMapping(float p_threshold, EventInputGamepad::Input p_positive, EventInputGamepad::Input p_negative, cocos2d::RepetitionClock p_clock)
	: threshold(p_threshold), on_positive_value(p_positive), on_negative_value(p_negative), clock(p_clock), previous_value(EventInputGamepad::Input::NONE) {}


EventInputGamepad::Input Gamepad::AxeMapping::GetInput(float current_axe_value) const
{
	if(current_axe_value >= threshold)
		return on_positive_value;
	if(current_axe_value <= -threshold)
		return on_negative_value;
	return EventInputGamepad::Input::NONE;
}

Gamepad::Gamepad(std::vector<EventInputGamepad::Input> button_maps, std::vector<Gamepad::AxeMapping> axes_maps, std::string p_name)
	: button_mappings(std::move(button_maps)), axe_mappings(std::move(axes_maps)), name(std::move(p_name)) {}