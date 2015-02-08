#include "main_menu_scene.h"
#include <2d\CCSprite.h>

#include <base\CCEventDispatcher.h>
#include "event_listener_gamepad.h"
#include "event_gamepad.h"

#include "scene_manager.h"


cocos2d::Scene* MainMenuScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	ThemeManager::Instance().AddElementsToNode("main_menu", dynamic_cast<cocos2d::Node*>(this));

	cocos2d::Node* cursor = getChildByName("cursor");
	if(cursor)
		menu_cursor_ = cursor;
	else
	{
		menu_cursor_ = ThemeManager::Instance().GetDefaultNode(DefaultItemId::CURSOR);
		addChild(menu_cursor_, 2);
	}

	menu_items_.reserve(static_cast<std::size_t>(State::__MAX_VALUE__));
	BuildMenuItem("solo", DefaultItemId::MAIN_MENU_SOLO, 2);
	BuildMenuItem("multi", DefaultItemId::MAIN_MENU_MULTIPLAYER, 2);
	BuildMenuItem("options", DefaultItemId::MAIN_MENU_OPTIONS, 2);

	//Event handling
	auto listener = EventListenerGamepad::create();
	listener->onPressed = [this] (EventInputGamepad* event)
	{
		auto input = event->getInput();
		if(input == EventInputGamepad::Input::DOWN)
		{
			//Goes down! Increment state!
			State next = static_cast<State>(static_cast<uint8_t>(current_state_)+1U);
			if(next==State::__MAX_VALUE__)
				next = static_cast<State>(static_cast<uint8_t>(0));
			ChangeState(next);
		}
		else if(input == EventInputGamepad::Input::UP)
		{
			State next;
			if(static_cast<uint8_t>(current_state_) == 0U)
				ChangeState(static_cast<State>(static_cast<uint8_t>(State::__MAX_VALUE__)-1U));
			else
				ChangeState(static_cast<State>(static_cast<uint8_t>(current_state_)-1U));
		}
		else if(input == EventInputGamepad::Input::CANCEL_SWAP)
		{
			SceneManager::Instance().ChangeScene(SceneId::START, TransitionPolicy::SLIDE_IN_L);
		}
		else if (input == EventInputGamepad::Input::VALIDATION_SWAP && current_state_ == State::SOLO)
		{
			SceneManager::Instance().ChangeScene(SceneId::SOLO);
		}
	};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	ChangeState(State::SOLO);
	
	return true;
}

void MainMenuScene::ChangeState(State state)
{
	current_state_ = state;
	cocos2d::Node* state_node = menu_items_[static_cast<std::size_t>(current_state_)];
	const auto& position = state_node->getPosition();
	menu_cursor_->setPosition({position.x - state_node->getContentSize().width/2.f, position.y});
}


void MainMenuScene::BuildMenuItem(const std::string& name, DefaultItemId id, uint32_t z_index)
{
	cocos2d::Node* node = getChildByName(name);
	if(node)
		menu_items_.push_back(node);
	else
	{
		menu_items_.push_back(ThemeManager::Instance().GetDefaultNode(id));
		addChild(menu_items_.back(), z_index);
	}
}