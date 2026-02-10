#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "BT_Number.h"
#include "BT_Counter.h"
#include "GameManager.h"
USING_NS_CC;

enum GameState
{
    GS_Initializing = 0,
    GS_ShowingTimer = 1,
    GS_ShowingLevel = 2,
    GS_ShowingAge   = 3,
    GS_WaitingForSelection = 4,
    GS_GoingToNextLevel = 5
};

class GameScreen : public cocos2d::LayerColor
{

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    // implement the "static create()" method manually
    CREATE_FUNC(GameScreen);

    void GoToPauseScene(Ref *pSender);
    void GoToMainMenuScene(Ref *pSender);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);


    void update(float dt);

    // Attributes
    Sprite * mBackground;

private:
    //bool mIsAtStartup;
    void Share(Ref *pSender);
    Menu* mCornerMenu;
    Menu* mCenterMenu;
    Menu* mShareMenu;
    Size mVisibleSize;
    Vec2 mOrigin;
    GameState mGameState;
    BT_Counter* mDownTimer;
    GameManager mGameManager;
    long long mShowStartTime;
    long mShowDuration;
    int mPlayerAge;
    EventListenerKeyboard* mListenerKeyboard;
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    float mWaitStartTime;
    const float mWaitBeforeNextLevel = .5;
    Node* mAgeNode;
};

#endif // __HELLOWORLD_SCENE_H__
