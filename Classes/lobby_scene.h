#ifndef __LOBBY_SCENE_H_CPL__
#define __LOBBY_SCENE_H_CPL__

#include <2d\CCLayer.h>
#include <2d\CCScene.h>

#include "session.h"
#include "player_lobby.h"

class LobbyScene : public cocos2d::Layer
{
	enum class State
	{
		IDLE,
		ADDING,
		DELETING,
	};
	//The state of the view
	State state_;
	//The session to be launched by the board later on, configured in the scene
	Session session_;
	//The players lobbys
	std::vector<PlayerLobby*> lobbies;
	//Creates and empty scene waiting for a new input of a gamepad
	void AddEmptyLobby();
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	void InitiateSession();

	CREATE_FUNC(LobbyScene);
};

#endif