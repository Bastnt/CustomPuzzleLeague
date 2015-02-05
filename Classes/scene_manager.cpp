#include "scene_manager.h"

#include "start_screen.h"

std::unique_ptr<SceneManager> SceneManager::instance = nullptr;

SceneManager& SceneManager::Instance()
{return *instance;}

SceneManager::SceneManager(const SceneManager::private_structure&) {}

cocos2d::Scene* SceneManager::GetInitialScene() const
{
	return StartScreen::createScene();
}