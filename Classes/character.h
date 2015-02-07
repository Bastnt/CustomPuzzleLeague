#ifndef __CHARACTER_H_CPL__
#define __CHARACTER_H_CPL__

#include <vector>
#include <memory>
#include <string>

using SharedSounds = std::shared_ptr<std::vector<std::string> >;
//Holds data for a loaded character
class Character
{
public:
	//The name of the character, also its unique identifier
	std::string name;
	//The description of the character, to be displayed on certain conditions
	std::string description;

	//Sounds to be played on chaining
	std::vector<SharedSounds> chains_sounds;
	//Sounds to be played on comboing
	std::vector<SharedSounds> combos_sounds;
	//Sounds to be played on selecting
	std::vector<std::string> selection_sounds;
	//Sounds to be played on taunting
	std::vector<std::string> taunt_sounds;
	//Sounds to be played on winning
	std::vector<std::string> win_sounds;

	//Backgrounds to be displayed behind the board
	std::vector<std::string> game_backgrounds;
	//Character main sprite path
	std::string main_sprite_path;
	//Character icon sprite path
	std::string icon_sprite_path;

	//Basic constructor
	Character(std::string name = "");
};

#endif