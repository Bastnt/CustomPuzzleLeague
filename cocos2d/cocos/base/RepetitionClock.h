#ifndef __cocos2d_custom__RepetitionClock__
#define __cocos2d_custom__RepetitionClock__

#include "platform/CCPlatformMacros.h"

#include <chrono>

NS_CC_BEGIN

class CC_DLL RepetitionClock
{
public:
	using Milli = std::chrono::milliseconds;
	using Instant = std::chrono::steady_clock::time_point;

	//Basic constructor
    RepetitionClock(bool enabled = false, Milli delay_repetition = Milli(1200), Milli frequence_repetition = Milli(333));

	//Starts the clock, must be called on button pressed event
	void Start(Instant current_time_point);
	//Stops the clock, must be called on button released event
	void Stop();

	//Whether the input is to be considered egarding the spent amount of time and whether this button is repetable or not
	bool ConsiderInput(Instant current_time_point);
		
	//Whether the repetition is enabled or not
	bool enabled;
	
	//The duration before the first repetition after pressing the button the first time
	Milli delay_repetition;
	//The duration after the first repetition after pressing the button the first time
	Milli frequency_repetition;

	//Sets the repetition clock
	void Setup(bool enabled, Milli delay, Milli frequency);

	//Whether the clock is started or not
	bool IsStarted() const;
private:
	//Whether the repetition has started or not
	bool started_;
	//The previous moment
	Instant previous_;
	//The spent duration
	Milli duration_;
	//Whether the repetition is before the first one or not
	bool before_first_;
};

NS_CC_END

#endif