#ifndef __cocos2d_custom__Joystick__
#define __cocos2d_custom__Joystick__

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class CC_DLL Joystick
{
public:
    Joystick();
	//Whether the joystick is currently present or not
	bool present;
	//The name of the joystick
    const char* name;
	//The unique identifier of the joystick
    int id;
	//The amount of buttons and buttons values
    int buttonValuesCount;
    const unsigned char* buttonValues;
	//The amount of axes and axes values
    // e.g. ps3: left: x,y right:x,y x (left)-1<=x<=1(right) (up)-1<=y<=1(down)
    int axesCount;
    const float* axes;
};

NS_CC_END

#endif