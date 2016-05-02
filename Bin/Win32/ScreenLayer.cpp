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
**      An Implementation of ScreenLayer class.
**
**      @file       Bin/Win32/ScreenLayer.cpp
**/

#include    "ScreenLayer.h"

#include    "FairyShogi/Common/HelperMacros.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    ScreenLayer  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ScreenLayer::ScreenLayer()
    : m_sVisible(LV_HIDDEN),
      m_cLeft  (0),
      m_cTop   (0),
      m_cWidth (0),
      m_cHeight(0)
{
}

//----------------------------------------------------------------
//    インスタンスを指定したサイズで初期化する
//  （コンストラクタ）。
//

ScreenLayer::ScreenLayer(
        const  WindowCoord  wcLeft,
        const  WindowCoord  wcTop,
        const  WindowCoord  wcWidth,
        const  WindowCoord  wcHeight)
    : m_sVisible(LV_HIDDEN),
      m_cLeft  (wcLeft),
      m_cTop   (wcTop),
      m_cWidth (wcWidth),
      m_cHeight(wcHeight)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ScreenLayer::~ScreenLayer()
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
//    イベントハンドラを呼び出す。
//

ScreenLayer::EventResult
ScreenLayer::dispatchLButtonUp(
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    return ( onLButtonUp(
                     fwKeys,
                     static_cast<WindowCoord>(xPos) - getLeft(),
                     static_cast<WindowCoord>(yPos) - getTop()
             ) );
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
//    ウィンドウ内に表示する時の高さを取得する。
//

ScreenLayer::WindowCoord
ScreenLayer::getHeight()  const
{
    return ( this->m_cHeight );
}

//----------------------------------------------------------------
//    ウィンドウ内に表示する時の高さを設定する。
//

ScreenLayer::WindowCoord
ScreenLayer::setHeight(
        const  WindowCoord  wcVal)
{
    return ( (this->m_cHeight) = wcVal );
}

//----------------------------------------------------------------
//    ウィンドウ内に表示する時の左端座標を取得する。
//

ScreenLayer::WindowCoord
ScreenLayer::getLeft()  const
{
    return ( this->m_cLeft );
}

//----------------------------------------------------------------
//    ウィンドウ内に表示する時の左端座標を設定する。
//

ScreenLayer::WindowCoord
ScreenLayer::setLeft(
        const  WindowCoord  wcVal)
{
    return ( (this->m_cLeft) = wcVal );
}

//----------------------------------------------------------------
//    ウィンドウ内に表示する時の上端座標を取得する。
//

ScreenLayer::WindowCoord
ScreenLayer::getTop()  const
{
    return ( this->m_cTop );
}

//----------------------------------------------------------------
//    ウィンドウ内に表示する時の上端座標を設定する。
//

ScreenLayer::WindowCoord
ScreenLayer::setTop(
        const  WindowCoord  wcVal)
{
    return ( (this->m_cTop) = wcVal );
}

//----------------------------------------------------------------
//    レイヤーの表示状態を取得する。
//

ScreenLayer::LayerVisible
ScreenLayer::getVisibleFlag()  const
{
    return ( this->m_sVisible );
}

//----------------------------------------------------------------
//    レイヤーの表示状態を設定する。
//

ScreenLayer::LayerVisible
ScreenLayer::setVisibleFlag(
        const  LayerVisible  slVal)
{
    return ( (this->m_sVisible) = slVal );
}

//----------------------------------------------------------------
//    ウィンドウ内に表示する時の幅を取得する。
//

ScreenLayer::WindowCoord
ScreenLayer::getWidth()  const
{
    return ( this->m_cWidth );
}

//----------------------------------------------------------------
//    ウィンドウ内に表示する時の幅を設定する。
//

ScreenLayer::WindowCoord
ScreenLayer::setWidth(
        const  WindowCoord  wcVal)
{
    return ( (this->m_cWidth) = wcVal );
}

//========================================================================
//
//    Protected Member Functions (Virtual Functions).
//

//----------------------------------------------------------------
//    マウスの左ボタンを離した時のイベントハンドラ。
//

ScreenLayer::EventResult
ScreenLayer::onLButtonUp(
        const  DWORD        fwKeys,
        const  WindowCoord  xPos,
        const  WindowCoord  yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);
    UTL_HELP_UNUSED_ARGUMENT(xPos);
    UTL_HELP_UNUSED_ARGUMENT(yPos);

    //  デフォルト動作は、何もしない。  //
    return ( EH_RESULT_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
