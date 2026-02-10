#include "GameManager.h"
#include <algorithm>
#include <random>
#include "SimpleAudioEngine.h"
GameManager::GameManager()
{
    mVisibleSize = Director::getInstance()->getVisibleSize();
    mOrigin = Director::getInstance()->getVisibleOrigin();
    mLevelState = LS_NotInitialized;
    Initialize();
    BT_Number temp(0, "fonts/BNAZANIN.TTF", 49);
    mNumberRadius = temp.GetBoundingRadius();

    mWidth = mVisibleSize.width - mVisibleSize.width/3;
    mHeight = mVisibleSize.height - mVisibleSize.height/3;
    mRows = mHeight / mCellWidth;
    mCols = mWidth / mCellWidth;
    mOffset = Vec2((mVisibleSize.width - mWidth)/2,(mVisibleSize.height - mHeight)/2);

}

void GameManager::Initialize()
{
    mLevel = 3;
    mSelectedNumber = nullptr;
    mTurn = 0;
    mTotalSuccess = 0;
    mClickCount = 0;
    mMemoryNumber = 0;
    mDummyNumber = 0;
}

void GameManager::CreateNextLevel()
{
    Scene* mainScene = Director::getInstance()->getRunningScene();
    mTurn++;
    //    for (BT_Number* oldNumber : mTouchableSprites)
    //    {
    //        mainScene->removeChild(oldNumber);
    //    }
    //    mTouchableSprites.clear();

    mLevelState = LS_Started;
    int totalNumbers = mLevel;
    //vector<Vec2> cellIndices = GenerateNonRecurringPoints( totalNumbers );
    vector<Vec2> cellIndices = GenerateNonRecurringPoints(totalNumbers + mDummyNumber);
    //std::default_random_engine generator;
    //std::uniform_int_distribution<int> distribution(1,10);
    std::vector<int> numbersDist = GenerateRandomNumbers(totalNumbers,1,9);
    //TODO:Create dummy circles if mDummyNumber > 0
    for(int i = 0; i < totalNumbers; i++)
    {
        int genNum = 0;
        if( i < numbersDist.size() )
        {
            genNum = numbersDist[i];
        }
        vector<int>::iterator iter;
        for( iter = mGeneratedNumbers.begin();
             iter != mGeneratedNumbers.end(); iter ++)
        {
            //            log("num %d",*iter);
            if( *iter <= genNum )
            {
                //                log("breaked");
                break;
            }
        }
        mGeneratedNumbers.insert( iter, genNum);
        BT_Number* number = new BT_Number(genNum, "fonts/BNAZANIN.TTF", 49);
        //log("radius is %f", number->GetBoundingRadius());
        number->SetIsSelectable( false );
        mainScene->addChild(number);
        mTouchableSprites.push_back(number);
        //log("cell positioned at: %f %f" ,cellIndices[i].x, cellIndices[i].y );

        number->setPosition( cellIndices[i] );



    }
    for(int i = 0; i<mDummyNumber; i++)
    {
        BT_Number* number = new BT_Number(100, "fonts/BNAZANIN.TTF", 49);
        number->SetNumberVisibility(false);
        number->SetIsSelectable( false );
        mainScene->addChild(number);
        mTouchableSprites.push_back(number);
        //log("cell positioned at: %f %f" ,cellIndices[totalNumbers+i].x, cellIndices[totalNumbers+i].y );

        number->setPosition( cellIndices[totalNumbers+i] );

    }
}

void GameManager::selectSpriteForTouch(Point touchLocation)
{
    mSelectedNumber = nullptr;
    for (BT_Number* number : mTouchableSprites)
    {
        if (number->IsSelectable() && number->ContainsPoint(touchLocation))
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("SoundEffects/two_tone_nav.mp3");
            mSelectedNumber = number;
            //log("Selected a number with value %f!" , number->GetNumber());
            if( number->GetNumber() < 10)
            {
                number->SetNumberVisibility(true);
            }
            number->SetIsSelectable( false );
            int poppedNum = mGeneratedNumbers.front();
            mGeneratedNumbers.erase(mGeneratedNumbers.begin());
            //log( "popped num %d", poppedNum );
            if( poppedNum != number->GetNumber())
            {
                number->SetNumberColor(Color3B::RED);
                //log("you lose!");
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("SoundEffects/fail-buzzer-03.mp3");

                mLevelState = LS_Failure;
            }
            else if(mGeneratedNumbers.size() == 0)
            {
                //log("you win!");
                number->SetNumberColor(Color3B::GREEN);
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("SoundEffects/ping_ping.mp3");
                mLevelState = LS_Success;
            }
            else
            {
                number->SetNumberColor(Color3B::GREEN);
            }
            mClickCount++;

            if( mLevelState == LS_Success || mLevelState == LS_Failure )
            {
                mMemoryNumber += mClickCount;
                if(mLevelState == LS_Success)
                {
                    mTotalSuccess++;
                    mLevel++;
                }
                else
                {
                    if( mDummyNumber > 0 )
                    {
                        mDummyNumber--;
                    }
                    else
                    {
                        mLevel--;
                    }
                }

                if( mLevel < 3 )
                {
                    mLevel = 3;
                }
                else if(mLevel > 9)
                {
                    mLevel = 9;
                    mDummyNumber++;
                }
                mClickCount = 0;


            }

            auto rotateTo = RotateBy::create(0.3f, 360.0f);
            number->runAction(rotateTo);
            number->setCascadeOpacityEnabled(true);
            break;
        }
    }
    if(mSelectedNumber == nullptr)
    {
       // log("Nothing selected!");
    }
}

