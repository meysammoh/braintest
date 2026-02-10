#include "GameScene.h"
#include "PauseScene.h"
#include "BT_Number.h"
#include "GameSetting.h"
#include "GameManager.h"
#include "MainMenuScene.h"
#include "utils.h"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    //mIsAtStartup = true;
    mGameState = GS_Initializing;
    //SET MOUSE LISTENER
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScreen::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScreen::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //END MOUSE LISTENER
    mListenerKeyboard = EventListenerKeyboard::create();
    mListenerKeyboard->onKeyReleased = CC_CALLBACK_2(GameScreen::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mListenerKeyboard, this);

    scheduleUpdate();
    CCLOG("update registered");

    mVisibleSize = Director::getInstance()->getVisibleSize();
    mOrigin = Director::getInstance()->getVisibleOrigin();
    //log("in scene %s", this->getName().c_str());

    auto pauseItem =
            MenuItemImage::create("GameScreen/Pause_Button.png",
                                  "GameScreen/Pause_Button(Click).png",
                                  CC_CALLBACK_1(GameScreen::GoToPauseScene, this));
    pauseItem->setPosition(Point(pauseItem->getContentSize().width -
                                 (pauseItem->getContentSize().width / 4) + mOrigin.x,
                                 mVisibleSize.height - pauseItem->getContentSize().height +
                                 (pauseItem->getContentSize().width / 4) + mOrigin.y));
    //pauseItem->setScale(.7);
    mCornerMenu = Menu::create(pauseItem, NULL);
    mCornerMenu->setPosition(Point::ZERO);
    this->addChild(mCornerMenu);


    auto mainMenuItem =
            MenuItemImage::create("MainMenuScreen/Play_Button.png",
                                  "MainMenuScreen/Play_Button(Click).png",
                                  CC_CALLBACK_1(GameScreen::GoToMainMenuScene, this));
    mainMenuItem->setScale(.5);
    mainMenuItem->setPosition(Point(mVisibleSize.width/2, mVisibleSize.height/2 - 100));
    mCenterMenu = Menu::create( mainMenuItem, NULL);
    //mCenterMenu->alignItemsVerticallyWithPadding(mVisibleSize.height);
    mCenterMenu->setVisible(false);
    mCenterMenu->setPosition(Point::ZERO);
    this->addChild( mCenterMenu );


    mShowStartTime = time(NULL);
    mShowDuration = 1;
    mPlayerAge = 1;
    return true;
}

void GameScreen::GoToPauseScene(cocos2d::Ref *pSender)
{
    auto scene = PauseMenu::createScene();

    Director::getInstance()->pushScene(scene);
}
void GameScreen::onEnterTransitionDidFinish()
{

    if(mGameState == GS_Initializing)
    {


        //        BT_Counter* counter2 = new BT_Counter(0, 3, 1, 1, true, "fonts/BNAZANIN.TTF", 49);
        //        counter2->setPosition( 600, 500 );
        //        mMainScene->addChild( counter2 );

        //log("transition finished %s",cocos2d::Director::getInstance()->getRunningScene()->getName().c_str());
        //mIsAtStartup = false;
        //GameManager::getInstance().CreateNextLevel();


    }
}

