#ifndef __cocos2d_custom__JoystickAxe__
#define __cocos2d_custom__JoystickAxe__

#include "platform/CCPlatformMacros.h"
#include <stdint.h>

NS_CC_BEGIN

class CC_DLL JoystickAxe 
{
public:
	//Basic constructor
	JoystickAxe();

	//The value of the axe between -1.f and 1.f
	float value;

	//The index of the axe amongst the other axes of the joystick
	uint16_t index_axe;

	//Deadzone setter
	void SetDeadZone(float dead_zone);
	//True whether the axe is not in its deadzone
	bool HasInput() const;

	//Whether the axe has moved or not
	bool moved;
private:
	//The positive threshold between 0.f and 1.f that invalidates the axes if value is below
	float dead_zone_;
};

NS_CC_END

#endif