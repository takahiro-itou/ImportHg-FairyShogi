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
**      An Interface of ChoiceScreen class.
**
**      @file       Bin/Win32/ChoiceScreen.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_CHOICE_SCREEN_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_CHOICE_SCREEN_H

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

//  クラスの前方宣言。  //
class   BitmapResource;

//========================================================================
//
//    ChoiceScreen  class.
//
/**
**    選択画面を管理するクラス。
**/

class  ChoiceScreen : public  ScreenLayer
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   ユーザーに示す選択肢の型。    **/
    typedef     int                         ChoiceIndex;

    /**   選択肢の配列型。              **/
    typedef     std::vector<ChoiceIndex>    OptionArray;

    typedef     int                         ChoiceSize;

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
    ChoiceScreen();

    //----------------------------------------------------------------
    /**   インスタンスを指定したサイズで初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] wcLeft      左端座標。
    **  @param [in] wcTop       上端座標。
    **  @param [in] wcWidth     幅。
    **  @param [in] wcHeight    高さ。
    **/
    ChoiceScreen(
            const  WindowCoord  wcLeft,
            const  WindowCoord  wcTop,
            const  WindowCoord  wcWidth,
            const  WindowCoord  wcHeight);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ChoiceScreen();

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
            BitmapImage  *  bmpTrg)  const  OVERRIDE;

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
    **  @param [in] hInstance   インスタンスハンドル。
    **  @param [in] hDC         デバイスコンテキスト。
    **  @param [in] imgPiece    駒の画像。
    **  @param [in] numCols     横方向に並ぶアイコン数。
    **  @param [in] numRows     縦方向に並ぶアイコン数。
    **  @param [in] xWidth      アイコンの幅。
    **  @param [in] yHeight     アイコンの高さ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setupBitmapImages(
            const  HINSTANCE    hInstance,
            const  HDC          hDC,
            const  LPCTSTR      imgPiece,
            const  ChoiceIndex  numCols,
            const  ChoiceIndex  numRows,
            const  ChoiceSize   xWidth,
            const  ChoiceSize   yHeight);

    //----------------------------------------------------------------
    /**   必要な画像データを準備する。
    **
    **  @param [in] imgPiece    駒の画像。
    **  @param [in] numCols     横方向に並ぶアイコン数。
    **  @param [in] numRows     縦方向に並ぶアイコン数。
    **  @param [in] xWidth      アイコンの幅。
    **  @param [in] yHeight     アイコンの高さ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setupBitmapImages(
            const  std::string  &imgPiece,
            const  ChoiceIndex  numCols,
            const  ChoiceIndex  numRows,
            const  ChoiceSize   xWidth,
            const  ChoiceSize   yHeight);

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
    ChoiceIndex
    getUserSelectCol()  const;

    //----------------------------------------------------------------
    /**   ユーザーが選択したインデックスを取得する。
    **
    **  @return     ユーザーの選択した番号を返す。
    **/
    ChoiceIndex
    getUserSelectIndex()  const;

    //----------------------------------------------------------------
    /**   ユーザーが選択したインデックスを取得する。
    **
    **  @return     ユーザーの選択した番号を返す。
    **/
    ChoiceIndex
    getUserSelectRow()  const;

    //----------------------------------------------------------------
    /**   ユーザーに示す選択肢を設定する。
    **
    **  @param [in] vSelect   選択肢のリスト。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setChoiceList(
            const  OptionArray  &vSelect);

    //----------------------------------------------------------------
    /**   選択肢の表示領域を設定する。
    **
    **  @param [in] numCols
    **  @param [in] numRows
    **  @param [in] xWidth
    **  @param [in] yHeight
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setupChoiceDisplay(
            const  ChoiceIndex  numCols,
            const  ChoiceIndex  numRows,
            const  ChoiceSize   xWidth,
            const  ChoiceSize   yHeight);

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

//========================================================================
//
//    Member Variables.
//
private:

    /**   ユーザーに示す選択肢。    **/
    OptionArray         m_prmOptions;

    /**   選択肢の表示に使う画像。  **/
    BitmapResource  *   m_brPiece;

    /**   ユーザーの選択した場所。  **/
    ChoiceIndex         m_xSelCol;

    /**   ユーザーの選択した場所。  **/
    ChoiceIndex         m_ySelRow;

    /**   ユーザーの選択した場所。  **/
    ChoiceIndex         m_psSelected;

    /**   各選択肢を表示する幅。    **/
    ChoiceSize          m_xImgWidth;

    /**   各選択肢を表示する高さ。  **/
    ChoiceSize          m_yImgHeight;

    /**   選択肢画像の横方向件数。  **/
    ChoiceIndex         m_numSrcCols;

    /**   選択肢画像の横方向件数。  **/
    ChoiceIndex         m_numSrcRows;

    /**   選択肢を横に並べる枚数。  **/
    ChoiceIndex         m_numSelCols;

    /**   選択肢を縦に並べる枚数。  **/
    ChoiceIndex         m_numSelRows;

//========================================================================
//
//    Other Features.
//
private:
    /**   スーパークラス。  **/
    typedef     ScreenLayer         Super;

private:
    typedef     ChoiceScreen        This;
    ChoiceScreen        (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   ChoiceScreenTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
