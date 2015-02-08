#ifndef __PLAYER_LOBBY_H_CPL___
#define __PLAYER_LOBBY_H_CPL___

#include <2d\CCNode.h>

class PlayerLobby : public cocos2d::Node
{
	enum class State
	{
		UNUSED,
		PROFILE,
		CHARACTER,
		DIFFICULTY,
		BLOCK_THEME,
		COMPLETED
	};
	State state_;

	//The id of the gamepad to be listened
	std::size_t gamepad_id_;

	//Private destructor (cocos2dx fashion)
	PlayerLobby();

	//Changes the state of the player lobby
	void ChangeState(State state);
public:
	virtual bool init() override;

	CREATE_FUNC(PlayerLobby);

	//Called by LobbyScene on first event : push start
	void OnPushStart(std::size_t gamepad_id);
	
	//Called by LobbyScene on first event : push start
	std::size_t GetGamepadId() const;
};

#endif