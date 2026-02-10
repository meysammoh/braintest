#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_
#define CC_SPRITE_DEBUG_DRAW 1
#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using namespace std;
struct TagResource
{
    Size size;
    char directory[100];
};

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

    static TagResource smallResource;
    static TagResource mediumResource;
    static TagResource largeResource;
    static CCSize designResolutionSize;

    vector<string> searchPath;
};

#endif // _APP_DELEGATE_H_

