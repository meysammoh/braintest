#include "AboutScene.h"
#include "MainMenuScene.h"
using namespace std;
Scene* AboutScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AboutScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AboutScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    this->setName("About Scene");

    mListenerKeyboard = EventListenerKeyboard::create();
    mListenerKeyboard->onKeyReleased = CC_CALLBACK_2(AboutScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mListenerKeyboard, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    string nameString = "میثم محمدی";
    string emailString = "mayssam.moh@gmail.com";
    if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    {
        nameString = "ىﺪﻤﺤﻣ ﻢﺜﯿﻣ";

    }
    Label* nameLabel = Label::createWithSystemFont( nameString,
                                                      "fonts/BNAZANIN.TTF", 50 );
    Label* emailLabel = Label::createWithSystemFont( emailString,
                                                      "fonts/Marker Felt.TTF", 50 );
    nameLabel->setColor(Color3B::GRAY);
    emailLabel->setColor(Color3B::GRAY);

    nameLabel->setPosition(visibleSize.width/2+200, visibleSize.height/2+200);
    emailLabel->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(nameLabel);
    this->addChild(emailLabel);
    return true;
}

void AboutScene::GoToMainMenuScene(cocos2d::Ref *pSender)
{
    //getEventDispatcher()->removeEventListener(mListenerKeyboard);
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}

void AboutScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        CCLOG("Go to main menu ...");
        GoToMainMenuScene(this);
    }
}


