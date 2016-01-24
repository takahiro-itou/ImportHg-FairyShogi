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
**      An Implementation of BoardState class.
**
**      @file       Game/BoardState.cpp
**/

#include    "FairyShogi/Game/BoardState.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  GAME  {

//========================================================================
//
//    BoardState  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

BoardState::BoardState()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BoardState::~BoardState()
{
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    駒を移動する指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodeMoveAction(
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        const  PieceIndex   flgProm)  const
{
    (void)(xOldCol);
    (void)(yOldRow);
    (void)(xNewCol);
    (void)(yNewRow);
    (void)(flgProm);
    return ( ActionData() );
}

//----------------------------------------------------------------
//    持ち駒を打つ指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodePutAction(
        const  PosCol       xPutCol,
        const  PosRow       yPosRow,
        const  PieceIndex   pHand)  const
{
    (void)(xPutCol);
    (void)(yPosRow);
    (void)(pHand);
    return ( ActionData() );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を進める。
//

ErrCode
BoardState::playForward(
        const  ActionData   &actFwd)
{
    (void)(actFwd);
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
BoardState::resetGameBoard()
{
    return ( resetGameBoard(&(this->m_icState)) );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
BoardState::resetGameBoard(
        InternState  *  pCurStat)
{
    for ( int yr = 0; yr < POS_NUM_ROWS; ++ yr ) {
        for ( int xc = 0; xc < POS_NUM_COLS; ++ xc ) {
            pCurStat->m_bsField[yr][xc] = FIELD_EMPTY_SQUARE;
        }
    }

    pCurStat->m_bsField[0][0]   = FIELD_WHITE_ROOK;
    pCurStat->m_bsField[0][1]   = FIELD_WHITE_BISHOP;
    pCurStat->m_bsField[0][2]   = FIELD_WHITE_SILVER;
    pCurStat->m_bsField[0][3]   = FIELD_WHITE_GOLD;
    pCurStat->m_bsField[0][4]   = FIELD_WHITE_KING;
    pCurStat->m_bsField[1][4]   = FIELD_WHITE_PAWN;

    pCurStat->m_bsField[3][0]   = FIELD_BLACK_PAWN;
    pCurStat->m_bsField[4][0]   = FIELD_BLACK_KING;
    pCurStat->m_bsField[4][1]   = FIELD_BLACK_GOLD;
    pCurStat->m_bsField[4][2]   = FIELD_BLACK_SILVER;
    pCurStat->m_bsField[4][3]   = FIELD_BLACK_BISHOP;
    pCurStat->m_bsField[4][4]   = FIELD_BLACK_ROOK;

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    現在の盤面を取得して、表示用バッファにコピーする。
//

ErrCode
BoardState::copyToViewBuffer(
        INTERFACE::ViewBuffer  &bufView)  const
{
    (void)(bufView);
    return ( ERR_FAILURE );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  GAME
FAIRYSHOGI_NAMESPACE_END
