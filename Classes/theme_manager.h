#ifndef __THEME_MANAGER_H_CPL__
#define __THEME_MANAGER_H_CPL__

class AppDelegate;
#include <memory>

//Parses the themes and contains data about 'em
class ThemeManager
{
	ThemeManager();
	static std::unique_ptr<ThemeManager> instance_;
public:
	static ThemeManager& Instance();
	static void Init();
	static void Kill();
};

#endif