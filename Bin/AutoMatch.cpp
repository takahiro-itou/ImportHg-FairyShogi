//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      ---  Fairy Shogi Game  ---                      **
**                                                                      **
**                                                                      **
**          Copyright (C), 2015-2016, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      思考エンジン自動対局。
**
**      @file       Bin/AutoMatch.cpp
**/

#include    "FairyShogi/Interface/GameController.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/MersenneTwister.h"

#include    <cstdlib>
#include    <iostream>
#include    <memory.h>

using   namespace   FAIRYSHOGI_NAMESPACE;

typedef     Interface::GameController       GameController;

typedef     Common::MersenneTwister         RandomGenerator;
typedef     RandomGenerator::TResultInt     RandResult;

static  CONSTEXPR_VAR   RandResult
RANDOM_MAX_VALUE    =  RandomGenerator::MaxValue<28>::VALUE;

enum  {
    MAX_TURN    = 1024
};

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    勝利数の先手後手による内訳を管理する構造体。
**/
struct  TWinCountDetail
{
    int     wonBlack;       /**<  先手番での勝利。  **/
    int     wonWhite;       /**<  後手番での勝利。  **/
    int     wonTotal;       /**<  先手後手の合計。  **/
};

//----------------------------------------------------------------
/**
**    勝利数の勝敗条件による内訳を管理する構造体。
**/

struct  TWinGamesDetail
{
    /**   勝利条件を問わない合計。  **/
    TWinCountDetail     numTotalWons;

    /**   チェックメイトでの勝利。  **/
    TWinCountDetail     numCheckMate;

    /**   ステイルメイトでの勝利。  **/
    TWinCountDetail     numStaleMate;

    /**   相手の投了による勝利。    **/
    TWinCountDetail     numOppResign;

    /**   相手の反則による勝利。    **/
    TWinCountDetail     numViolation;
};

//----------------------------------------------------------------
/**
**    自動対局による結果を管理する構造体。
**/
struct  MatchResult
{
    int     numGame;
    int     numDraw;
    TWinGamesDetail     wgdPlayer1;
    TWinGamesDetail     wgdPlayer2;
};

//========================================================================
//
//    Functions.
//

//----------------------------------------------------------------
/**   対局結果を集計用の変数に加算する。
**
**  @note   先手番で勝利した場合。
**  @param [in,out] pCount
**/

