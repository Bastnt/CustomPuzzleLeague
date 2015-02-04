#include "base/Joystick.h"

NS_CC_BEGIN

Joystick::Joystick() {}

void Joystick::Init()
{
	button_states = std::vector<bool>(button_values_count_, false);
	repetition_clocks = std::vector<RepetitionClock>(button_values_count_, { false });
	axes = std::vector<JoystickAxe>(axes_count_, JoystickAxe());
}


int Joystick::getIndex() const
{
	return id_;
}

std::string Joystick::getName() const
{
	return name_;
}
NS_CC_END