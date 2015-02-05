#include "start_screen.h"
#include <2d\CCSprite.h>
#include <base\CCEventDispatcher.h>

#include "event_listener_gamepad.h"
#include "event_gamepad.h"

cocos2d::Scene* StartScreen::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = StartScreen::create();
	scene->addChild(layer);
	return scene;
}

bool StartScreen::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto bg = cocos2d::Sprite::create("bg.jpg");
	bg->setAnchorPoint({0.f, 0.f});
	addChild(bg, 1);

	auto listener = EventListenerGamepad::create();
	listener->onPressed = [] (EventInputGamepad* event)
	{
#ifdef _DEBUG
		cocos2d::log("A valid input was pressed!");
#endif
	};
	listener->onReleased = [] (EventInputGamepad* event)
	{
#ifdef _DEBUG
		cocos2d::log("A valid input was released!");
#endif
	};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}