void GameScreen::update(float dt)
{
    if(mGameState == GS_Initializing)
    {

        mDownTimer = new BT_Counter(1, 3, 1, .75, true, "fonts/BNAZANIN.TTF", 49);
        mDownTimer->setPosition( mVisibleSize.width/2, mVisibleSize.height/2 );
        this->addChild( mDownTimer );
        mGameState = GS_ShowingTimer;

    }
    else if(mGameState == GS_ShowingTimer)
    {

        if(mDownTimer->IsFinished())
        {
            this->removeChild(mDownTimer);
            mGameManager.CreateNextLevel();
            mGameState = GS_ShowingLevel;
            mShowStartTime = time( NULL );
        }
    }
    else if(mGameState == GS_ShowingLevel)
    {

        long long now = time(NULL);
        if( now - mShowStartTime > mShowDuration )
        {
            mGameManager.QuitShowing();
            mGameState = GS_WaitingForSelection;
        }
    }
    else if(mGameState == GS_WaitingForSelection)
    {
        if(mGameManager.GetLevelState() == LS_Success)
        {
            //log("good for you!");
            mGameState = GS_GoingToNextLevel;
            mWaitStartTime = 0;
            //            mGameState = GS_Initializing;
        }
        else if(mGameManager.GetLevelState() == LS_Failure)
        {
            //log("bad for you!");
            mGameState = GS_GoingToNextLevel;
            mWaitStartTime = 0;
            //            mGameState = GS_Initializing;
        }
    }
    else if( mGameState == GS_GoingToNextLevel )
    {
        if( mWaitStartTime > mWaitBeforeNextLevel )
        {
            mGameManager.ClearScene();

            if(!mGameManager.IsGameFinished())
            {
                if( mGameManager.GetLevelState() == LS_Success )
                {

                }
                else if( mGameManager.GetLevelState() == LS_Failure )
                {

                }
                mShowStartTime = time(NULL);
                mGameState = GS_Initializing;
            }
            else
            {
                mAgeNode = Node::create();
                mPlayerAge = mGameManager.ComputeAge();
                string ageString = "سن مغز شما";
                if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
                {
                    ageString = "ﺎﻤﺷ ﺰﻐﻣ ﻦﺳ";
                }

                Label* ageStringLabel = Label::createWithSystemFont(ageString, "fonts/BNAZANIN.TTF", 50 );
                ageStringLabel->setPosition( mVisibleSize.width/2 + 120, mVisibleSize.height/2 + 140);
                ageStringLabel->setColor(Color3B::GRAY);
                mAgeNode->addChild( ageStringLabel );

                Label* ageLabel = Label::createWithSystemFont(
                            to_string_with_precision(mPlayerAge, 0), "fonts/BNAZANIN.TTF", 60 );
                ageLabel->setPosition( mVisibleSize.width/2, mVisibleSize.height/2 + 70 );
                ageLabel->setColor(Color3B::BLUE);
                mAgeNode->addChild( ageLabel );
                mGameState = GS_ShowingAge;
                this->addChild(mAgeNode);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

                auto shareButton =
                        MenuItemImage::create("GameScreen/share_button.png",
                                              "GameScreen/share_button(clicked).png",
                                              CC_CALLBACK_1(GameScreen::Share, this));
                shareButton->setScale(.5);
                shareButton->setPosition(100,mVisibleSize.height - 100);
                mShareMenu = Menu::create(shareButton, NULL);
                mShareMenu->setPosition(Point::ZERO);
                this->addChild(mShareMenu);




#endif

            }
        }
        mWaitStartTime += dt;
    }
    else if(mGameState == GS_ShowingAge)
    {
        if(mCornerMenu->isVisible())
        {
            mCornerMenu->setVisible(false);
            mCenterMenu->setVisible(true);
        }

    }
}


bool GameScreen::onTouchBegan(Touch* touch, Event* event)
{
    if( mGameState == GS_WaitingForSelection )
    {
        Point touchLocation = convertTouchToNodeSpace(touch);
        //log("touch began at %f , %f", touchLocation.x, touchLocation.y);

        mGameManager.selectSpriteForTouch(touchLocation);
    }
    return true;
}

void GameScreen::onTouchMoved(Touch* touch, Event* event)
{
}

void GameScreen::onTouchEnded(Touch* touch, Event* event)
{
}

void GameScreen::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        CCLOG("Pause");
        //getEventDispatcher()->removeEventListener(mListenerKeyboard);
        GoToPauseScene(this);
    }
}
void GameScreen::GoToMainMenuScene(cocos2d::Ref *pSender)
{
    mShowStartTime = time(NULL);
    mShowDuration = 1;
    mPlayerAge = 1;
    mCornerMenu->setVisible(true);
    mCenterMenu->setVisible(false);
    mGameState = GS_Initializing;
    this->removeChild(mAgeNode);
    mGameManager.Initialize();
}

void GameScreen::Share(Ref *pSender)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLOG("Sharing ... ");
    JniMethodInfo t;
    const char* subject = "My Brain Age!";
    string ageString = ("My Brain's age is "+to_string_with_precision(mPlayerAge, 0)+"!");
    const char* msg = ageString.c_str();
    if (JniHelper::getStaticMethodInfo(t,
                                       "org/cocos2dx/cpp/AppActivity",
                                       "shareMessage",
                                       "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring tStringArg1 = t.env->NewStringUTF( subject );
        jstring tStringArg2 = t.env->NewStringUTF( msg );

        t.env->CallStaticVoidMethod(t.classID, t.methodID, tStringArg1, tStringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}




