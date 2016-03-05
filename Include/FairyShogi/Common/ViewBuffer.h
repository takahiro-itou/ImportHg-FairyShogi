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
**      An Interface of ViewBuffer class.
**
**      @file       Common/ViewBuffer.h
**/

#if !defined( FAIRYSHOGI_COMMON_INCLUDED_VIEW_BUFFER_H )
#    define   FAIRYSHOGI_COMMON_INCLUDED_VIEW_BUFFER_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    "DefaultShogiPieces.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ViewBuffer  class.
//
/**
**    ゲームの局面を表示するためのバッファ構造体。
**/

struct  ViewBuffer
{
    /**   プレーヤの人数。  **/
    PlayerIndex     numPlayers;

    /**   盤面の行数。      **/
    PosRow          numRows;

    /**   盤面の列数。      **/
    PosCol          numCols;

    /**
    **    持ち駒の種類。
    **
    **    各プレーヤー毎に異なっていてもよい。
    **/
    PieceIndex      numHandTypes[FSSYSLIMIT::MAX_NUM_PLAYERS];

    /**   盤上の状態。      **/
    PieceIndex      piBoard[FSSYSLIMIT::MAX_FIELD_SIZE];

    /**   持ち駒の数。      **/
    THandCount      nHands [FSSYSLIMIT::MAX_HAND_TYPES];
};

}   //  End of namespace  Common
FAIRYSHOGI_NAMESPACE_END

#endif
