#include "base/JoystickAxe.h"

NS_CC_BEGIN

JoystickAxe::JoystickAxe() : value(0.f), dead_zone_(.20f), moved(false)
{}


void JoystickAxe::SetDeadZone(float p_dead_zone)
{
	dead_zone_ = p_dead_zone;
}

bool JoystickAxe::HasInput() const
{
	return value > dead_zone_ || value < - dead_zone_;
}

NS_CC_END