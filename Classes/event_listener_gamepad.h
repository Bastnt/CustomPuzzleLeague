#ifndef EVENT_LISTENER_GAMEPAD
#define EVENT_LISTENER_GAMEPAD

#include <base/CCEventListenerCustom.h>
class EventGamepad;
class EventInputGamepad;

class EventListenerGamepad : public cocos2d::EventListenerCustom
{
public:
    static EventListenerGamepad* create();
    
    /// Overrides
    virtual bool checkAvailable() override;
    virtual EventListenerGamepad* clone() override;
	
    std::function<void (EventGamepad* event)> onConnect;
    std::function<void (EventGamepad* event)> onDisconnect;
    std::function<void (EventInputGamepad* event)> onPressed;
    std::function<void (EventInputGamepad* event)> onReleased;
    
CC_CONSTRUCTOR_ACCESS:
    /** Constructor */
    EventListenerGamepad();
    
    /** Initializes event with type and callback function */
    bool init();
	    
protected:
};

#endif