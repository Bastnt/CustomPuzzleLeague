#ifndef __MAIN_MENU_SCENE_H_CPL__
#define __MAIN_MENU_SCENE_H_CPL__

#include <2d\CCLayer.h>
#include <2d\CCScene.h>
#include "theme_manager.h"

#include <vector>

class MainMenuScene : public cocos2d::Layer
{
	enum class State : uint8_t
	{
		SOLO,
		MULTIPLAYER,
		OPTIONS,
		__MAX_VALUE__,
	};
	State current_state_;
	//Nodes pointers to the nodes of selection
	std::vector<cocos2d::Node*> menu_items_;
	//Cursor of selection
	cocos2d::Node* menu_cursor_;
	//Changes the states and cursor position
	void ChangeState(State state);
	//Submethods for init
	void BuildMenuItem(const std::string& name, DefaultItemId id, uint32_t z_index);
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(MainMenuScene);
};

#endif