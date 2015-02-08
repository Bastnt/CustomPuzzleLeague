#ifndef __PLAYER_LOBBY_H_CPL___
#define __PLAYER_LOBBY_H_CPL___

#include <2d\CCNode.h>

class PlayerLobby : public cocos2d::Node
{
public:
	virtual bool init() override;

	CREATE_FUNC(PlayerLobby);
};

#endif