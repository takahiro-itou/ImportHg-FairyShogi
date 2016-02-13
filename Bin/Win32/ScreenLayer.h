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

FAIRYSHOGI_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Interface  {
class   BitmapImage;
}   //  End of namespace  Interface

namespace  Interface  {

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
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

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

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
