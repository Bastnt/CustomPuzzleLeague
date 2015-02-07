#ifndef __LOBBY_SCENE_H_CPL__
#define __LOBBY_SCENE_H_CPL__

#include <2d\CCLayer.h>
#include <2d\CCScene.h>

class LobbyScene : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(LobbyScene);
};

#endif