#ifndef __SOUND_MANAGER_H_CPL__
#define __SOUND_MANAGER_H_CPL__

#include <string>

//Handles the sound being played in the game
class SoundManager
{
public:
	static void Play(std::string to_play);
	static void PlayBackground(std::string to_play);
	static void Preload(std::string to_preload);
};

#endif
