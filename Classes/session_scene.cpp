#include "2d\CCSprite.h"
#include "base\CCDirector.h"
#include "base\CCEventListenerKeyboard.h"
#include "base\CCEventKeyboard.h"
#include "base\CCEventDispatcher.h"

#include "session_scene.h"
#include "board.h"
#include "event_listener_gamepad.h"
#include "event_gamepad.h"

USING_NS_CC;

SessionScene::SessionScene() {}

Scene* SessionScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SessionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SessionScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto director = Director::getInstance();
	auto window_size = director->getVisibleSize();



	auto board = Board::create(config, { window_size.height*config.width / config.height, window_size.height - 2 * config.margin });

	board->AddLine();
	board->AddLine();
	board->AddLine();
	board->AddLine();
	board->setAnchorPoint({ 1.f, 0.077f });
	
	board->setPosition({ window_size.width, 0 });

	auto frame = DrawNode::create();
	frame->setContentSize({ window_size.height*config.width / config.height, window_size.height - 2 * config.margin });
	auto fsize = frame->getContentSize();
	frame->drawRect({ 0, 0 }, { fsize.width, fsize.height }, { 1.f, 1.f, 1.f, 1.f });
	frame->setAnchorPoint({ 1.f,0 });
	frame->setPosition({ window_size.width,0 });
	addChild(frame);

	addChild(board);
	auto listener = EventListenerKeyboard::create();
	

	auto listener2 = EventListenerGamepad::create();
	listener2->onPressed = [board](EventInputGamepad* event)
	{
		switch (event->getInput()) {
		case EventInputGamepad::Input::UP:
			board->MoveCursor(Board::Direction::UP);
			break;
		case EventInputGamepad::Input::DOWN:
			board->MoveCursor(Board::Direction::DOWN);
			break;
		case EventInputGamepad::Input::RIGHT:
			board->MoveCursor(Board::Direction::RIGHT);
			break;
		case EventInputGamepad::Input::LEFT:
			board->MoveCursor(Board::Direction::LEFT);
			break;
		case EventInputGamepad::Input::VALIDATION_SWAP:
			board->Swap();
			break;
		case EventInputGamepad::Input::SCROLL:
			board->Scroll();
			break;
		default:
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);


	listener->onKeyPressed = [board, director](EventKeyboard::KeyCode keyCode, Event* event)
	{
		log("Key with keycode %d pressed", keyCode);
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			board->MoveCursor(Board::Direction::UP);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			board->MoveCursor(Board::Direction::DOWN);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			board->MoveCursor(Board::Direction::RIGHT);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			board->MoveCursor(Board::Direction::LEFT);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			board->Swap();
			break;
		case EventKeyboard::KeyCode::KEY_CTRL:
			board->Scroll();
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			director->end();
			break;
		default:
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}