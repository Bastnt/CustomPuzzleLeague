#include "2d\CCSprite.h"
#include "base\CCDirector.h"
#include "base\CCEventListenerKeyboard.h"
#include "base\CCEventKeyboard.h"
#include "base\CCEventDispatcher.h"

#include "session_scene.h"

USING_NS_CC;

SessionScene::SessionScene() : model(config) {

}

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

	model.AddLine(Matrix::Fill::RANDOMLY);
	model.AddLine(Matrix::Fill::RANDOMLY);
	model.AddLine(Matrix::Fill::RANDOMLY);
	model.AddLine(Matrix::Fill::RANDOMLY);

	auto matrix = Board::create(model, { window_size.height*config.width / config.height, window_size.height - 2 * config.margin });
	matrix->setPosition({ window_size.width / 2.f, window_size.height / 2.f });
	matrix->setAnchorPoint({ .5f, .5f });

	addChild(matrix);

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [matrix](EventKeyboard::KeyCode keyCode, Event* event)
	{
		log("Key with keycode %d pressed", keyCode);
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			matrix->MoveCursor(Board::Direction::UP);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			matrix->MoveCursor(Board::Direction::DOWN);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			matrix->MoveCursor(Board::Direction::RIGHT);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			matrix->MoveCursor(Board::Direction::LEFT);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			matrix->Swap();
			break;
		case EventKeyboard::KeyCode::KEY_CTRL:
			matrix->Scroll();
			break;
		default:
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}