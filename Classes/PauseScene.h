#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class PauseMenu : public cocos2d::LayerColor
{
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PauseMenu);

    void Resume(Ref *pSender);
    void GoToMainMenuScene(Ref *pSender);

};

#endif // __HELLOWORLD_SCENE_H__