ErrCode
incrementBlackWinCount(
        TWinCountDetail  *  pCount)
{
    ++  (pCount->wonBlack);
    ++  (pCount->wonTotal);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   対局結果を集計用の変数に加算する。
**
**  @note   後手番で勝利した場合。
**  @param [in,out] pCount
**/

ErrCode
incrementWhiteWinCount(
        TWinCountDetail  *  pCount)
{
    ++  (pCount->wonWhite);
    ++  (pCount->wonTotal);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   勝率を計算する。
**
**  @param [in] numWon1
**  @param [in] numWon2
**/

ErrCode
computeWinPercent(
        const  int  numWon1,
        const  int  numWon2,
        double  *   pwPoint,
        double  *   pwMin95,
        double  *   pwMax95,
        double  *   pwMin99,
        double  *   pwMax99)
{
    const  int  numGame = (numWon1 + numWon2);

    double  chi;
    int     nMin99  = -1,   nMax99  = -1;
    int     nMin95  = -1,   nMax95  = -1;

    for ( int i = 1; i < numGame; ++ i ) {
        const  int  expWon1 = i;
        const  int  expWon2 = (numGame - i);
        chi = ((numWon1 - expWon1) * (numWon1 - expWon1)) / expWon1
                + ((numWon2 - expWon2) * (numWon2 - expWon2)) / expWon2;

        if ( chi < 3.841 ) {
            if ( nMin95 < 0 ) {
                nMin95  = expWon1;
            } else {
                nMax95  = expWon1;
            }
        }
        if ( chi < 6.635 ) {
            if ( nMin99 < 0 ) {
                nMin99  = expWon1;
            } else {
                nMax99  = expWon1;
            }
        } else if ( nMax99 >= 0 ) {
            break;
        }
    }

    if ( nMin95 < 0 ) { nMin95 = 0; }
    if ( nMin99 < 0 ) { nMin99 = 0; }
    if ( nMax95 < 0 ) { nMax95 = numGame; }
    if ( nMax99 < 0 ) { nMax99 = numGame; }

    (* pwPoint) = (numWon1 * 100.0 / numGame);
    (* pwMin95) = (nMin95  * 100.0 / numGame);
    (* pwMax95) = (nMax95  * 100.0 / numGame);
    (* pwMin99) = (nMin99  * 100.0 / numGame);
    (* pwMax99) = (nMax99  * 100.0 / numGame);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   対局結果を集計用の変数に加算する。
**
**  @note   プレーヤー１が先手、プレーヤー２が後手の場合。
**  @param [in]     retVal
**  @param [in,out] pMatch
**/

ErrCode
countMatchResult(
        const  GameResultVals   retVal,
        MatchResult  *          pMatch,
        TWinGamesDetail  *      pBlack,
        TWinGamesDetail  *      pWhite)
{
    if ( retVal & Common::GAME_BLACK_WON ) {
        incrementBlackWinCount( &(pBlack->numTotalWons) );
    } else if ( retVal & Common::GAME_WHITE_WON ) {
        incrementWhiteWinCount( &(pWhite->numTotalWons) );
    } else {
        ++  (pMatch->numDraw);
    }

    if ( retVal == Common::GAME_BLACK_WON_CHECKMATE ) {
        incrementBlackWinCount( &(pBlack->numCheckMate) );
    }
    if ( retVal == Common::GAME_BLACK_WON_STALEMATE ) {
        incrementBlackWinCount( &(pBlack->numStaleMate) );
    }
    if ( retVal == Common::GAME_BLACK_WON_W_RESIGN ) {
        incrementBlackWinCount( &(pBlack->numOppResign) );
    }
    if ( retVal == Common::GAME_BLACK_WON_W_VIOLATE ) {
        incrementBlackWinCount( &(pBlack->numViolation) );
    }

    if ( retVal == Common::GAME_WHITE_WON_CHECKMATE ) {
        incrementWhiteWinCount( &(pWhite->numCheckMate) );
    }
    if ( retVal == Common::GAME_WHITE_WON_STALEMATE ) {
        incrementWhiteWinCount( &(pWhite->numStaleMate) );
    }
    if ( retVal == Common::GAME_WHITE_WON_B_RESIGN ) {
        incrementWhiteWinCount( &(pWhite->numOppResign) );
    }
    if ( retVal == Common::GAME_WHITE_WON_B_VIOLATE ) {
        incrementWhiteWinCount( &(pWhite->numViolation) );
    }

    return ( ERR_SUCCESS );
}


//----------------------------------------------------------------
/**   対局結果を集計用の変数に加算する。
**
**  @note   プレーヤー１が先手、プレーヤー２が後手の場合。
**  @param [in]     retVal
**  @param [in,out] pMatch
**/

ErrCode
countMatchResultBlackWhite(
        const  GameResultVals   retVal,
        MatchResult  *          pMatch)
{
    return ( countMatchResult(
                     retVal,  pMatch,
                     &(pMatch->wgdPlayer1), &(pMatch->wgdPlayer2)) );
}

//----------------------------------------------------------------
/**   対局結果を集計用の変数に加算する。
**
**  @note   プレーヤー１が先手、プレーヤー２が後手の場合。
**  @param [in]     retVal
**  @param [in,out] pMatch
**/

ErrCode
countMatchResultWhiteBlack(
        const  GameResultVals   retVal,
        MatchResult  *          pMatch)
{
    return ( countMatchResult(
                     retVal,  pMatch,
                     &(pMatch->wgdPlayer2), &(pMatch->wgdPlayer1)) );
}

//----------------------------------------------------------------
/**   自動対局の集計結果を表示する。
**
**/

std::ostream  &
displayMatchResults(
        const  MatchResult  &amRets,
        std::ostream        &outStr)
{
    outStr  <<    "Total Games     = "  <<  (amRets.numGame)
            <<  "\nDraw Gamme      = "  <<  (amRets.numDraw)
            <<  "\nPlayer 1 Wons   = "
            <<  (amRets.wgdPlayer1.numTotalWons.wonTotal)
            <<  "\n     at Black   = "
            <<  (amRets.wgdPlayer1.numTotalWons.wonBlack)
            <<  "\n     at White   = "
            <<  (amRets.wgdPlayer1.numTotalWons.wonWhite)
            <<  "\nPlayer 2 Wons   = "
            <<  (amRets.wgdPlayer2.numTotalWons.wonTotal)
            <<  "\n     at Black   = "
            <<  (amRets.wgdPlayer2.numTotalWons.wonBlack)
            <<  "\n     at White   = "
            <<  (amRets.wgdPlayer2.numTotalWons.wonWhite)
            <<  std::endl;

    const  int  numWon1 = (amRets.wgdPlayer1.numTotalWons.wonTotal);
    const  int  numWon2 = (amRets.wgdPlayer2.numTotalWons.wonTotal);

    //  プレーヤー１の勝率を計算する。  //
    double  dwpPoint;
    double  dwpMin95,  dwpMax95;
    double  dwpMin99,  dwpMax99;
    computeWinPercent(
            numWon1,    numWon2,
            &dwpPoint,  &dwpMin95, &dwpMax95,  &dwpMin99, &dwpMax99);
    outStr  <<  "Player 1 Win Percent:\n"
            <<  "(POINT)     : "    <<  (dwpPoint)
            <<  '%'     <<  std::endl
            <<  "(95% CHI^2) : ("
            <<  (dwpMin95)  <<  " %, "  <<  (dwpMax95)
            <<  " %)"   <<  std::endl
            <<  "(99% CHI^2) : ("
            <<  (dwpMin99)  <<  " %, "  <<  (dwpMax99)
            <<  " %)"   <<  std::endl;

    //  プレーヤー２の勝率を計算する。  //
    computeWinPercent(
            numWon2,    numWon1,
            &dwpPoint,  &dwpMin95, &dwpMax95,  &dwpMin99, &dwpMax99);
    outStr  <<  "Player 2 Win Percent:\n"
            <<  "(POINT)     : "    <<  (dwpPoint)
            <<  '%'     <<  std::endl
            <<  "(95% CHI^2) : ("
            <<  (dwpMin95)  <<  " %, "  <<  (dwpMax95)
            <<  " %)"   <<  std::endl
            <<  "(99% CHI^2) : ("
            <<  (dwpMin99)  <<  " %, "  <<  (dwpMax99)
            <<  " %)"   <<  std::endl;

    return ( outStr );
}

//----------------------------------------------------------------
/**   次のダイスを設定する。
**
**  @param [in,out] objGame
**  @param [in,out] rndGen
**/

ErrCode
setNextDice(
        GameController   & objGame,
        RandomGenerator  & rndGen)
{
    const  RandResult   rv  =  (rndGen.getNext() & RANDOM_MAX_VALUE);

    if ( objGame.isCheckState(objGame.getCurrentPlayer()) ) {
        objGame.setConstraint(Common::DICE_ANY_MOVE);
        return ( ERR_SUCCESS );
    }

    const  int  rn
        =  (rv * Common::DICE_MAX_VALUE) / (RANDOM_MAX_VALUE + 1) + 1;
    objGame.setConstraint(rn);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
/**   対局を壱回行う。
**
**  @param [in,out] objGame
**  @param [in,out] rndGen
**  @return     対局結果を示す値を返す。
**/

GameResultVals
executeSingleMatch(
        GameController   & objGame,
        RandomGenerator  & rndGen)
{
    Common::ActionView  actData;

    for ( int i = 0; i < MAX_TURN; ++ i ) {
        setNextDice(objGame, rndGen);
        if ( objGame.computeBestAction(actData) != ERR_SUCCESS ) {
            break;
        }
        objGame.playForward(actData);
        objGame.setPlayerToNext();
    }

    objGame.testGameStateResult();
    return ( objGame.getGameResult() );
}

//----------------------------------------------------------------
/**   自動対局を指定した回数だけ繰り返し実行する。
**
**  @param [in] engName1
**  @param [in] engName2
**  @param [in] numGame
**  @param[out] outStr
**/

Boolean
executeAutoMatches(
        const  std::string  &engName1,
        const  std::string  &engName2,
        const  int          numGame,
        std::ostream        &outStr)
{
    MatchResult     amRes;
    ::memset( &amRes, 0, sizeof(amRes) );

    RandomGenerator     rndGen;
    GameController      objGame;
    GameResultVals      retVal  =  Common::GAME_RESULT_DRAW;

    //  通常の対局を繰り返し行う。  //
    for ( int i = 1 ; i <= numGame; ++ i ) {
        //--------------------------------------------------------------//
        //    プレーヤー１を先手、プレーヤー２を後手で対局する。        //
        //--------------------------------------------------------------//
        rndGen.setSeedValue(i);
        outStr  <<  "Game # "   <<  i
                <<  " (TOP) @ START.."  <<  std::endl;

        objGame.setComputerEngine(Common::PLAYER_BLACK,  engName1);
        objGame.setComputerEngine(Common::PLAYER_WHITE,  engName2);
        objGame.resetGame();
        retVal  =  executeSingleMatch(objGame, rndGen);
        outStr  <<  "Game # "   <<  i
                <<  " (TOP) @ END. RESULT = "   <<  retVal  <<  std::endl;
        countMatchResultBlackWhite(retVal,  &amRes);
        outStr  <<  std::endl;

        //--------------------------------------------------------------//
        //    プレーヤー１を後手、プレーヤー２を先手で対局する。        //
        //--------------------------------------------------------------//
        rndGen.setSeedValue(i);
        outStr  <<  "Game # "   <<  i
                <<  " (BOT) @ START.."  <<  std::endl;

        objGame.setComputerEngine(Common::PLAYER_BLACK,  engName2);
        objGame.setComputerEngine(Common::PLAYER_WHITE,  engName1);
        objGame.resetGame();
        retVal  =  executeSingleMatch(objGame, rndGen);
        outStr  <<  "Game # "   <<  i
                <<  " (BOT) @ END. RESULT = "   <<  retVal  <<  std::endl;
        countMatchResultWhiteBlack(retVal,  &amRes);
        outStr  <<  std::endl;
    }

    outStr  <<  "----------------------------------------\nRESULTS:\n";
    displayMatchResults(amRes, outStr)  <<  std::endl;

    return ( BOOL_TRUE );
}

//----------------------------------------------------------------
/**   アプリケーションのエントリポイント。
**
**/

int  main(int argc, char * argv[])
{
    if ( argc < 3 ) {
        return ( 1 );
    }

    executeAutoMatches(
            argv[1],  argv[2],  std::atoi(argv[3]),  std::cout);

    return ( 0 );
}
