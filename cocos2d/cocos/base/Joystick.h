#ifndef __cocos2d_custom__Joystick__
#define __cocos2d_custom__Joystick__

#include "platform/CCPlatformMacros.h"
#include "base/RepetitionClock.h"

#include <chrono>
#include <vector>

NS_CC_BEGIN

class JoystickManager;
class CC_DLL Joystick
{
public:
	//States of the buttons
	std::vector<bool> button_states;//true: pressed, false: released

	//Basic constructor
    Joystick();

	friend class JoystickManager;
private:

	////////////////////
	//// RAW DATAS /////
	////////////////////
	//The name of the joystick
    const char* name_;
	//The unique identifier of the joystick
    int id_;
	//The amount of buttons and buttons values
    int button_values_count_;
    const unsigned char* button_values_;
	//The amount of axes and axes values
    // e.g. ps3: left: x,y right:x,y x (left)-1<=x<=1(right) (up)-1<=y<=1(down)
    int axes_count_;
    const float* axes_;
	
	//The repetition clock
	std::vector<RepetitionClock> repetition_clocks_;
};

NS_CC_END

#endif