#ifndef _BT_NUMBER_H
#define _BT_NUMBER_H

#include "cocos2d.h"
#include "GameSetting.h"

using namespace cocos2d;

class BT_Number: public Node
{
    float mNumber;
    int mFontSize;
    std::string mFontFamily;
    Sprite* mBackground;
    bool mShowFloatingValue;
    bool mIsNumberVisible;
protected:
    bool mIsSelectable;
    Label* mNumberLabel;
public:
    BT_Number(float number, std::string fontFamily, int fontSize, bool showFloatingPoint = false);
    bool ContainsPoint(Point p);
    float GetNumber() const;
    void SetNumber(float number);
    bool IsSelectable() const;
    void SetIsSelectable(bool isSelectable);
    void SetShowFloatingValue(bool showFloatingValue);
    void SetNumberVisibility(bool isVisible);
    void SetNumberColor(Color3B color);
    float GetBoundingRadius();
};

#endif //_BT_NUMBER_H
