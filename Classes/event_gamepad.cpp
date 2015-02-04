#include "event_gamepad.h"


EventGamepad::EventGamepad(std::size_t gamepad_id, EventGamepad::Type p_type) 
	: EventCustom("gamepad"), type_(p_type), gamepad_id_(gamepad_id) {}

EventInputGamepad::EventInputGamepad(std::size_t gamepad_id, EventGamepad::Type type, EventInputGamepad::Input input) 
	: EventGamepad(gamepad_id, type), input_(input) {}