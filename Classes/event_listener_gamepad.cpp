#include "event_listener_gamepad.h"
#include "event_gamepad.h"

EventListenerGamepad::EventListenerGamepad()
: EventListenerCustom(), onConnect(nullptr), onDisconnect(nullptr), onPressed(nullptr), onReleased(nullptr)
{
}

EventListenerGamepad* EventListenerGamepad::create()
{
    EventListenerGamepad* ret = new (std::nothrow) EventListenerGamepad();
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

bool EventListenerGamepad::init()
{
    bool ret = false;
    
    auto listener = [this](cocos2d::Event* event){
		auto casted = dynamic_cast<EventGamepad*>(event);
		if(casted)
		{
			switch(casted->getEventGamepadType())
			{
			case EventGamepad::Type::CONNECT:
			{
				if(onConnect != nullptr)
					onConnect(casted);
			} break;
			case EventGamepad::Type::DISCONNECT:
			{
				if(onDisconnect != nullptr)
					onDisconnect(casted);
			} break;
			case EventGamepad::Type::PRESSED:
			{
				auto input = dynamic_cast<EventInputGamepad*>(casted);
				if(input && onPressed != nullptr)
					onPressed(input);
			} break;
			case EventGamepad::Type::RELEASED:
			{
				auto input = dynamic_cast<EventInputGamepad*>(casted);
				if(input && onReleased != nullptr)
					onReleased(input);
			} break;
			}
		}
    };
    
    if (EventListener::init(EventListener::Type::CUSTOM, "gamepad", listener))
    {
        ret = true;
    }
    return ret;
}

EventListenerGamepad* EventListenerGamepad::clone()
{
    EventListenerGamepad* ret = new (std::nothrow) EventListenerGamepad();
    if (ret && ret->init())
    {
        ret->autorelease();
        ret->onConnect = onConnect;
        ret->onDisconnect = onDisconnect;
        ret->onPressed = onPressed;
        ret->onReleased = onReleased;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerGamepad::checkAvailable()
{
	return true;//to avoid double check
}