#include "app_delegate.h"
#include "scene_manager.h"
#include "theme_manager.h"

USING_NS_CC;

AppDelegate::AppDelegate() : gamepad_manager(nullptr) {

}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithFullScreen("Custom Puzzle League");
		//glview = GLViewImpl::createWithRect("Endless", Rect(0, 0, 1920, 1080), 1.f);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);//intern

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1. / 60.);

	//Creates instances
	gamepad_manager =  std::make_unique<GamepadManager>();
	SceneManager::Init();
	ThemeManager::Init();

	// Start first scene
	SceneManager::Instance().StartInitialScene();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
