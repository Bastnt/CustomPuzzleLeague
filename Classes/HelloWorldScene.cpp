#include "HelloWorldScene.h"

#include "gamepad_manager.h"
#include "event_listener_gamepad.h"
#include "event_gamepad.h"
#include <base/JoystickManager.h>

#include <array>
#include <memory>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Handles the gamepad events at lower level
	auto manager = GamepadManager::create();
	addChild(manager);
	
	auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
    {
		cocos2d::JoystickManager::Instance().ReconnectJoysticks();
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto listener2 = EventListenerGamepad::create();
	listener2->onPressed = [] (EventInputGamepad* event)
	{
		if(event->getInput() == EventInputGamepad::Input::LEFT)
			log("Left button was pressed!");
		else
			log("Another button was pressed!");
	};
	listener2->onReleased = [] (EventInputGamepad* event)
	{
		if(event->getInput() == EventInputGamepad::Input::RIGHT)
			log("Right button was released!");
		else
			log("Another button was released!");
	};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

    return true;
}
