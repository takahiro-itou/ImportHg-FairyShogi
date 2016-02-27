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
**      An Implementation of GraphicalInterface class.
**
**      @file       Interface/GraphicalInterface.cpp
**/

#include    "FairyShogi/Interface/GraphicalInterface.h"

#include    "FairyShogi/Common/ActionView.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    ConsoleInterface  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

GraphicalInterface::GraphicalInterface()
    : Super()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

GraphicalInterface::~GraphicalInterface()
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

//----------------------------------------------------------------
//    指定したマウス入力を、指し手データに変換する。
//

ErrCode
GraphicalInterface::setupMoveActionFromMouse(
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        PromoteList  *      vProms,
        ActionView   *      ptrAct)  const
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    指定したマウス入力を、指し手データに変換する。
//

ErrCode
GraphicalInterface::setupPutActionFromMouse(
        const  PosCol       xPutCol,
        const  PosRow       yPutRow,
        const  PieceIndex   pHand,
        PromoteList  *      vProms,
        ActionView   *      ptrAct)  const
{
    return ( ERR_FAILURE );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    入力した座標を内部処理用に変換する。
//

ErrCode
GraphicalInterface::convertCoordsFromMouse(
        const   ShowCoordFlags  flgShow,
        PosCol  *   const       ptrCol,
        PosRow  *   const       ptrRow)
{
    return ( ERR_FAILURE );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
