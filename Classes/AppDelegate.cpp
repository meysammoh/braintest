#include "AppDelegate.h"
#include "MainMenuScene.h"

//USING_NS_CC;


TagResource AppDelegate::smallResource  =  { Size(512, 384),   "small" };
TagResource AppDelegate::mediumResource =  { Size(1024, 768),  "medium"   };
TagResource AppDelegate::largeResource  =  { Size(2048, 1536), "large" };
Size AppDelegate::designResolutionSize = Size(1024, 768);

AppDelegate::AppDelegate() {

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
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionFixedHeight);
    Size frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium resource size, select large resource.
    if (frameSize.height > mediumResource.size.height)
    {
        searchPath.push_back(largeResource.directory);
        director->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
        CCLOG("large design");
    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        director->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);
        CCLOG("medium design");
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
    else
    {
        searchPath.push_back(smallResource.directory);
        director->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
        CCLOG("small design");
    }
    FileUtils::getInstance()->setSearchPaths(searchPath);


    // create a scene. it's an autorelease object
    auto scene = MainMenu::createScene();
    scene->setName("Main menu");

    // run
    director->runWithScene(scene);

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
