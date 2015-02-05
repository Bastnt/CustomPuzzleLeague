#ifndef __cocos2d_custom__EventListenerJoystick__
#define __cocos2d_custom__EventListenerJoystick__

#include "base/CCEventListener.h"

NS_CC_BEGIN

class Event;
class EventJoystick;
class EventButtonJoystick;
class EventAxeJoystick;

class CC_DLL EventListenerJoystick : public EventListener
{
public:
    static const std::string LISTENER_ID;
    static EventListenerJoystick* create();

    /// Overrides
    virtual EventListenerJoystick* clone() override;
    virtual bool checkAvailable() override;

    std::function<void (EventJoystick* event)> onConnect;
    std::function<void (EventJoystick* event)> onDisconnect;
    std::function<void (EventButtonJoystick* event)> onButtonPressed;
    std::function<void (EventButtonJoystick* event)> onButtonReleased;
    std::function<void (EventAxeJoystick* event)> onAxeMoved;
    std::function<void (EventAxeJoystick* event)> onAxeNeutralized;

CC_CONSTRUCTOR_ACCESS:
    EventListenerJoystick();
    bool init();
};
NS_CC_END

#endif