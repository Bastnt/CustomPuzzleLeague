#include "EventJoystick.h"

NS_CC_BEGIN

EventJoystick::EventJoystick(Joystick* joy, EventJoystick::EventType type)
    : Event(Type::JOYSTICK), joystick_(joy), joystick_event_type_(type)
{}

Joystick& EventJoystick::getJoystick() const
{
	return *joystick_;
}

void EventJoystick::setJoystick(Joystick* joy)
{
	joystick_ = joy;
}

EventJoystick::EventType EventJoystick::getJoystickEventType() const
{
	return joystick_event_type_;
}

void EventJoystick::setJoystickEventType(EventJoystick::EventType type)
{
	joystick_event_type_ = type;
}


EventButtonJoystick::EventButtonJoystick(Joystick* joy, EventJoystick::EventType type, std::size_t index_button)
: EventJoystick(joy, type), button_(index_button) {}
	
std::size_t EventButtonJoystick::getIndexButton() const
{
	return button_;
}

void EventButtonJoystick::setIndexButton(std::size_t button)
{
	button_ = button;
}

NS_CC_END