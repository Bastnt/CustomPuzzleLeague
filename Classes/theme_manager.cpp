#include "theme_manager.h"
#include <CCFileUtils.h>
#include <2d\CCSprite.h>
#include <2d\CCLabel.h>

std::unique_ptr<ThemeManager> ThemeManager::instance_ = nullptr;

void ThemeManager::Init() {
	ThemeManager::instance_.reset(new ThemeManager());
}

void ThemeManager::LoadTheme(const std::string& theme_name)
{
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename("themes/"+theme_name+"/config.json");
	path_current_theme_ = "themes/"+theme_name+"/";
    std::string json = cocos2d::FileUtils::getInstance()->getStringFromFile(fullPath);
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
					auto to_add = cocos2d::Label::createWithBMFont(path_current_theme_+label["path"].GetString(), label["value"].GetString());
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
	case DefaultItemId::CURSOR:
	{
		auto node = cocos2d::Label::createWithBMFont("themes/default/main_menu/pixel.fnt", "> ");
		node->setAnchorPoint({1.f,.5f});
		return node;
	} break;
	case DefaultItemId::MAIN_MENU_SOLO:
	{
		auto node = cocos2d::Label::createWithBMFont("themes/default/main_menu/pixel.fnt", "SOLO");
		node->setName("solo");
		node->setPosition({960.f, 780.f});
		return node;
	} break;
	case DefaultItemId::MAIN_MENU_MULTIPLAYER:
	{
		auto node = cocos2d::Label::createWithBMFont("themes/default/main_menu/pixel.fnt", "MULTIPLAYER");
		node->setName("multi");
		node->setPosition({960.f, 540.f});
		return node;
	} break;
	case DefaultItemId::MAIN_MENU_OPTIONS:
	{
		auto node = cocos2d::Label::createWithBMFont("themes/default/main_menu/pixel.fnt", "OPTIONS");
		node->setName("options");
		node->setPosition({960.f, 300.f});
		return node;
	} break;
	default:
		break;
	}
	return nullptr;
}

std::string ThemeManager::GetDefaultPath(DefaultItemId id)
{
	switch (id)
	{
	case DefaultItemId::CHARACTER_SPRITE:
		return "placeholder.png";
	case DefaultItemId::CHARACTER_ICON:
		return "placeholder.png";
	case DefaultItemId::CHARACTER_GAME_BACKGROUND:
		return "placeholder.png";
	default:
		return "";
	}
}


void ThemeManager::LoadCharacters()
{
	characters_.clear();

	auto file_util = cocos2d::FileUtils::getInstance();

	std::string fullPath = file_util->fullPathForFilename("characters/config.json");
    std::string json = file_util->getStringFromFile(fullPath);
	rapidjson::Document characters_array;
	characters_array.Parse<0>(json.c_str());
	std::string folder_name { "" };
	if(characters_array.IsArray())
	{
		for(rapidjson::SizeType i = 0U, end_i = characters_array.Size(); i < end_i; ++i)
		{
			folder_name = characters_array[i].GetString();
			if(file_util->isDirectoryExist("characters/"+folder_name) && file_util->isFileExist("characters/"+folder_name+"/config.json"))
			{
				std::string json = file_util->getStringFromFile(file_util->fullPathForFilename("characters/"+folder_name+"/config.json"));
				rapidjson::Document character_json;
				character_json.Parse<0>(json.c_str());
				if(character_json.IsObject() && character_json.HasMember("name") && character_json["name"].GetString() != "")
				{
					std::string chara_name { character_json["name"].GetString() };
					if(characters_.count(chara_name)==0)
					{
						Character chara { chara_name };
						LoadCharacter(character_json, chara);
						characters_[chara_name] = std::move(chara);
					}
					else
					{
						cocos2d::log("Ignored loading of character '%s' from folder '%s', its name is already used.", chara_name.c_str(), folder_name.c_str());
					}
				}
				else
				{
					cocos2d::log("Incorrect data for character '%s', cannot find name in config.json file.", folder_name.c_str());
				}
			}
			else
			{
				cocos2d::log("Incorrect data for character '%s', cannot find folder or config.json file.", folder_name.c_str());
			}
		}
	}
	else
	{
		cocos2d::log("Incorrect data or cannot find 'characters/config.json'.");
	}
}


