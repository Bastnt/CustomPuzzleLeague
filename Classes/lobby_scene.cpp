#include "lobby_scene.h"

cocos2d::Scene* LobbyScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = LobbyScene::create();
	scene->addChild(layer);
	return scene;
}

bool LobbyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	
	return true;
}