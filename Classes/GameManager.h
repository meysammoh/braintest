#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <memory>
#include <mutex>

#include <cocos2d.h>
#include "BT_Number.h"
#include "BT_Counter.h"
#include <vector>
USING_NS_CC;
using namespace std;
enum LevelState
{
    LS_NotInitialized = 1,
    LS_Started = 2,
    LS_Success = 3,
    LS_Failure = 4
};

class GameManager
{
    int mLevel;
    Size mVisibleSize;
    Vec2 mOrigin;
    LevelState mLevelState;
    const int mMaxTurns = 10;
    int mTotalSuccess;
    int mTurn;
    int mClickCount;
    int mMemoryNumber;
    int mDummyNumber;
    //////////
    int mRows;
    int mCols;
    float mHeight;
    float mWidth;
    const float mCellWidth = 25;
    Vec2 mOffset;
    float mNumberRadius;
    BT_Number * mSelectedNumber;
    std::vector<BT_Number*>  mTouchableSprites;
    std::vector<int> mGeneratedNumbers;
    //////////
public:
    GameManager();
//    static GameManager& getInstance()
//    {
//        static GameManager instance;
//        return instance;
//    }
    void CreateNextLevel();
    void selectSpriteForTouch(Point touchLocation);
    void QuitShowing();
    LevelState GetLevelState();
    void ClearScene();
    bool IsGameFinished();
    int ComputeAge();
    void Initialize();
private:
//    GameManager();
//    GameManager( GameManager const& ) = delete;
//    void operator=( GameManager const& ) = delete;
    vector<Vec2> GenerateNonRecurringPoints(int numbers);
    Vec2 SelectAndUpdateWeights(int **matrix);
    void SetBoundingCellsZero(int **matrix, int row, int col, float radius);

    std::vector<int> GenerateRandomNumbers(int length, int min, int max);

};
#endif
