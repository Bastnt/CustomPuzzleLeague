#include "scene_manager.h"

#include <2d\CCTransition.h>

#include "start_screen.h"
#include "main_menu.h"
#include "session_scene.h"

std::unique_ptr<SceneManager> SceneManager::instance_ = nullptr;

void SceneManager::Init() 
{
	SceneManager::instance_.reset(new SceneManager());
}

void SceneManager::Kill() 
{
	for(auto& scene : instance_->scenes_)
	{
		if(scene)
			scene->release();
	}
	SceneManager::instance_ = nullptr;
}

SceneManager& SceneManager::Instance() 
{
	return *instance_;
}

SceneManager::SceneManager() : director_ { cocos2d::Director::getInstance() }, scenes_(static_cast<std::size_t>(SceneId::__MAX_VALUE__), nullptr)
{
}

void SceneManager::StartInitialScene()
{
	scenes_[0] = StartScreen::createScene();
	scenes_[0]->retain();
	director_->runWithScene(scenes_[0]);
}


void SceneManager::ChangeScene(SceneId scene_id, TransitionPolicy transition_policy)
{
	std::size_t index { static_cast<std::size_t>(scene_id) };
	switch (scene_id)
	{
	case SceneId::START_SCREEN:
	{
		if(!scenes_[index])
		{
			scenes_[index] = StartScreen::createScene();
			scenes_[index]->retain();
		}
	} break;
	case SceneId::MAIN_MENU:
	{		   
		if(!scenes_[index])
		{
			scenes_[index] = MainMenu::createScene();
			scenes_[index]->retain();
		}
	} break;
	default:
		return;
	}

	switch (transition_policy)
	{
	case TransitionPolicy::SLIDE_IN_L:
		director_->replaceScene(cocos2d::TransitionSlideInL::create(.5f, scenes_[index]));
		break;
	case TransitionPolicy::SLIDE_IN_R:
		director_->replaceScene(cocos2d::TransitionSlideInR::create(.5f, scenes_[index]));
		break;
	case TransitionPolicy::SLIDE_IN_T:
		director_->replaceScene(cocos2d::TransitionSlideInT::create(.5f, scenes_[index]));
		break;
	case TransitionPolicy::SLIDE_IN_B:
		director_->replaceScene(cocos2d::TransitionSlideInB::create(.5f, scenes_[index]));
		break;
	default:
		break;
	}

}