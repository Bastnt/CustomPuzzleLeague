#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include <stdint.h>
#include <vector>
#include <memory>

#include "player.h"

class Session {
public:
	float margin;
	float padding;
	uint32_t width;
	short height;
	short real_height;
	unsigned char max_color;
	float time_step;
	float falling_time;
	float dying_time;
	float swap_time;
	float hanging_time;

	std::vector<std::shared_ptr<Player> > players;

	Session();
};

#endif