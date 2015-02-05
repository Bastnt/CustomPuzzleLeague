#include "RepetitionClock.h"

NS_CC_BEGIN

RepetitionClock::RepetitionClock(bool p_enabled, Milli p_delay_repetition, Milli p_frequence_repetition) 
	: enabled(p_enabled), delay_repetition(p_delay_repetition), frequency_repetition(p_frequence_repetition), started_(false), before_first_(true), previous_(Milli(0))
{}

void RepetitionClock::Start(Instant current_time_point)
{
	if(enabled)
	{
		previous_ = current_time_point;
		before_first_ = true;
		duration_ = Milli(0);
		started_ = true;
	}
}

void RepetitionClock::Stop()
{
	if(started_)
		started_ = false;
}

bool RepetitionClock::ConsiderInput(Instant current_time_point)
{
	if(enabled && started_)
	{
		duration_ += std::chrono::duration_cast<Milli>(current_time_point - previous_);
		previous_ = current_time_point;
		if(before_first_)
		{
			if(duration_ >= delay_repetition)
			{
				duration_ -= delay_repetition;
				before_first_ = false;
				return true;
			}
			return false;
		}
		else
		{
			if(duration_ >= frequency_repetition)
			{
				duration_ -= frequency_repetition;
				return true;
			}
			return false;
		}
	}
	return false;
}

void RepetitionClock::Setup(bool p_enabled, Milli p_delay, Milli p_frequency)
{
	enabled = p_enabled;
	delay_repetition = p_delay;
	frequency_repetition = p_frequency;
}


bool RepetitionClock::IsStarted() const
{
	return started_;
}

NS_CC_END