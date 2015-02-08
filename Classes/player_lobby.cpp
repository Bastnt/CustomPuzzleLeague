#include "player_lobby.h"

#include <base\CCEventDispatcher.h>
#include "event_listener_gamepad.h"
#include "event_gamepad.h"

#include "theme_manager.h"

#include "lobby_scene.h"


PlayerLobby::PlayerLobby() : gamepad_id_ { 16u /* Cannot be reached (systemic) */} , state_ { State::UNUSED } {};

bool PlayerLobby::init() 
{
	if(!cocos2d::Node::init())
		return false;

	setContentSize({960.f, 1080.f});
	
	ChangeState(State::UNUSED);

	auto listener = EventListenerGamepad::create();
	listener->onPressed = [this] (EventInputGamepad* event)
	{
		if(event->getGamepadId() == gamepad_id_)
		{
			if(event->getInput()==EventInputGamepad::Input::CANCEL_SWAP)
			{
				LobbyScene* parent = dynamic_cast<LobbyScene*>(getParent());
				if(parent)
				{
					parent->DeleteLobby(this);
				}
			}
			event->stopPropagation();
		}
	};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void PlayerLobby::OnPushStart(std::size_t p_gamepad_id)
{
	gamepad_id_ = p_gamepad_id;
	ChangeState(State::PROFILE);
}


std::size_t PlayerLobby::GetGamepadId() const
{
	return gamepad_id_;
}

void PlayerLobby::ChangeState(State state) 
{
	state_ = state;
	removeAllChildrenWithCleanup(true);
	switch (state)
	{
	case PlayerLobby::State::UNUSED: 
	{
		ThemeManager::Instance().AddElementsToNode("player_lobby_start", dynamic_cast<cocos2d::Node*>(this));
	} break;
	case PlayerLobby::State::PROFILE:
	{
		ThemeManager::Instance().AddElementsToNode("player_lobby_profile", dynamic_cast<cocos2d::Node*>(this));

	} break;
	case PlayerLobby::State::CHARACTER: 
	{

	} break;
	case PlayerLobby::State::DIFFICULTY: 
	{

	} break;
	case PlayerLobby::State::BLOCK_THEME: 
	{

	} break;
	case PlayerLobby::State::COMPLETED: 
	{

	} break;
	default:
		break;
	}
}