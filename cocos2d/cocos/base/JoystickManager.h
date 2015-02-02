#ifndef __cocos2d_custom__JoystickManager__
#define __cocos2d_custom__JoystickManager__

#include "platform/CCPlatformMacros.h"
#include "base/Joystick.h"

#include <memory>
#include <array>
#include <string>
#include <map>

NS_CC_BEGIN

class Event;
class CC_DLL JoystickManager
{
	//trick found on http://stackoverflow.com/questions/8147027/how-do-i-call-stdmake-shared-on-a-class-with-only-protected-or-private-const/8147213#8147213
   struct private_structure {
   };
public:
	explicit JoystickManager(const private_structure &);

	//Kill the instance
	static void Kill();
	
	//Gets the instance
	static JoystickManager& Instance();

	//The joysticks (16 is the max amount of recognized joysticks)
	std::array<std::shared_ptr<Joystick>, 16U> joysticks;

	//Poll the events
	void PollEvents();

private:
	static std::unique_ptr<JoystickManager> instance_;

	//Handles the raw datas of the joystick of index i
	void UpdateRawDatas(int i /*index_joystick */);

	std::chrono::steady_clock clock_;
	
};

NS_CC_END
#endif