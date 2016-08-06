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

#include    <memory.h>

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
    : m_blnAnimFlag(BOOL_FALSE),
      m_animFirst  (),
      m_animQueue  (),
      m_hTargetWnd (NULL),
      m_pfnStepAnim(nullptr)
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
    if ( (this->m_blnAnimFlag) == BOOL_FALSE ) {
        //  アニメーションが停止中のときは何もしない。  //
        return( ERR_SUCCESS );
    }

    imgDest.copyRectangle(
            (this->m_animFirst.anmCurX) / (this->m_animFirst.bcScaleX),
            (this->m_animFirst.anmCurY) / (this->m_animFirst.bcScaleY),
            (this->m_animFirst.srcImgW),
            (this->m_animFirst.srcImgH),
            (* this->m_animFirst.srcImage),
            (this->m_animFirst.srcImgX),
            (this->m_animFirst.srcImgY) );

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    アニメーションを行う指示をキューに挿入する。
//

ErrCode
Animation::enqueueAnimation(
        const  BitmapCoord  xFrom,
        const  BitmapCoord  yFrom,
        const  BitmapCoord  xTo,
        const  BitmapCoord  yTo,
        const  PixelMatrix  &imgSrc,
        const  BitmapCoord  srcX,
        const  BitmapCoord  srcY,
        const  BitmapCoord  srcW,
        const  BitmapCoord  srcH,
        const  TStepCount   nSteps,
        const  TWaitTime    msWait)
{
    AnimationEntry  anmEnt;

    anmEnt.anmDestX = xTo;
    anmEnt.anmDestY = yTo;

    anmEnt.srcImage = &imgSrc;
    anmEnt.srcImgX  = srcX;
    anmEnt.srcImgY  = srcY;
    anmEnt.srcImgW  = srcW;
    anmEnt.srcImgH  = srcH;

    anmEnt.bcScaleX = 32;
    anmEnt.bcScaleY = 32;
    anmEnt.bcStepX  = (xTo - xFrom) * anmEnt.bcScaleX / nSteps;
    anmEnt.bcStepY  = (yTo - yFrom) * anmEnt.bcScaleY / nSteps;

    anmEnt.anmCurX  = xFrom * anmEnt.bcScaleX;
    anmEnt.anmCurY  = yFrom * anmEnt.bcScaleY;
    anmEnt.cntSteps = nSteps;
    anmEnt.msWaits  = msWait;

    this->m_animQueue.push(anmEnt);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    アニメーションを行うためのループを実行する。
//

ErrCode
Animation::enterAnimationLoop()
{
    LpFnAnimationStep   pfnStep = (this->m_pfnStepAnim);
    if ( pfnStep == nullptr ) {
        return ( ERR_FAILURE );
    }

    if ( this->m_animQueue.empty() ) {
        //  アニメーションキューが空だった、何もできない。  //
        return ( ERR_FAILURE );
    }

    const  HWND         hTrgWnd = (this->m_hTargetWnd);

    //  キューの先頭のエントリを取り出す。  //
    this->m_animFirst   = this->m_animQueue.front();
    this->m_animQueue.pop();

    this->m_blnAnimFlag = BOOL_TRUE;

    int     ret;
    MSG     msg;
    while ( this->m_blnAnimFlag ) {
        if ( ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) ) {
            //  メッセージを処理する。      //
            ret = ::GetMessage(&msg, NULL, 0, 0);
            if ( ret == 0 || ret == -1 ) {
                break;
            }
            ::TranslateMessage(&msg);
            ::DispatchMessage (&msg);
        }

        //  アニメーションを処理する。  //
        ::InvalidateRect(hTrgWnd, NULL, FALSE);
        ::UpdateWindow  (hTrgWnd);
        if ( (* pfnStep)(hTrgWnd, * this) == BOOL_FALSE ) {
            return ( ERR_FAILURE );
        }
    }

    ::InvalidateRect(hTrgWnd, NULL, FALSE);
    ::UpdateWindow  (hTrgWnd);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    アニメーションを次のステップに進める。
//

Boolean
Animation::stepAnimation()
{
    if ( (this->m_blnAnimFlag) == BOOL_FALSE ) {
        //  アニメーションが停止中のときは何もしない。  //
        return( BOOL_FALSE );
    }

    this->m_animFirst.anmCurX   +=  (this->m_animFirst.bcStepX);
    this->m_animFirst.anmCurY   +=  (this->m_animFirst.bcStepY);

    if ( (-- (this->m_animFirst.cntSteps)) >= 0 ) {
        return ( BOOL_TRUE );
    }

    //  アニメーションフレームが終了した。  //
    if ( this->m_animQueue.empty() ) {
        //  次のフレームも存在しないので、すべて終了した。  //
        this->m_blnAnimFlag = BOOL_FALSE;
        return ( BOOL_FALSE );
    }

    //  次のフレームを実行する準備をする。  //
    this->m_animFirst   = this->m_animQueue.front();
    this->m_animQueue.pop();
    return ( BOOL_TRUE );
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
    return ( this->m_blnAnimFlag );
}

//----------------------------------------------------------------
//    アニメーション実行中のコールバック関数を指定する。
//

ErrCode
Animation::setAnimationCallback(
        LpFnAnimationStep   const   fnCb)
{
    this->m_pfnStepAnim = fnCb;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    描画を行うウィンドウを指定する。
//

ErrCode
Animation::setAnimationWindow(
        const   HWND    hWnd)
{
    this->m_hTargetWnd  = hWnd;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ステップ間の待機時間を取得する。
//

Animation::TWaitTime
Animation::getWaitMilliSeconds()  const
{
    return ( this->m_animFirst.msWaits );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
