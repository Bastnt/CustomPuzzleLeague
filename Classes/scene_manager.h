#ifndef __SCENE_MANAGER_H_CPL__
#define __SCENE_MANAGER_H_CPL__

#include <2d\CCScene.h>

#include <memory>
#include "start_screen.h"

class AppDelegate;

//Orchestrates the scenes
class SceneManager
{   
	struct private_structure {
	};
	static std::unique_ptr<SceneManager> instance;
public:
	explicit SceneManager(const SceneManager::private_structure&);
	static SceneManager& Instance();
	
	//Returns the first scene to be runned in the game
	cocos2d::Scene* GetInitialScene() const;

	friend class AppDelegate;
};

#endif