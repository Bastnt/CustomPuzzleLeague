#include "theme_manager.h"

std::unique_ptr<ThemeManager> ThemeManager::instance_ = nullptr;

void ThemeManager::Init() {
	ThemeManager::instance_ = std::make_unique<ThemeManager>();
}

void ThemeManager::Kill() {
	ThemeManager::instance_ = nullptr;
}

ThemeManager& ThemeManager::Instance() {
	return *instance_;
}

ThemeManager::ThemeManager() {}