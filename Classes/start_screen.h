#ifndef __START_SCREEN_H_CPL_
#define __START_SCREEN_H_CPL_

#include <2d\CCLayer.h>
#include <2d\CCScene.h>

class StartScreen : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(StartScreen);
};

#endif