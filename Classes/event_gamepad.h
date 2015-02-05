#ifndef EVENT_GAMEPAD_INPUT_CPL
#define EVENT_GAMEPAD_INPUT_CPL

#include <base/CCEventCustom.h>
#include <stdint.h>

class EventGamepad : public cocos2d::EventCustom
{
public:
	enum class Type : uint8_t
	{
		CONNECT,//Connection of a gamepad
		DISCONNECT,//Disconnection of a gamepad
		PRESSED,//Input pressed on a gamepad
		RELEASED,//Input released on a gamepad
	};

    /** Constructor */
    EventGamepad(std::size_t gamepad_id, EventGamepad::Type type);
    
    /** Gets event sub type */
    inline EventGamepad::Type getEventGamepadType() const { return type_; };
    inline std::size_t getGamepadId() const { return gamepad_id_; };
protected:
    EventGamepad::Type type_;
    std::size_t gamepad_id_;
};

class EventInputGamepad : public EventGamepad
{
public:
	//Available input for the games
	enum class Input : uint8_t
	{
		VALIDATION_SWAP,//Validates or swaps blocks
		CANCEL_SWAP,//Cancels or swaps blocks
		VALIDATION_PAUSE,//Validates or pauses game
		SCROLL,//Scrolls blocks
		LEFT,//Goes left
		RIGHT,//Goest right
		UP,//Goes up
		DOWN,//Goes down
		NONE//No input
	};

    /** Constructor */
    EventInputGamepad(std::size_t gamepad_id, EventGamepad::Type type, EventInputGamepad::Input input);
    
    inline EventInputGamepad::Input getInput() const { return input_; };
protected:
    EventInputGamepad::Input input_;
};

#endif
