#ifndef __cocos2d_custom__EventJoystick__
#define __cocos2d_custom__EventJoystick__

#include "base/CCEvent.h"

#include <cstddef>

NS_CC_BEGIN

class Joystick;
class JoystickAxe;

class CC_DLL EventJoystick : public Event
{
public:
	//Different types of Joystick Event
    enum class Type
    {
		AXE_ENABLED,
        BUTTON_PRESSED,
		BUTTON_RELEASED,
		CONNECT,
		DISCONNECT,
    };
    EventJoystick(Joystick* joy, EventJoystick::Type type);

    Joystick& getJoystick() const;
    EventJoystick::Type getJoystickEventType() const;    
protected:
    Joystick* joystick_;
	EventJoystick::Type joystick_event_type_;
};

class CC_DLL EventButtonJoystick : public EventJoystick
{
public:
    EventButtonJoystick(Joystick* joy, EventJoystick::Type type, std::size_t index_button);
	
    std::size_t getIndexButton() const;
private:
	std::size_t button_;
};

//A quasi copy of EventButtonJoystick (but might change in the future)
class CC_DLL EventAxeJoystick : public EventJoystick
{
public:
    EventAxeJoystick(Joystick* joy, EventJoystick::Type type, std::size_t index_axe);
	
    std::size_t getIndexAxe() const;
	JoystickAxe& getAxe() const;
private:
	std::size_t axe_;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__EventJoystick__) */