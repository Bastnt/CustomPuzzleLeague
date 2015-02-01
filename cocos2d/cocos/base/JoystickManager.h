#ifndef __cocos2d_custom__JoystickManager__
#define __cocos2d_custom__JoystickManager__

#include "platform/CCPlatformMacros.h"
#include "base/Joystick.h"

#include <memory>
#include <array>

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

	//The joysticks
	std::array<Joystick, 16U> Joysticks;

	//Poll the events
	void PollEvents();

private:
	static std::unique_ptr<JoystickManager> instance_;
};
NS_CC_END
#endif /* defined(__cocos2d_libs__EventListenerJoystick__) */