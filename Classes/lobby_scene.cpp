#include "lobby_scene.h"

#include <2d\CCActionInterval.h>
#include <2d\CCActionInstant.h>
#include <2d\CCActionEase.h>
#include <base\CCEventDispatcher.h>
#include "event_listener_gamepad.h"
#include "event_gamepad.h"

#include "theme_manager.h"
#include "scene_manager.h"

//FOR TESTS ONLY
#include "random_generator.h"


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

	lobbies_.reserve(16);
	
	ThemeManager::Instance().AddElementsToNode("lobby_scene", dynamic_cast<cocos2d::Node*>(this));
	InitiateSession();

	auto listener = EventListenerGamepad::create();
	listener->onPressed = [this] (EventInputGamepad* event)
	{
		if(lobbies_.size()==1 && event->getInput()==EventInputGamepad::Input::CANCEL_SWAP)
		{
			SceneManager::Instance().ChangeScene(SceneId::MAIN_MENU, TransitionPolicy::SLIDE_IN_L);
		}
		else if(IsNewGamepad(event->getGamepadId()))
		{
			std::size_t gamepad_id = event->getGamepadId();
			(lobbies_.back())->OnPushStart(gamepad_id);
			AddEmptyLobby();
		}
	};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}

void LobbyScene::InitiateSession()
{
	//Reset the session
	session_ = Session();

	//Changes the state
	state_ = State::ADDING;

	//Creates the first slot for the player 1
	auto lobby = PlayerLobby::create();
		addChild(lobby, 2);
		lobby->setPosition({3000.f, 540.f});
		lobby->setAnchorPoint({0.5f, 0.5f});
		lobby->setScale(0.f);
		
	lobbies_.push_back(lobby);
	
	RepositionLobbies();
}

void LobbyScene::AddEmptyLobby()
{
	if(state_ == State::IDLE)
	{
		auto lobby = PlayerLobby::create();
		addChild(lobby, 2);
		lobby->setPosition({3000.f, 540.f});
		lobby->setAnchorPoint({0.5f, 0.5f});
		lobby->setScale(0.f);

		//Changes the state
		state_ = State::ADDING;
		
		lobbies_.push_back(lobby);

		RepositionLobbies();
	}
}


void LobbyScene::DeleteLobby(PlayerLobby* to_be_deleted)
{
	if(state_ == State::IDLE)
	{
		auto it = std::find(lobbies_.begin(), lobbies_.end(), to_be_deleted);

		if(it != lobbies_.end())
		{
			//Changes the state
			state_ = State::DELETING;
			
			auto lobby = *it;

			//Remove the node from the vector of lobbies
			lobbies_.erase(it);

			auto removing = cocos2d::Sequence::createWithTwoActions(
				cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.25f, 0)),
				cocos2d::CallFunc::create([lobby](){ lobby->removeFromParentAndCleanup(true); })
			);
			lobby->runAction(removing);

			auto positioning = cocos2d::Sequence::createWithTwoActions(
				cocos2d::DelayTime::create(0.25f),
				cocos2d::CallFunc::create([this](){ RepositionLobbies(); })
			);
			runAction(positioning);
		}	
	}
}

void LobbyScene::RepositionLobbies()
{
	if(lobbies_.size()==1)
	{
		auto spawn = cocos2d::Spawn::createWithTwoActions(
					cocos2d::ScaleTo::create(0.5f, 0.95f),  //Scale to theorical scaling factor
					cocos2d::MoveTo::create(0.5f, { getContentSize().width / 2.f, (lobbies_.front())->getPositionY()})); //Move to theorical position
				(lobbies_.front())->runAction(spawn);
		auto idling = cocos2d::Sequence::createWithTwoActions(
					cocos2d::DelayTime::create(0.5f),
					cocos2d::CallFunc::create([this](){ state_ = State::IDLE; })
					);
		runAction(idling);
		return;
	}

	//Calculating margin, equals to 5% of total_width in total
	float margin { (0.05f * getContentSize().width) / (lobbies_.size()+1) };
	// (k+1).margin + k.width = total_width
	float estimated_size_after_scaling { 0.95f * getContentSize().width / (lobbies_.size()) };
	float scaling_factor { estimated_size_after_scaling / (lobbies_.front())->getContentSize().width };

	float current_position_x { margin+estimated_size_after_scaling/2.f };
	margin += estimated_size_after_scaling;

	for(auto& lobby : lobbies_)
	{
		auto spawn = cocos2d::Spawn::createWithTwoActions(
			cocos2d::ScaleTo::create(0.5f, scaling_factor),  //Scale to theorical scaling factor
			cocos2d::MoveTo::create(0.5f, { current_position_x, lobby->getPositionY()})); //Move to theorical position
		lobby->runAction(spawn);
		current_position_x += margin;
	}
	auto idling = cocos2d::Sequence::createWithTwoActions(
			cocos2d::DelayTime::create(0.5f),
			cocos2d::CallFunc::create([this](){ state_ = State::IDLE; })
			);
	runAction(idling);
}

bool LobbyScene::IsNewGamepad(std::size_t gamepad_id) const
{
	for(auto& lobby : lobbies_)
	{
		if(lobby->GetGamepadId()==gamepad_id)
			return false;
	}
	return true;
}