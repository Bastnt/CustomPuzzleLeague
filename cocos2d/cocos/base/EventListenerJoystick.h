#ifndef __cocos2d_custom__EventListenerJoystick__
#define __cocos2d_custom__EventListenerJoystick__

#include "base/CCEventListener.h"

NS_CC_BEGIN

class Event;

class CC_DLL EventListenerJoystick : public EventListener
{
public:
    static const std::string LISTENER_ID;
    static EventListenerJoystick* create();

    /// Overrides
    virtual EventListenerJoystick* clone() override;
    virtual bool checkAvailable() override;

    std::function<void(Event* event)> onConnect;
    std::function<void(Event* event)> onDisconnect;
    std::function<void(std::size_t index_button, Event* event)> onButtonPressed;
    std::function<void(std::size_t index_button, Event* event)> onButtonReleased;
    std::function<void(Event* event)> onJoystickMoved;

CC_CONSTRUCTOR_ACCESS:
    EventListenerJoystick();
    bool init();
};
NS_CC_END

#endif