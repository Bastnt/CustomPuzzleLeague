#ifndef __PLAYER_H_CPL__
#define __PLAYER_H_CPL__

#include <memory>
class Profile;
class Character;

class Player
{
public:
	//Selected profile
	std::shared_ptr<Profile> profile; 
	//Selected character
	std::shared_ptr<Character> player; 
};

#endif