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
**      An Interface of Animation class.
**
**      @file       Win32/Animation.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_ANIMATION_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_ANIMATION_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    "FairyShogi/Interface/PixelMatrix.h"

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

#include    <queue>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    Animation  class.
//
/**
**    アニメーションを管理するクラス。
**/

class  Animation
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**
    **    アニメーションの速度を制御する型。
    **
    **  各ステップの間の待機時間を指定する。
    **/
    typedef     int                         TWaitTime;

private:

    /**   ビットマップイメージクラス。  **/
    typedef     Interface::PixelMatrix      PixelMatrix;

    /**   ピクセルの座標を指定する型。  **/
    typedef     PixelMatrix::BitmapCoord    BitmapCoord;

    /**
    **    アニメーションのステップ数をカウントする型。
    **/
    typedef     int                         TStepCount;

    /**
    **    アニメーションステップ時のコールバック関数。
    **/
    typedef     Boolean (* LpFnAnimationStep)(
            const   HWND    hWnd,
            Animation     & objAnim);

    struct  AnimationEntry
    {
        BitmapCoord             anmDestX;
        BitmapCoord             anmDestY;

        const   PixelMatrix  *  srcImage;
        BitmapCoord             srcImgX;
        BitmapCoord             srcImgY;
        BitmapCoord             srcImgW;
        BitmapCoord             srcImgH;

        BitmapCoord             anmCurX;
        BitmapCoord             anmCurY;

        BitmapCoord             bcScaleX;
        BitmapCoord             bcScaleY;
        BitmapCoord             bcStepX;
        BitmapCoord             bcStepY;

        TStepCount              cntSteps;
        TWaitTime               msWaits;
    };

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    Animation();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~Animation();

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
public:

    //----------------------------------------------------------------
    /**   アニメーションの壱ステップを描画する。
    **
    **  @param[out] imgDest   描画先のイメージ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    drawAnimation(
            PixelMatrix   & imgDest);

    //----------------------------------------------------------------
    /**   アニメーションを行う指示をキューに挿入する。
    **
    **  @param [in] xFrom
    **  @param [in] yFrom
    **  @param [in] xTo
    **  @param [in] yTo
    **  @param [in] imgSrc
    **  @param [in] srcX
    **  @param [in] srcY
    **  @param [in] srcW
    **  @param [in] srcH
    **  @param [in] nSteps    アニメーションのステップ数。
    **  @param [in] msWait    ステップ間の待機時間（ミリ秒）。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    enqueueAnimation(
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
            const  TWaitTime    msWait);

    //----------------------------------------------------------------
    /**   アニメーションを行うためのループを実行する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    enterAnimationLoop();

    //----------------------------------------------------------------
    /**   アニメーションを次のステップに進める。
    **
    **  @retval     BOOL_TRUE   : アニメーションの続きがある。
    **  @retval     BOOL_FALSE  : アニメーションが終了した。
    **/
    virtual  Boolean
    stepAnimation();

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   アニメーションの状態を取得する。
    **
    **  @retval     BOOL_TRUE   : アニメーションを実行中。
    **  @retval     BOOL_FALSE  : アニメーションは停止中。
    **/
    Boolean
    getAnimationFlag()  const;

    //----------------------------------------------------------------
    /**   アニメーション実行中のコールバック関数を指定する。
    **
    **  @param [in] fnCb    コールバック関数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setAnimationCallback(
            LpFnAnimationStep   const   fnCb);

    //----------------------------------------------------------------
    /**   描画を行うウィンドウを指定する。
    **
    **  @param [in] hWnd    ウィンドウハンドル。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setAnimationWindow(
            const   HWND    hWnd);

    //----------------------------------------------------------------
    /**   ステップ間の待機時間を取得する。
    **
    **  @return     待機時間をミリ秒単位で返す。
    **/
    TWaitTime
    getWaitMilliSeconds()  const;

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    typedef     std::queue<AnimationEntry>      AnimationQueue;

private:

    /**
    **    アニメーションが実行中か停止中かを示すフラグ。
    **/
    Boolean             m_blnAnimFlag;

    /**
    **    アニメーションの現在の状態を管理するデータ。
    **/
    AnimationEntry      m_animFirst;

    /**
    **    アニメーションキュー。
    **/
    AnimationQueue      m_animQueue;

    /**
    **    描画を行う対象のウィンドウハンドル。
    **/
    HWND                m_hTargetWnd;

    /**
    **    アニメーション実行中のコールバック関数。
    **/
    LpFnAnimationStep   m_pfnStepAnim;

//========================================================================
//
//    Other Features.
//
private:
    typedef     Animation       This;
    Animation           (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   AnimationTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
