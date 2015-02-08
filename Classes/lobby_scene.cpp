#include "lobby_scene.h"

#include <2d\CCActionInterval.h>
#include <2d\CCActionInstant.h>
#include <base\CCEventDispatcher.h>
#include "event_listener_gamepad.h"
#include "event_gamepad.h"

#include "theme_manager.h"

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

	lobbies.reserve(16);
	
	ThemeManager::Instance().AddElementsToNode("lobby_scene", dynamic_cast<cocos2d::Node*>(this));
	InitiateSession();

	auto listener = EventListenerGamepad::create();
	listener->onPressed = [this] (EventInputGamepad* event)
	{
		auto input = event->getInput();
		if(input == EventInputGamepad::Input::VALIDATION_PAUSE)
		{
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
		
	lobbies.push_back(lobby);

	auto spawn = cocos2d::Spawn::createWithTwoActions(
				cocos2d::ScaleTo::create(0.5f, 0.95f),  //Scale to theorical scaling factor
				cocos2d::MoveTo::create(0.5f, { getContentSize().width / 2.f, lobby->getPositionY()})); //Move to theorical position
			lobby->runAction(spawn);
	auto idling = cocos2d::Sequence::createWithTwoActions(
				cocos2d::DelayTime::create(0.5f),
				cocos2d::CallFunc::create([this](){ state_ = State::IDLE; })
				);
	runAction(idling);
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
		
		lobbies.push_back(lobby);

		//Calculating margin, equals to 5% of total_width in total
		float margin { (0.05f * getContentSize().width) / (lobbies.size()+1) };
		// (k+1).margin + k.width = total_width
		float estimated_size_after_scaling { 0.95f * getContentSize().width / (lobbies.size()) };
		float scaling_factor { estimated_size_after_scaling / lobby->getContentSize().width };

		float current_position_x { margin+estimated_size_after_scaling/2.f };
		margin += estimated_size_after_scaling;

		for(auto& lobby : lobbies)
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
}