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
**      An Implementation of Animation class.
**
**      @file       Win32/Animation.cpp
**/

#include    "FairyShogi/Win32/Animation.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    Animation  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

Animation::Animation()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

Animation::~Animation()
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
//    アニメーションの壱ステップを描画する。
//

ErrCode
Animation::drawAnimation(
        Interface::PixelMatrix  &imgDest)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    アニメーションを行うためのループを実行する。
//

ErrCode
Animation::enterAnimationLoop()
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    アニメーションを次のステップに進める。
//

Boolean
Animation::stepAnimation()
{
    return ( BOOL_FALSE );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    アニメーションの状態を取得する。
//

Boolean
Animation::getAnimationFlag()  const
{
    return ( BOOL_FALSE );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
