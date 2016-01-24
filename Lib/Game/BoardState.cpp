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
    return ( ERR_FAILURE );
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
