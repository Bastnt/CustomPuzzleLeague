#include "scene_manager.h"

#include "start_screen.h"
#include "session_scene.h"

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
	auto s = SessionScene::createScene();
	director_->runWithScene(s);
}