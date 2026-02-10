#include "PauseScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
USING_NS_CC;

Scene* PauseMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    this->setName("Pause Scene");

    auto listenerKeyboard = EventListenerKeyboard::create();
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(PauseMenu::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    string resumeString = "ادامه";
    string mainMenuString = "منوی اصلی";
    if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    {
        resumeString = "ﻪﻣﺍﺩﺍ";
        mainMenuString = "ﯽﻠﺻﺍ ىﻮﻨﻣ";
    }
    Label* resumeLabel = Label::createWithSystemFont( resumeString,
                                                      "fonts/BNAZANIN.TTF", 50 );
    //ageStringLabel->setPosition( mVisibleSize.width/2 + 120, mVisibleSize.height/2 + 140);
    resumeLabel->setColor(Color3B::GRAY);
    auto resumeItem =
            MenuItemLabel::create(resumeLabel,
                                  CC_CALLBACK_1(PauseMenu::Resume, this));

    Label* mainMenuLabel = Label::createWithSystemFont( mainMenuString,
                                                        "fonts/BNAZANIN.TTF", 50 );
    //ageStringLabel->setPosition( mVisibleSize.width/2 + 120, mVisibleSize.height/2 + 140);
    mainMenuLabel->setColor(Color3B::GRAY);
    auto mainMenuItem =
            MenuItemLabel::create( mainMenuLabel,
                                  CC_CALLBACK_1(PauseMenu::GoToMainMenuScene, this));
    auto menu = Menu::create(resumeItem, mainMenuItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 16);
    this->addChild(menu);

    return true;
}

void PauseMenu::Resume(cocos2d::Ref *pSender)
{
    Director::getInstance()->popScene();
}

void PauseMenu::GoToMainMenuScene(cocos2d::Ref *pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}

void PauseMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        CCLOG("Unause");
        //getEventDispatcher()->removeEventListener(mListenerKeyboard);
        Resume(this);
    }
}

