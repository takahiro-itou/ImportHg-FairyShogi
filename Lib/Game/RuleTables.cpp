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
**      An Implementation of RuleTables class.
**
**      @file       Game/RuleTables.cpp
**/

#include    "RuleTables.h"

#include    "FairyShogi/Game/BitSet.h"

#include    <memory.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Game  {

namespace  {

/**
**    方向を示す定数。
**/

enum  Direction
{
    NW = +6, N = -1, NE = -8,
    W  = +7,         E  = -7,
    SW = +8, S = +1, SE = -6
};

/**
**    座標データを番兵付きの座標に変換するためのテーブル。
**/

CONSTEXPR_VAR   int     g_tblConvPos[25] = {
    8,  9,  10, 11, 12,
    15, 16, 17, 18, 19,
    22, 23, 24, 25, 26,
    29, 30, 31, 32, 33,
    36, 37, 38, 39, 40
};

/**
**    番兵付きの座標から、元の座標に変換するためのテーブル。
**/

CONSTEXPR_VAR   int     g_tblInvPos[49] = {
    -1, -1, -1, -1, -1, -1, -1,
    -1,  0,  1,  2,  3,  4, -1,
    -1,  5,  6,  7,  8,  9, -1,
    -1, 10, 11, 12, 13, 14, -1,
    -1, 15, 16, 17, 18, 19, -1,
    -1, 20, 21, 22, 23, 24, -1,
    -1, -1, -1, -1, -1, -1, -1
};

/**
**    隣接移動テーブル。
**/

CONSTEXPR_VAR   int
g_tblWalkDir[BoardState::NUM_FIELD_PIECE_TYPES][9] = {
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Empty.

    { N , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Black Pawn.
    { SW, NW, N , SE, NE, 0 , 0 , 0 , 0 },      //  Black Silver.
    { W , NW, S , N , E , NE, 0 , 0 , 0 },      //  Black Gold.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Black Bishop.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Black Rook.
    { SW, W , NW, S , N , SE, E , NE, 0 },      //  Black King.
    { W , NW, S , N , E , NE, 0 , 0 , 0 },      //  Black Pr.Pawn.
    { W , NW, S , N , E , NE, 0 , 0 , 0 },      //  Black Pr.Silver.
    { W , S , N,  E , 0 , 0 , 0 , 0 , 0 },      //  Black Pr.Bishop.
    { SW, NW, SE, NE, 0 , 0 , 0 , 0 , 0 },      //  Black Pr.Rook.

    { S , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  White Pawn.
    { SW, NW, S , SE, NE, 0 , 0 , 0 , 0 },      //  White Silver.
    { SW, W , S , N , SE, E , 0 , 0 , 0 },      //  White Gold.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  White Bishop.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  White Rook.
    { SW, W , NW, S , N , SE, E , NE, 0 },      //  White King.
    { SW, W , S , N , SE, E , 0 , 0 , 0 },      //  White Pr.Pawn.
    { SW, W , S , N , SE, E , 0 , 0 , 0 },      //  White Pr.Silver.
    { W , S , N,  E , 0 , 0 , 0 , 0 , 0 },      //  White Pr.Bishop.
    { SW, NW, SE, NE, 0 , 0 , 0 , 0 , 0 }       //  White Pr.Rook.
};

/**
**      飛行移動テーブル。
**/

CONSTEXPR_VAR   int
g_tblJumpDir[BoardState::NUM_FIELD_PIECE_TYPES][9] = {
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Empty.

    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Black Pawn.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Black Silver.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Black Gold.
    { SW, NW, SE, NE, 0 , 0 , 0 , 0 , 0 },      //  Black Bishop.
    { W , S , N,  E , 0 , 0 , 0 , 0 , 0 },      //  Black Rook.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Black King.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Black Pr.Pawn.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  Black Pr.Silver.
    { SW, NW, SE, NE, 0 , 0 , 0 , 0 , 0 },      //  Black Pr.Bishop.
    { W , S , N,  E , 0 , 0 , 0 , 0 , 0 },      //  Black Pr.Rook.

    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  White Pawn.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  White Silver.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  White Gold.
    { SW, NW, SE, NE, 0 , 0 , 0 , 0 , 0 },      //  White Bishop.
    { W , S , N,  E , 0 , 0 , 0 , 0 , 0 },      //  White Rook.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  White King.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  White Pr.Pawn.
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },      //  White Pr.Silver.
    { SW, NW, SE, NE, 0 , 0 , 0 , 0 , 0 },      //  White Pr.Bishop.
    { W , S , N,  E , 0 , 0 , 0 , 0 , 0 }       //  White Pr.Rook.
};

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    RuleTables  class.
//

//========================================================================
//
//    Static Member Variables.
//

uint32_t    RuleTables::s_tblMoveTo[FIELD_SIZE][NUM_PIECE_TYPES];

uint32_t    RuleTables::s_tblMoveFrom[FIELD_SIZE][NUM_PIECE_TYPES];

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

RuleTables::RuleTables()
{
    setupRuleTables();
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

RuleTables::~RuleTables()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    ルールテーブルを構築する。
//

ErrCode
RuleTables::setupRuleTables()
{
    TDirsTable  tblWalk;
    TDirsTable  tblJump;
    TMoveTable  tblMove;
    TPinsTable  tblPins;

    ::memset( s_tblMoveFrom, 0, sizeof(s_tblMoveFrom) );

    for ( int i = 0; i < NUM_PIECE_TYPES; ++ i ) {
        for ( int j = 0; j < MAX_DIRECTIONS; ++ j ) {
            tblWalk[j]  = - g_tblWalkDir[i][j];
            tblJump[j]  = - g_tblJumpDir[i][j];
        }
        expandDirTable(
                tblWalk, tblJump, tblMove, tblPins);
        for ( int k = 0; k < FIELD_SIZE; ++ k ) {
            s_tblMoveFrom[k][i] = tblMove[k];
        }
    }

    return ( ERR_FAILURE );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    ルールテーブルを展開する。
//

ErrCode
RuleTables::expandDirTable(
        const  TDirsTable  &tblWalk,
        const  TDirsTable  &tblJump,
        TMoveTable         &tblMove,
        TPinsTable         &tblPins)
{
    for ( int posSrc = 0; posSrc < 25; ++ posSrc ) {
        BitSet  bstWork;

        const  int      tmpSrc  = g_tblConvPos[posSrc];
        const  int  *   ptrDir  = (nullptr);
        for ( ptrDir = tblWalk; (* ptrDir); ++ ptrDir ) {
            const  int  tmpTrg  = tmpSrc + (* ptrDir);
            const  int  posTrg  = g_tblInvPos[tmpTrg];
            if ( posTrg < 0 ) {
                continue;       //  盤外にはみ出した。  //
            }
            bstWork.setBitValue(posTrg);
        }

        for ( ptrDir = tblJump; (* ptrDir); ++ ptrDir ) {
            const  int  jmpDir  = (* ptrDir);
            int         tmpTrg  = tmpSrc + jmpDir;
            for ( ;; tmpTrg += jmpDir) {
                const  int  posTrg  = g_tblInvPos[tmpTrg];
                if ( posTrg < 0 ) {
                    break;      //  盤外にはみだした。  //
                }
                bstWork.setBitValue(posTrg);
            }
        }

        tblMove[posSrc] = bstWork.getValueBlock();
    }

    return ( ERR_SUCCESS );
}

}   //  End of namespace  Game
FAIRYSHOGI_NAMESPACE_END
