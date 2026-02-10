#ifndef _BT_COUNTER_H
#define _BT_COUNTER_H

#include "cocos2d.h"
#include "GameSetting.h"
#include "BT_Number.h"

using namespace cocos2d;

class BT_Counter: public BT_Number
{
    float mInterval;
    float mPace;
    bool mIsDownCounter;
    int mMinValue;
    int mMaxValue;
    bool mIsFinished;
protected:
    bool mIsSelectable;
public:
    BT_Counter(float minValue, float maxValue, float pace, float interval,
               bool isDownCounter, std::string fontFamily,
               int fontSize, bool showFloatingValue = false);
    float GetInterval() const;
    void SetInterval(float interval);
    bool IsFinished();
    //void update(float delta);
private:
    void UpdateTimer(float dt);
};

#endif //_BT_COUNTER_H
