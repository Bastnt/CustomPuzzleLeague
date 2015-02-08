#include "player_lobby.h"

#include "theme_manager.h"

bool PlayerLobby::init() 
{
	if(!cocos2d::Node::init())
		return false;

	setContentSize({960.f, 1080.f});
	
	ThemeManager::Instance().AddElementsToNode("player_lobby_start", dynamic_cast<cocos2d::Node*>(this));
}