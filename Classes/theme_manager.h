#ifndef __THEME_MANAGER_H_CPL__
#define __THEME_MANAGER_H_CPL__

#include <cocos2d\external\json\document.h>
#include <2d\CCNode.h>

#include <memory>
#include <string>

class AppDelegate;

//Parses the themes and contains data about 'em
class ThemeManager
{
	struct private_structure {
	};
	static std::unique_ptr<ThemeManager> instance;

	//The theme object (JSON)
	rapidjson::Document current_theme;
	//The theme path
	std::string path_current_theme;
public:
	explicit ThemeManager(const ThemeManager::private_structure&);
	static ThemeManager& Instance();
	
	//Load the theme with provided name
	void LoadTheme(const std::string& theme_name);

	//Add children to the provided node based on the name
	void AddElementsToNode(const std::string& scene_name, cocos2d::Node* node);

	friend class AppDelegate;
};

#endif