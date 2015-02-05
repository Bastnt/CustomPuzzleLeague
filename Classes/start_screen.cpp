#include "start_screen.h"
#include <2d\CCSprite.h>
#include <base\CCEventDispatcher.h>

#include "event_listener_gamepad.h"
#include "event_gamepad.h"

#include "theme_manager.h"

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

	ThemeManager::Instance().AddElementsToNode("start_screen", dynamic_cast<cocos2d::Node*>(this));

	auto listener = EventListenerGamepad::create();
	listener->onPressed = [] (EventInputGamepad* event)
	{
		if(event->getInput() == EventInputGamepad::Input::VALIDATION_PAUSE)
		{
#ifdef _DEBUG
		cocos2d::log("Pressed start!");
#endif
		}
	};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}