void GameManager::QuitShowing()
{
    for (BT_Number* number : mTouchableSprites)
    {
        number->SetNumberVisibility(false);
        number->SetIsSelectable( true );
    }
}

LevelState GameManager::GetLevelState()
{
    return mLevelState;
}

void GameManager::ClearScene()
{
    Scene* mainScene = Director::getInstance()->getRunningScene();
    for (BT_Number* number : mTouchableSprites)
    {
        mainScene->removeChild( number );
    }
    mGeneratedNumbers.clear();
    mTouchableSprites.clear();
    mSelectedNumber = nullptr;
}

bool GameManager::IsGameFinished()
{
    return mTurn >= mMaxTurns;
}

int GameManager::ComputeAge()
{
    int result = 0;
    if (mMemoryNumber >= 48) {
        result = 20;
    }
    if (mMemoryNumber < 48) {
        result = 69 - mMemoryNumber;
    }
    if (mMemoryNumber < 40) {
        result = 70 - mMemoryNumber;
    }
    if (mMemoryNumber < 30) {
        result = 80 - mMemoryNumber;
    }
    if (mMemoryNumber < 20) {
        result = 120;
    }
    if ((mTotalSuccess >= 8) || (result < 20)) {
        result = 20;
    }
    return result;
}

std::vector<int> GameManager::GenerateRandomNumbers(int length, int min, int max)
{
    std::vector<int> result;
    srand (time(NULL));
    int generatedNum = 0;

    int remaining = ( length > (max - min + 1) ? (max - min + 1) : length);
    //log("length %d min %d max %d" , length , min , max);
    while( remaining > 0 )
    {
        bool isRepeated = true;
        while( isRepeated || generatedNum < min)
        {
            generatedNum = rand() % (max + 1);
            isRepeated = std::find(result.begin(), result.end(), generatedNum) != result.end();
            //log("remains %d repeated: %d", remaining , generatedNum);
        }
        result.push_back( generatedNum );
        //log("generated: %d", generatedNum);
        remaining--;
    }
    return result;
}

vector<Vec2> GameManager::GenerateNonRecurringPoints(int numbers)
{

    int parts = 3;
    int ** matrix = new int* [mRows];
    //int vector [vectorSize];
    //int cumulativeVector[vectorSize];
    //int sum = 0;
    for( int i = 0; i < mRows; i++ )
    {
        matrix[i] = new int[mCols];
        for( int j = 0 ;j < mCols; j++ )
        {
            matrix[i][j] = 0;
            //vector[i*cols + j] = 0;
            int computedWeight = 0;
            if( i < mRows/parts || i >= mRows - mRows/parts)
            {
                computedWeight = 1;
            }
            else if ( j< mCols/parts || j >= mCols - mCols/parts)
            {
                computedWeight = 1;
            }
            else
            {
                computedWeight = 10;
            }
            //vector[i*cols + j] = computedWeight;
            //sum = sum + computedWeight;
            matrix[i][j] = computedWeight;

        }
    }
    srand(time(NULL));
    vector<Vec2> result;
    for(int i = 0; i< numbers;i++)
    {
        result.push_back(SelectAndUpdateWeights(matrix));
    }
    return result;

}

Vec2 GameManager::SelectAndUpdateWeights(int **matrix)
{
    Vec2 result;
    int sum = 0;
    int cdf [mRows][mCols];
    for(int i = 0; i<mRows; i ++)
    {
        for(int j = 0 ; j<mCols;j++)
        {
            sum += matrix[i][j];
            cdf[i][j] = sum;
        }
    }


    int rnum = rand()%sum + 1;
    //log("1111111111111 sum %d rand: %d",sum,rnum);
    int prevNum = 0;
    int i = 0;
    int j = 0 ;
    bool isb = false;
    for(i = 0; i<mRows; i ++)
    {
        for(j = 0; j<mCols;j++)
        {
            //log("##### rnum %d > prevnum %d && rnum %d <= cdf %d",rnum,prevNum,rnum,cdf[i][j]);
            if( rnum > prevNum && rnum <= cdf[i][j] )
            {
                isb=true;
                break;
            }
            prevNum = cdf[i][j] ;
        }
        if(isb)
            break;
    }
    if( i < mRows && j< mCols)
    {
        matrix[i][j] = 0;
        SetBoundingCellsZero(matrix, i, j, mNumberRadius);
        result = Vec2(j*mCellWidth + mOffset.x,i*mCellWidth + mOffset.y);
    }
    else
    {
        log("no selectable cell");
    }

    return result;
}

void GameManager::SetBoundingCellsZero(int **matrix, int row, int col, float radius)
{
    int dist = ceil( radius/mCellWidth );
    //log("dist is %d", dist);
    for(int i = row - dist; i<= row+dist; i++)
    {
        for(int j = col - dist; j<=col+dist; j++)
        {
            if(i > -1 && i < mRows &&
                    j>-1 && j<mCols)
            {
                matrix[i][j] = 0;
            }
        }
    }
}