void ThemeManager::LoadCharacter(const rapidjson::Document& json, Character& chara)
{
	//Handles description if any
	if(json.HasMember("description") && json["description"].IsString())
		chara.description = json["description"].GetString();

	//Handles sounds for chains
	ThemeManager::LoadSharedSounds(chara.chains_sounds, 14, "chains", json);
	
	//Handles sounds for combos
	ThemeManager::LoadSharedSounds(chara.combos_sounds, 30, "combos", json);
	
	//Handles sounds for selection
	if(json.HasMember("selection") && json["selection"].IsArray())
		ThemeManager::LoadVectorString(chara.selection_sounds, json["selection"]);

	//Handles sounds for taunt
	if(json.HasMember("taunt") && json["taunt"].IsArray())
		ThemeManager::LoadVectorString(chara.taunt_sounds, json["taunt"]);

	//Handles sounds for win
	if(json.HasMember("win") && json["win"].IsArray())
		ThemeManager::LoadVectorString(chara.win_sounds, json["win"]);

	//Handles character icon
	if(json.HasMember("character_icon") && json["character_icon"].IsString())
		chara.icon_sprite_path = json["character_icon"].GetString();
	else
		chara.icon_sprite_path = ThemeManager::GetDefaultPath(DefaultItemId::CHARACTER_ICON);

	//Handles character main sprite
	if(json.HasMember("character") && json["character"].IsString())
		chara.main_sprite_path = json["character"].GetString();
	else
		chara.main_sprite_path = ThemeManager::GetDefaultPath(DefaultItemId::CHARACTER_SPRITE);

	//Handles character's game backgrounds
	if(json.HasMember("game_background") && json["game_background"].IsArray())
	{
		ThemeManager::LoadVectorString(chara.game_backgrounds, json["game_background"]);
	}
	if(chara.game_backgrounds.empty())
		chara.game_backgrounds.push_back(ThemeManager::GetDefaultPath(DefaultItemId::CHARACTER_GAME_BACKGROUND));
}

void ThemeManager::LoadSharedSounds(std::vector<SharedSounds>& to_be_filled, std::size_t max_size, const char* to_parse, const rapidjson::Document& json)
{
	to_be_filled.reserve(max_size);
	SharedSounds empty_vector = std::make_shared<std::vector<std::string> >();
	to_be_filled.push_back(SharedSounds(empty_vector));//chain "0"
	to_be_filled.push_back(SharedSounds(empty_vector));//chain "1"

	if(json.HasMember(to_parse) && json[to_parse].IsObject())
	{
		SharedSounds current { empty_vector };
		for(std::size_t i { 2U }; i < max_size; ++i)
		{
			//Searchs for a new array of sounds!
			const char* index = std::to_string(i).c_str();
			if(json[to_parse].HasMember(index) && json[to_parse][index].IsArray())
			{
				const auto& array_sounds = json[to_parse][index];
				current = std::make_shared<std::vector<std::string> >(array_sounds.Size());
				ThemeManager::LoadVectorString(*current, array_sounds);
			}
			//Adds the current vector to the sounds.
			to_be_filled.push_back(SharedSounds(current));
		}
	}
	else
	{
		for(std::size_t i { 2U }; i < max_size; ++i)
			to_be_filled.push_back(SharedSounds(empty_vector));
	}
}

void ThemeManager::LoadVectorString(std::vector<std::string>& to_be_filled, const NodeValue& parsed)
{
	to_be_filled.reserve(parsed.Size());
	for(rapidjson::SizeType j = 0U, end_j = parsed.Size(); j < end_j; ++j)
	{
		if(parsed[j].IsString())
			to_be_filled.push_back(parsed[j].GetString());
	}
}