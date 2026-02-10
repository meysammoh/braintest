#include "BT_Number.h"
#include "utils.h"

float BT_Number::GetNumber() const
{
    return mNumber;
}

void BT_Number::SetNumber(float number)
{
    mNumber = number;
    mNumberLabel->setString(
                to_string_with_precision(mNumber , (mShowFloatingValue ? 2 : 0) )
                );
}
BT_Number::BT_Number(float number, std::string fontFamily, int fontSize, bool showFloatingPoint)
{
    mIsNumberVisible = true;
    mIsSelectable = true;
    mNumber = number;
    mFontFamily = fontFamily;
    mFontSize = fontSize;

    mBackground = Sprite::create("GameScreen/circle_black.png");

    mBackground->setScale(.5);
    this->addChild(mBackground);
    mShowFloatingValue = showFloatingPoint;
    mNumberLabel = Label::createWithSystemFont(
                to_string_with_precision(mNumber , (mShowFloatingValue ? 2 : 0) ),
                mFontFamily, mFontSize);
    mNumberLabel->setColor(Color3B::ORANGE);
    this->addChild(mNumberLabel);

}

bool BT_Number::ContainsPoint(Point point)
{
    bool result = false;
    //(x - center_x)^2 + (y - center_y)^2 < radius^2
    float radius = mBackground->getBoundingBox().size.width / 2;
    return ((point.x - getPosition().x) * (point.x - getPosition().x) +
            (point.y - getPosition().y) * (point.y - getPosition().y)) < (radius * radius);
}

bool BT_Number::IsSelectable() const
{
    return mIsSelectable;
}
void BT_Number::SetIsSelectable(bool isSelectable)
{
    mIsSelectable = isSelectable;
}

void BT_Number::SetShowFloatingValue(bool showFloatingValue)
{
    mShowFloatingValue = showFloatingValue;
}

void BT_Number::SetNumberVisibility(bool isVisible)
{
    mIsNumberVisible = isVisible;
    if(!mIsNumberVisible)
    {
        mNumberLabel->setString("");
    }
    else
    {
        SetNumber(mNumber);
    }
}

void BT_Number::SetNumberColor(Color3B color)
{
    mNumberLabel->setColor(color);
}

float BT_Number::GetBoundingRadius()
{
    return mBackground->getBoundingBox().size.width / 2;
}
