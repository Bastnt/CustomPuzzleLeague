#ifndef __THEME_MANAGER_H_CPL__
#define __THEME_MANAGER_H_CPL__

class AppDelegate;
#include <memory>

//Parses the themes and contains data about 'em
class ThemeManager
{
	struct private_structure {
	};
	static std::unique_ptr<ThemeManager> instance;
public:
	explicit ThemeManager(const ThemeManager::private_structure&);
	static ThemeManager& Instance();

	friend class AppDelegate;
};

#endif