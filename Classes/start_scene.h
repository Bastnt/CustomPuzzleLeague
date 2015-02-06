#ifndef __START_SCENE_H_CPL___
#define __START_SCENE_H_CPL___

#include <2d\CCLayer.h>
#include <2d\CCScene.h>

class StartScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(StartScene);
};

#endif