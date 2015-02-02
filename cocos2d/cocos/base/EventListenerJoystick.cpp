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
        ret->onJoystickMoved = onJoystickMoved;
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
: onConnect(nullptr), onDisconnect(nullptr), onButtonPressed(nullptr), onButtonReleased(nullptr), onJoystickMoved(nullptr)
{}

bool EventListenerJoystick::init()
{
    auto listener = [this](Event* event){
        auto joystick_event = dynamic_cast<EventJoystick*>(event);
        switch (joystick_event->getJoystickEventType())
        {
            case EventJoystick::EventType::CONNECT:
			{
                if(onConnect != nullptr)
                    onConnect(event);
			} break;
            case EventJoystick::EventType::DISCONNECT:
			{
                if(onDisconnect != nullptr)
                    onDisconnect(event);
			} break;
            case EventJoystick::EventType::BUTTON_PRESSED:
			{
				auto joystick_button_event = dynamic_cast<EventButtonJoystick*>(event);
                if(joystick_button_event && onButtonPressed != nullptr)
                    onButtonPressed(joystick_button_event->getIndexButton(), event);
			} break;
            case EventJoystick::EventType::BUTTON_RELEASED:
			{
				auto joystick_button_event = dynamic_cast<EventButtonJoystick*>(event);
                if(joystick_button_event && onButtonReleased != nullptr)
                    onButtonReleased(joystick_button_event->getIndexButton(), event);
			} break;
            case EventJoystick::EventType::JOYSTICK_MOVE:
			{
				if(onJoystickMoved != nullptr)
                    onJoystickMoved(event);
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