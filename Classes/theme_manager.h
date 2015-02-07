#ifndef __THEME_MANAGER_H_CPL__
#define __THEME_MANAGER_H_CPL__

#include <cocos2d\external\json\document.h>
#include <2d\CCNode.h>

#include <memory>
#include <string>
#include <map>

#include "character.h"

enum DefaultItemId
{
	CURSOR,
	MAIN_MENU_SOLO,
	MAIN_MENU_MULTIPLAYER,
	MAIN_MENU_OPTIONS,
	CHARACTER_ICON,
	CHARACTER_SPRITE,
	CHARACTER_GAME_BACKGROUND,
};

//Parses the themes and contains data about 'em
class ThemeManager
{
	//The theme object (JSON)
	rapidjson::Document current_theme_;
	//The theme path
	std::string path_current_theme_;
	//Basic private constructor (singleton)
	ThemeManager();
	//Singleton
	static std::unique_ptr<ThemeManager> instance_;

	using NodeValue = rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> >;
	//Add the provided element to a node, submethod of AddElementsToNode
	static void AddElementToNode(const NodeValue& node_json, cocos2d::Node* to_add, cocos2d::Node* node);

	//The loaded characters 
	std::map<std::string, Character> characters_;
	//Load a character
	static void LoadCharacter(const rapidjson::Document& chara_json, Character& chara);
	//Submethods of LoadCharacter method
	static void LoadSharedSounds(std::vector<SharedSounds>& to_be_filled, std::size_t max_size,  const char* to_parse, const rapidjson::Document& json);
	static void LoadVectorString(std::vector<std::string>& to_be_filled, const NodeValue& parsed);
public:
	//Initializes the instance
	static void Init();
	//Kills the instance
	static void Kill();
	//Getter of the instance
	static ThemeManager& Instance();
	
	//Load the theme with provided name
	void LoadTheme(const std::string& theme_name);
	
	//Load the characters from folders
	void LoadCharacters();

	//Add children to the provided node based on the name
	void AddElementsToNode(const std::string& scene_name, cocos2d::Node* node);

	//Gets the default node for element based on 
	cocos2d::Node* GetDefaultNode(DefaultItemId id);
	//Gets the default path for element based on 
	static std::string GetDefaultPath(DefaultItemId id);
};

#endif