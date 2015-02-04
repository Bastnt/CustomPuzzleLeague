#include "EventListenerJoystick.h"
#include "EventJoystick.h"

NS_CC_BEGIN

const std::string EventListenerJoystick::LISTENER_ID = "__cc_joystick";

bool EventListenerJoystick::checkAvailable()
{
    return true;
}
EventListenerJoystick* EventListenerJoystick::clone()
{
    auto ret = new EventListenerJoystick();
    if (ret && ret->init())
    {
        ret->autorelease();
        ret->onConnect = onConnect;
        ret->onDisconnect = onDisconnect;
        ret->onAxeMoved = onAxeMoved;
		ret->onAxeNeutralized = onAxeNeutralized;
        ret->onButtonReleased = onButtonReleased;
        ret->onButtonPressed = onButtonPressed;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}
EventListenerJoystick* EventListenerJoystick::create()
{
    auto ret = new EventListenerJoystick();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

EventListenerJoystick::EventListenerJoystick()
: onConnect(nullptr), onDisconnect(nullptr), 
onButtonPressed(nullptr), onButtonReleased(nullptr), 
onAxeMoved(nullptr), onAxeNeutralized(nullptr)
{}

bool EventListenerJoystick::init()
{
    auto listener = [this](Event* event){
        auto joystick_event = dynamic_cast<EventJoystick*>(event);
		if(joystick_event)
			switch (joystick_event->getJoystickEventType())
			{
				case EventJoystick::Type::CONNECT:
				{
					if(onConnect != nullptr)
						onConnect(joystick_event);
				} break;
				case EventJoystick::Type::DISCONNECT:
				{
					if(onDisconnect != nullptr)
						onDisconnect(joystick_event);
				} break;
				case EventJoystick::Type::BUTTON_PRESSED:
				{
					auto joystick_button_event = dynamic_cast<EventButtonJoystick*>(joystick_event);
					if(joystick_button_event && onButtonPressed != nullptr)
						onButtonPressed(joystick_button_event);
				} break;
				case EventJoystick::Type::BUTTON_RELEASED:
				{
					auto joystick_button_event = dynamic_cast<EventButtonJoystick*>(joystick_event);
					if(joystick_button_event && onButtonReleased != nullptr)
						onButtonReleased(joystick_button_event);
				} break;
				case EventJoystick::Type::AXE_MOVED:
				{			 
					auto joystick_axe_event = dynamic_cast<EventAxeJoystick*>(joystick_event);
					if(joystick_axe_event && onAxeMoved != nullptr)
						onAxeMoved(joystick_axe_event);
				} break;
				case EventJoystick::Type::AXE_NEUTRALIZED:
				{			 
					auto joystick_axe_event = dynamic_cast<EventAxeJoystick*>(joystick_event);
					if(joystick_axe_event && onAxeNeutralized != nullptr)
						onAxeNeutralized(joystick_axe_event);
				} break;
				default: {} break;
			}
    };

    if (EventListener::init(Type::JOYSTICK, LISTENER_ID, listener))
    {
        return true;
    }
    
    return false;
}

NS_CC_END