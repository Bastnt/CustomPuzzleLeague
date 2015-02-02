#ifndef __cocos2d_custom__EventJoystick__
#define __cocos2d_custom__EventJoystick__

#include "base/CCEvent.h"

#include <cstddef>

NS_CC_BEGIN

class Joystick;

class CC_DLL EventJoystick : public Event
{
public:
	//Different types of Joystick Event
    enum class EventType
    {
		JOYSTICK_MOVE,
        BUTTON_PRESSED,
		BUTTON_RELEASED,
		CONNECT,
		DISCONNECT,
    };
    EventJoystick(Joystick* joy, EventJoystick::EventType type);

    Joystick& getJoystick() const;
	void setJoystick(Joystick* joy);
	
    EventJoystick::EventType getJoystickEventType() const;
	void setJoystickEventType(EventJoystick::EventType type);
    
protected:
    Joystick* joystick_;
	EventJoystick::EventType joystick_event_type_;
};

class CC_DLL EventButtonJoystick : public EventJoystick
{
public:
    EventButtonJoystick(Joystick* joy, EventJoystick::EventType type, std::size_t index_button);
	
    std::size_t getIndexButton() const;
	void setIndexButton(std::size_t button);
private:
	std::size_t button_;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__EventJoystick__) */