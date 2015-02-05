#include "sound_manager.h"
#include <cocos2d\cocos\audio\include\SimpleAudioEngine.h>

void SoundManager::Play(std::string to_play)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(to_play.c_str());
}

void SoundManager::PlayBackground(std::string to_play)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(to_play.c_str());
}

void SoundManager::Preload(std::string to_preload)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(to_preload.c_str());
}