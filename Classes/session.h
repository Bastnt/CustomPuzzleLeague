#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include <stdint.h>
#include <vector>
#include <memory>

#include "player.h"

class Session {
public:
	float margin;

	// ====== Configurable members ======

	// Height to which we hit the ground
	uint32_t ground_height;
	// Width of the matrix
	uint32_t width;
	// Playable matrix height
	uint32_t height;
	// Matrix height including hiden buffer for garbages
	uint32_t real_height;
	// Total number of colors
	unsigned char max_color;
	// Time unit between two physic calls (in seconds)
	float time_step;
	// Falling time (in steps)
	uint32_t falling_time;
	// Dying time (in steps)
	uint32_t dying_time;
	// Swap time (in steps)
	uint32_t swap_time;
	// Hanging time (in steps)
	uint32_t hanging_time;
	// Time to generate a newline (in steps)
	uint32_t creep_shift_time;
	// Size of a block computed relative to the screen height
	float block_size;

	Session();
	void UpdateConstants();

	// ====== Processed members ======

	// Division of a block
	uint32_t block_division;
	// Number of steps between creep moves
	uint32_t creep_division_steps;
	// Number of creep moves between newline generation
	uint32_t newline_generation_creep_moves;

	std::vector<std::shared_ptr<Player> > players;

};

#endif