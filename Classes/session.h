#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include <stdint.h>

class Session {
public:
	float const margin;
	float const padding;
	uint32_t const width;
	short const height;
	short const real_height;
	unsigned char const max_color;
	float time_step;
	float falling_time;
	float dying_time;
	float swap_time;
	float hanging_time;

	Session();
};

#endif