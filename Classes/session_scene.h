#ifndef __SESSION_SCENE_H__
#define __SESSION_SCENE_H__

#include "2d\CCLayer.h"
#include "2d\CCScene.h"

#include "board.h"
#include "session.h"

class SessionScene : public cocos2d::Layer
{
public:
	// Cocos
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SessionScene);

	// My configuration
	Session config;

private:
	Matrix model;
	SessionScene();
	static float BLOCK_SIZE_;
};

#endif // __GAME_H__
