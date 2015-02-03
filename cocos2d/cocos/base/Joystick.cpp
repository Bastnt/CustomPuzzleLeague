#include "base/Joystick.h"

NS_CC_BEGIN

Joystick::Joystick() {}

void Joystick::Init()
{
	button_states = std::vector<bool>(button_values_count_, false);
	repetition_clocks_ = std::vector<RepetitionClock>(button_values_count_, { true });
	axes = std::vector<JoystickAxe>(axes_count_, JoystickAxe());
}

NS_CC_END