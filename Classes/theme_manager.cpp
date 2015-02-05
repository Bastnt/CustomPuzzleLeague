#include "theme_manager.h"
#include <CCFileUtils.h>
#include <2d\CCSprite.h>


std::unique_ptr<ThemeManager> ThemeManager::instance_ = nullptr;

void ThemeManager::Init() {
	ThemeManager::instance_.reset(new ThemeManager());
}

void ThemeManager::LoadTheme(const std::string& theme_name)
{
    std::string fullPath = cocos2d::FileUtils::sharedFileUtils()->fullPathForFilename("themes/"+theme_name+"/config.json");
	path_current_theme = "themes/"+theme_name+"/";
    std::string json = cocos2d::FileUtils::sharedFileUtils()->getStringFromFile(fullPath);
	current_theme.Parse<0>(json.c_str());
}


void ThemeManager::AddElementsToNode(const std::string& scene_name, cocos2d::Node* node)
{
	if(current_theme.IsObject() && current_theme.HasMember(scene_name.c_str()))
	{
		const auto& scene_json = current_theme[scene_name.c_str()];
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
					std::string s = sprite["path"].GetString();
					auto to_add = cocos2d::Sprite::create(path_current_theme+sprite["path"].GetString());
					if(to_add)
					{
						//Handles optional parameters
						if(sprite.HasMember("anchor") && sprite["anchor"].IsArray() && sprite["anchor"].Size()==2)
							to_add->setAnchorPoint(cocos2d::Vec2(sprite["anchor"][0U].GetDouble(), sprite["anchor"][1U].GetDouble()));
						if(sprite.HasMember("position") && sprite["position"].IsArray() && sprite["position"].Size()==2)
							to_add->setPosition(cocos2d::Vec2(sprite["position"][0U].GetDouble(), sprite["position"][1U].GetDouble()));

						//Adds the sprite
						if(sprite.HasMember("z_index") && sprite["z_index"].IsNumber())
							node->addChild(to_add, sprite["z_index"].GetUint());
						else
							node->addChild(to_add);
					}
				}
			}
		}
	}
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
