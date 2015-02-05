#include "scene_manager.h"

#include "start_screen.h"
#include "Game.h"

std::unique_ptr<SceneManager> SceneManager::instance_ = nullptr;

void SceneManager::Init() {
	SceneManager::instance_.reset(new SceneManager());
}

void SceneManager::Kill() {
	SceneManager::instance_ = nullptr;
}

SceneManager& SceneManager::Instance() {
	return *instance_;
}

SceneManager::SceneManager() {
	director_ = cocos2d::Director::getInstance();
}

void SceneManager::StartInitialScene() const
{
	auto s = Game::createScene();
	director_->runWithScene(s);
}