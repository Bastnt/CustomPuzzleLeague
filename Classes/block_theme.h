#ifndef __BLOCK_THEME_H_CPL__
#define __BLOCK_THEME_H_CPL__

#include <vector>
#include <memory>
#include <string>

//Holds data for a loaded block theme
class BlockTheme
{
public:
	//The name of the block theme, also its unique identifier
	std::string name;

	//The paths to the color blocks and metal (first position)
	std::vector<std::string> living_blocks;
	//Cursor path
	std::string cursor;

	//Basic constructor
	BlockTheme(std::string name = "");
};

#endif