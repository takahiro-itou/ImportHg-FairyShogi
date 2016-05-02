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
**      An Interface of PromotionScreen class.
**
**      @file       Bin/Win32/PromotionScreen.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_PROMOTION_SCREEN_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_PROMOTION_SCREEN_H

#include    "ScreenLayer.h"

#if !defined( FAIRYSHOGI_STDC_INCLUDED_STL_STRING )
#    include    <string>
#    define     FAIRYSHOGI_STDC_INCLUDED_STL_STRING
#endif

#if !defined( FAIRYSHOGI_STDC_INCLUDED_STL_VECTOR )
#    include    <vector>
#    define     FAIRYSHOGI_STDC_INCLUDED_STL_VECTOR
#endif

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    PromotionScreen  class.
//
/**
**    成り選択画面を管理するクラス。
**/

class  PromotionScreen : public  ScreenLayer
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   ユーザーに示す選択肢の型。    **/
    typedef     std::vector<PieceIndex>     OptionArray;

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
    PromotionScreen();

    //----------------------------------------------------------------
    /**   インスタンスを指定したサイズで初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] wcLeft      左端座標。
    **  @param [in] wcTop       上端座標。
    **  @param [in] wcWidth     幅。
    **  @param [in] wcHeight    高さ。
    **/
    PromotionScreen(
            const  WindowCoord  wcLeft,
            const  WindowCoord  wcTop,
            const  WindowCoord  wcWidth,
            const  WindowCoord  wcHeight);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~PromotionScreen();

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
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
            BitmapImage  *  bmpTrg)  const  override;

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
    /**   必要な画像データを準備する。
    **
    **  @param [in] imgPiece    駒の画像。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setupBitmapImages(
            const  std::string  &imgPiece);

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
    /**   ユーザーが選択したインデックスを取得する。
    **
    **  @return     ユーザーの選択した番号を返す。
    **/
    PieceIndex
    getUserSelect()  const;

    //----------------------------------------------------------------
    /**   ユーザーに示す選択肢を設定する。
    **
    **  @param [in] vSelect   選択肢のリスト。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setSelectionList(
            const  OptionArray  &vSelect);

//========================================================================
//
//    Protected Member Functions (Overrides).
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
            const   DWORD   fwKeys,
            const   UINT    xPos,
            const   UINT    yPos)  OVERRIDE;

//========================================================================
//
//    For Internal Use Only.
//
private:

    static  constexpr   int     SQUARE_WIDTH        = 64;
    static  constexpr   int     SQUARE_HEIGHT       = 64;

//========================================================================
//
//    Member Variables.
//
private:

    /**   ユーザーに示す選択肢。    **/
    OptionArray     m_prmOptions;

    /**   選択肢の表示に使う画像。  **/
    BitmapImage  *  m_biPiece;

    /**   ユーザーの選択した番号。  **/
    PieceIndex      m_psSelected;

//========================================================================
//
//    Other Features.
//
private:
   /**   スーパークラス。  **/
    typedef     ScreenLayer         Super;

private:
    typedef     PromotionScreen     This;
    PromotionScreen     (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   PromotionScreenTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
