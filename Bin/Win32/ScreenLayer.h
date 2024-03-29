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
**      An Interface of ScreenLayer class.
**
**      @file       Bin/Win32/ScreenLayer.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SCREEN_LAYER_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_SCREEN_LAYER_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//  クラスの前方宣言。  //
class   BitmapImage;

//========================================================================
//
//    ScreenLayer  class.
//
/**
**    画面表示のレイヤーを管理するクラス。
**/

class  ScreenLayer
{
public:

    /**   座標を表すための型。  **/
    typedef     int     WindowCoord;

    /**   レイヤーの表示状態。  **/
    enum  LayerVisible
    {
        LV_HIDDEN,          /**<  非表示。          **/
        LV_DISABLED,        /**<  表示するが無効。  **/
        LV_ENABLED          /**<  有効状態で表示。  **/
    };

    /**   イベントハンドラの戻り値型。  **/
    enum  EventResult
    {
        /**   異常終了。    **/
        EH_RESULT_FAILURE,

        /**   正常終了。    **/
        EH_RESULT_SUCCESS,

        /**   正常終了。再描画が必要。  **/
        EH_RESULT_REDRAW
    };

    /**   ビットマップイメージクラス。  **/
    typedef     Win32::BitmapImage      BitmapImage;

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
    ScreenLayer();

    //----------------------------------------------------------------
    /**   インスタンスを指定したサイズで初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] wcLeft      左端座標。
    **  @param [in] wcTop       上端座標。
    **  @param [in] wcWidth     幅。
    **  @param [in] wcHeight    高さ。
    **/
    ScreenLayer(
            const  WindowCoord  wcLeft,
            const  WindowCoord  wcTop,
            const  WindowCoord  wcWidth,
            const  WindowCoord  wcHeight);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ScreenLayer();

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
public:

    //----------------------------------------------------------------
    /**   指定したビットマップイメージ上に内容を描画する。
    **
    **  @param [in,out] bmpTrg    描画対象のイメージ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    drawScreenLayer(
            BitmapImage  *  bmpTrg)  const  = 0;

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//
public:

    //----------------------------------------------------------------
    /**   イベントハンドラを呼び出す。
    **
    **  @param [in] fwKeys
    **  @param [in] xPos
    **  @param [in] yPos
    **  @return     イベントハンドラの処理結果。
    **/
    virtual  EventResult
    dispatchLButtonUp(
            const   DWORD   fwKeys,
            const   UINT    xPos,
            const   UINT    yPos);

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
    /**   ウィンドウ内に表示する時の高さを取得する。
    **
    **  @return     高さを返す。
    **/
    WindowCoord
    getHeight()  const;

    //----------------------------------------------------------------
    /**   ウィンドウ内に表示する時の高さを設定する。
    **
    **  @param [in] wcVal   設定する値。
    **  @return     設定した値を返す。
    **/
    WindowCoord
    setHeight(
            const  WindowCoord  wcVal);

    //----------------------------------------------------------------
    /**   ウィンドウ内に表示する時の左端座標を取得する。
    **
    **  @return     左端座標を返す。
    **/
    WindowCoord
    getLeft()  const;

    //----------------------------------------------------------------
    /**   ウィンドウ内に表示する時の左端座標を設定する。
    **
    **  @param [in] wcVal   設定する値。
    **  @return     設定した値を返す。
    **/
    WindowCoord
    setLeft(
            const  WindowCoord  wcVal);

    //----------------------------------------------------------------
    /**   ウィンドウ内に表示する時の上端座標を取得する。
    **
    **  @return     上端座標を返す。
    **/
    WindowCoord
    getTop()  const;

    //----------------------------------------------------------------
    /**   ウィンドウ内に表示する時の上端座標を設定する。
    **
    **  @param [in] wcVal   設定する値。
    **  @return     設定した値を返す。
    **/
    WindowCoord
    setTop(
            const  WindowCoord  wcVal);

    //----------------------------------------------------------------
    /**   レイヤーの表示状態を取得する。
    **
    **  @return     表示状態を表すフラグを返す。
    **/
    LayerVisible
    getVisibleFlag()  const;

    //----------------------------------------------------------------
    /**   レイヤーの表示状態を設定する。
    **
    **  @param [in] slVal   設定する値。
    **  @return     設定した値を返す。
    **/
    LayerVisible
    setVisibleFlag(
            const  LayerVisible  slVal);

    //----------------------------------------------------------------
    /**   ウィンドウ内に表示する時の幅を取得する。
    **
    **  @return     幅を返す。
    **/
    WindowCoord
    getWidth()  const;

    //----------------------------------------------------------------
    /**   ウィンドウ内に表示する時の幅を設定する。
    **
    **  @param [in] wcVal   設定する値。
    **  @return     設定した値を返す。
    **/
    WindowCoord
    setWidth(
            const  WindowCoord  wcVal);

//========================================================================
//
//    Protected Member Functions (Virtual Functions).
//
protected:

    //----------------------------------------------------------------
    /**   マウスの左ボタンを離した時のイベントハンドラ。
    **
    **  @param [in] fwKeys
    **  @param [in] xPos
    **  @param [in] yPos
    **  @return     イベントハンドラの処理結果。
    **/
    virtual  EventResult
    onLButtonUp(
            const  DWORD        fwKeys,
            const  WindowCoord  xPos,
            const  WindowCoord  yPos);

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    /**   表示状態。            **/
    LayerVisible    m_sVisible;

    /**   表示位置。左端座標。  **/
    WindowCoord     m_cLeft;

    /**   表示位置。上端座標。  **/
    WindowCoord     m_cTop;

    /**   表示する幅。          **/
    WindowCoord     m_cWidth;

    /**   表示する高さ。        **/
    WindowCoord     m_cHeight;

//========================================================================
//
//    Other Features.
//
private:
    typedef     ScreenLayer     This;
    ScreenLayer         (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   ScreenLayerTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
