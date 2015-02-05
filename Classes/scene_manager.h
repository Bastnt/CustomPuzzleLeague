#ifndef __SCENE_MANAGER_H_CPL__
#define __SCENE_MANAGER_H_CPL__

#include <2d\CCScene.h>
#include <base\CCDirector.h>

#include <memory>

class AppDelegate;

//Orchestrates the scenes
class SceneManager
{
	static std::unique_ptr<SceneManager> instance_;
	cocos2d::Director* director_;
	SceneManager();

public:
	static void Init();
	static void Kill();
	static SceneManager& Instance();
	//Returns the first scene to be runned in the game
	void StartInitialScene() const;
};

#endif