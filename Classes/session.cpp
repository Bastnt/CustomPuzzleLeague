#include "session.h"

// Default configuration
Session::Session() :
	margin(20.f),
	width(6),
	height(13),
	real_height(45),
	max_color(5),
	padding(1),
	time_step(.01f),
	//time_step(.06f),
	falling_time(1.f),
	dying_time(60.f),
	swap_time(4.f),
	hanging_time(10.f)
{}