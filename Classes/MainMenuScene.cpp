#include "MainMenuScene.h"
#include "GameScene.h"
#include "AboutScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// include JniHelper.h
#include "jni/JniHelper.h"
#endif
USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    //setColor(Color3B(255, 255, 255));

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->setName("Main Menu Scene");

    /////////////////////////////
    // 3. add your codes below...

    mListenerKeyboard = EventListenerKeyboard::create();
    mListenerKeyboard->onKeyReleased = CC_CALLBACK_2(MainMenu::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mListenerKeyboard, this);


    auto playItem =
            MenuItemImage::create("MainMenuScreen/Play_Button.png",
                                  "MainMenuScreen/Play_Button(Click).png",
                                  CC_CALLBACK_1(MainMenu::GoToGameScene, this));
    auto contactItem =
            MenuItemImage::create("MainMenuScreen/Contact_Us.png",
                                  "MainMenuScreen/Contact_Us(Click).png",
                                  CC_CALLBACK_1(MainMenu::GoToAboutScene, this));


    // create menu, it's an autorelease object
    auto menu = Menu::create(playItem, contactItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu);

    return true;
}

void MainMenu::GoToGameScene(Ref *pSender)
{
    auto scene = GameScreen::createScene();
    scene->setName("Game Scene");
    //getEventDispatcher()->removeEventListener(mListenerKeyboard);
    Director::getInstance()->replaceScene(scene);
}

void MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        CCLOG("Exit game ...");
        CCDirector::Director::getInstance()->end();
    }
}

void MainMenu::GoToAboutScene(Ref *pSender)
{
    auto scene = AboutScene::createScene();
    scene->setName("About Scene");
    //getEventDispatcher()->removeEventListener(mListenerKeyboard);
    Director::getInstance()->replaceScene(scene);
}


