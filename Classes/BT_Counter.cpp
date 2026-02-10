#include "BT_Counter.h"
#include "SimpleAudioEngine.h"

BT_Counter::BT_Counter(float minValue, float maxValue, float pace, float interval,
                       bool isDownCounter, std::string fontFamily,
                       int fontSize, bool showFloatingValue) : BT_Number( (isDownCounter ? maxValue :minValue),fontFamily, fontSize, showFloatingValue )
{

    mIsSelectable = false;
    mPace = pace;
    mInterval = interval;
    mMinValue = minValue;
    mMaxValue = maxValue;
    mIsDownCounter = isDownCounter;
    mIsFinished = false;
    this->schedule( schedule_selector( BT_Counter::UpdateTimer) , mInterval );

    //this->scheduleUpdate();
}

float BT_Counter::GetInterval() const
{
    return mInterval;
}

void BT_Counter::SetInterval(float interval)
{
    mInterval = interval;
}

bool BT_Counter::IsFinished()
{
    return mIsFinished;
}

void BT_Counter::UpdateTimer(float dt)
{
    if(mIsDownCounter)
    {
        if(GetNumber() - mPace >= mMinValue)
        {
            SetNumber(GetNumber() - mPace);

        }
        else
        {
            mIsFinished = true;
        }
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("SoundEffects/beep-07.mp3");
    }
    else
    {
        if(GetNumber() + mPace <= mMaxValue)
        {
            SetNumber(GetNumber() + mPace);
        }
        else
        {
            mIsFinished = true;
        }
    }
    if(mIsFinished)
    {
        this->unschedule( schedule_selector(BT_Counter::UpdateTimer) );
    }
}
//void BT_Counter::update(float delta)
//{


//}
