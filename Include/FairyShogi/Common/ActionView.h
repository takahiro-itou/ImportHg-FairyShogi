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

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ActionView  class.
//
/**
**    指し手の内部形式を表示用に変換した構造体。
**/

struct  ActionView
{
    PosCol      xNewCol;        /**<  移動先の座標（横方向）。  **/
    PosRow      yNewRow;        /**<  移動先の座標（縦方向）。  **/
    PosCol      xOldCol;        /**<  移動元の座標（横方向）。  **/
    PosRow      yOldRow;        /**<  移動元の座標（縦方向）。  **/

    PieceIndex  fpAfter;        /**<  駒が成った後の種類。      **/
    PieceIndex  fpMoved;        /**<  移動した自分の駒の種類。  **/

    PieceIndex  fpCatch;        /**<  捕獲した敵の駒の種類。    **/
    PieceIndex  putHand;        /**<  打った持ち駒の種類。      **/
};

}   //  End of namespace  Common
FAIRYSHOGI_NAMESPACE_END

#endif
