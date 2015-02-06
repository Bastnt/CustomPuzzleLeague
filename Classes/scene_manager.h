#ifndef __SCENE_MANAGER_H_CPL__
#define __SCENE_MANAGER_H_CPL__

#include <2d\CCScene.h>
#include <base\CCDirector.h>

#include <vector>
#include <memory>
#include "start_screen.h"
#include "scene_id.h"
#include "transition_policy.h"

//Orchestrates the scenes
class SceneManager
{
	//Singleton pattern
	static std::unique_ptr<SceneManager> instance_;
	//Direct access to the director
	cocos2d::Director* director_;
	//Basic constructor
	SceneManager();
	//Retains the Scenes so that they are not destroyed each time
	std::vector<cocos2d::Scene*> scenes_;
public:
	//Initializes the instance
	static void Init();
	//Kills the instance
	static void Kill();
	//Getter of the instance
	static SceneManager& Instance();
	//Sets the first scene and runs it
	void StartInitialScene();
	//Sets the current scene with a wonderful transition
	void ChangeScene(SceneId scene_id, TransitionPolicy transition_policy = TransitionPolicy::SLIDE_IN_R);
};

#endif