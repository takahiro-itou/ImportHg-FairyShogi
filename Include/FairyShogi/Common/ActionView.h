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
**      An Interface of ActionView class.
**
**      @file       Common/ActionView.h
**/

#if !defined( FAIRYSHOGI_COMMON_INCLUDED_ACTION_VIEW_H )
#    define   FAIRYSHOGI_COMMON_INCLUDED_ACTION_VIEW_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    "DefaultShogiPieces.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    指し手の合法判定のフラグに使う定数。
**/
enum  ActionLegalFlag
{
    /**
    **    合法手である。
    **/
    ALF_LEGAL_ACTION    = 0,

    /**
    **    駒の動かし方の間違い。
    **/
    ALF_ILLEGAL_MOVE    = 1,

    /**
    **    王手放置。自ら王手になる場合を含む。
    **/
    ALF_IGNORE_CHECK    = 2,

    /**
    **    二歩。
    **/
    ALF_DOUBLE_PAWNS    = 4,

    /**
    **    打ち歩詰めの反則。
    **/
    ALF_DROP_PAWN_END   = 8,

    /**
    **    全てのフラグの論理和。
    **/
    ALF_ALL_FLAGS       = 15
};

//========================================================================
//
//    ActionView  class.
//
/**
**    指し手の内部形式を表示用に変換した構造体。
**/

struct  ActionView
{
    PosCol      xPlayNewCol;    /**<  移動先の座標（横方向）。  **/
    PosRow      yPlayNewRow;    /**<  移動先の座標（縦方向）。  **/
    PosCol      xPlayOldCol;    /**<  移動元の座標（横方向）。  **/
    PosRow      yPlayOldRow;    /**<  移動元の座標（縦方向）。  **/

    PieceIndex  fpAfter;        /**<  駒が成った後の種類。      **/
    PieceIndex  fpMoved;        /**<  移動した自分の駒の種類。  **/

    PieceIndex  fpCatch;        /**<  捕獲した敵の駒の種類。    **/
    PieceIndex  hpiDrop;        /**<  打った持ち駒の種類。      **/

    ActionFlag  fLegals;        /**<  指し手の合法判定の結果。  **/
    PosCol      xDispNewCol;    /**<  移動先の座標（表示用）。  **/
    PosRow      yDispNewRow;    /**<  移動先の座標（表示用）。  **/
    PosCol      xDispOldCol;    /**<  移動元の座標（表示用）。  **/
    PosRow      yDispOldRow;    /**<  移動元の座標（表示用）。  **/
};

}   //  End of namespace  Common
FAIRYSHOGI_NAMESPACE_END

#endif
