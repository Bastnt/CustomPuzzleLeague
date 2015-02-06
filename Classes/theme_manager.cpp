#include "theme_manager.h"
#include <CCFileUtils.h>
#include <2d\CCSprite.h>
#include <2d\CCLabelBMFont.h>


std::unique_ptr<ThemeManager> ThemeManager::instance_ = nullptr;

void ThemeManager::Init() {
	ThemeManager::instance_.reset(new ThemeManager());
}

void ThemeManager::LoadTheme(const std::string& theme_name)
{
    std::string fullPath = cocos2d::FileUtils::sharedFileUtils()->fullPathForFilename("themes/"+theme_name+"/config.json");
	path_current_theme_ = "themes/"+theme_name+"/";
    std::string json = cocos2d::FileUtils::sharedFileUtils()->getStringFromFile(fullPath);
	current_theme_.Parse<0>(json.c_str());
}

void ThemeManager::AddElementsToNode(const std::string& scene_name, cocos2d::Node* node)
{
	if(current_theme_.IsObject() && current_theme_.HasMember(scene_name.c_str()))
	{
		const auto& scene_json = current_theme_[scene_name.c_str()];

		//Handles sprites first
		if(scene_json.HasMember("sprites") && scene_json["sprites"].IsArray())
		{
			const auto& sprites = scene_json["sprites"];
			for (rapidjson::SizeType i = 0U, end_i = sprites.Size(); i < end_i; ++i)
			{
				const auto& sprite = sprites[i];
				if(sprite.HasMember("path"))
				{
					//Creates a sprite
					auto to_add = cocos2d::Sprite::create(path_current_theme_+sprite["path"].GetString());
					if(to_add)
					{
						ThemeManager::AddElementToNode(sprite, to_add, node);
					}
				}
			}
		}

		//Handles labels
		if(scene_json.HasMember("labels") && scene_json["labels"].IsArray())
		{
			const auto& labels = scene_json["labels"];
			for (rapidjson::SizeType i = 0U, end_i = labels.Size(); i < end_i; ++i)
			{
				const auto& label = labels[i];
				if(label.HasMember("path") && label.HasMember("value"))
				{
					//Creates a label
					auto to_add = cocos2d::LabelBMFont::create(label["value"].GetString(), path_current_theme_+label["path"].GetString());
					if(to_add)
					{
						ThemeManager::AddElementToNode(label, to_add, node);
					}
				}
			}
		}
	}
}

void ThemeManager::AddElementToNode(const NodeValue& node_json, cocos2d::Node* to_add, cocos2d::Node* node)
{
	//Handles optional, common, parameters
	if(node_json.HasMember("anchor") && node_json["anchor"].IsArray() && node_json["anchor"].Size()==2)
		to_add->setAnchorPoint(cocos2d::Vec2(node_json["anchor"][0U].GetDouble(), node_json["anchor"][1U].GetDouble()));
	if(node_json.HasMember("position") && node_json["position"].IsArray() && node_json["position"].Size()==2)
		to_add->setPosition(cocos2d::Vec2(node_json["position"][0U].GetDouble(), node_json["position"][1U].GetDouble()));
	if(node_json.HasMember("name"))
		to_add->setName(node_json["name"].GetString());

	//Adds the node
	if(node_json.HasMember("z_index") && node_json["z_index"].IsNumber())
		node->addChild(to_add, node_json["z_index"].GetUint());
	else
		node->addChild(to_add);
}

void ThemeManager::Kill() {
	ThemeManager::instance_ = nullptr;
}

ThemeManager& ThemeManager::Instance() {
	return *instance_;
}

ThemeManager::ThemeManager() 
{
	LoadTheme("default");
}


cocos2d::Node* ThemeManager::GetDefaultNode(DefaultItemId id)
{
	switch (id)
	{
	case CURSOR:
	{
		auto node = cocos2d::LabelBMFont::create(">", "themes/default/main_menu/pixel.fnt");
		node->setAnchorPoint({1.f,.5f});
		return node;
	} break;
	case MAIN_MENU_SOLO:
	{
		auto node = cocos2d::LabelBMFont::create("SOLO", "themes/default/main_menu/pixel.fnt");
		node->setName("solo");
		node->setPosition({960.f, 780.f});
		return node;
	} break;
	case MAIN_MENU_MULTIPLAYER:
	{
		auto node = cocos2d::LabelBMFont::create("MULTIPLAYER", "themes/default/main_menu/pixel.fnt");
		node->setName("multi");
		node->setPosition({960.f, 540.f});
		return node;
	} break;
	case MAIN_MENU_OPTIONS:
	{
		auto node = cocos2d::LabelBMFont::create("OPTIONS", "themes/default/main_menu/pixel.fnt");
		node->setName("options");
		node->setPosition({960.f, 300.f});
		return node;
	} break;
	default:
		break;
	}
	return nullptr;
}
