#include "session.h"

// Default configuration
Session::Session() :
margin(20.f),
width(6),
height(13),
real_height(45),
max_color(5),
time_step(.017f),
//time_step(.06f),
falling_time(1.f),
dying_time(90.f),
swap_time(4.f),
hanging_time(15.f),
creep_shift_time(1000u),
block_division(15),
block_size(15.f),
ground_height(1)
{
	UpdateConstants();
}

void Session::UpdateConstants() {
	creep_division_steps = creep_shift_time / block_division;
	players.reserve(16u);
}