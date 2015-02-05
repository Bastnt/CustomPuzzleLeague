#include "theme_manager.h"

std::unique_ptr<ThemeManager> ThemeManager::instance = nullptr;

ThemeManager& ThemeManager::Instance()
{return *instance;}

ThemeManager::ThemeManager(const ThemeManager::private_structure&) {}