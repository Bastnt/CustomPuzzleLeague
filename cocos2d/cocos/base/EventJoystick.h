#ifndef __cocos2d_custom__EventJoystick__
#define __cocos2d_custom__EventJoystick__

#include "base/CCEvent.h"

NS_CC_BEGIN
/**
 * Data returned in this class is based off of the GLFW joystick API
 * http://www.glfw.org/docs/latest/group__input.html#gaffcbd9ac8ee737fcdd25475123a3c790
 */
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
    
private:
    Joystick* joystick_;
	EventJoystick::EventType joystick_event_type_;
};
NS_CC_END

#endif /* defined(__cocos2d_libs__EventJoystick__) */