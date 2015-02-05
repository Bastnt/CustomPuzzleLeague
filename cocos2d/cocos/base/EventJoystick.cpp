#include "EventJoystick.h"
#include "Joystick.h"

NS_CC_BEGIN

EventJoystick::EventJoystick(Joystick& joy, EventJoystick::Type type)
    : Event(Event::Type::JOYSTICK), joystick_(joy), joystick_event_type_(type)
{}

Joystick& EventJoystick::getJoystick() const
{
	return joystick_;
}

EventJoystick::Type EventJoystick::getJoystickEventType() const
{
	return joystick_event_type_;
}


EventButtonJoystick::EventButtonJoystick(Joystick& joy, EventJoystick::Type type, std::size_t index_button)
: EventJoystick(joy, type), button_(index_button) {}
	
std::size_t EventButtonJoystick::getIndexButton() const
{
	return button_;
}


EventAxeJoystick::EventAxeJoystick(Joystick& joy, EventJoystick::Type type, std::size_t index_axe)
 : EventJoystick(joy, type), axe_(index_axe) {}
	
std::size_t EventAxeJoystick::getIndexAxe() const
{
	return axe_;
}

JoystickAxe& EventAxeJoystick::getAxe() const
{
	return joystick_.axes[axe_];
}

NS_CC_END