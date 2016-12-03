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
**      An Interface of TextUserInterface class.
**
**      @file       TextUI/TextUserInterface.h
**/

#if !defined( FAIRYSHOGI_TEXTUI_INCLUDED_TEXT_USER_INTERFACE_H )
#    define   FAIRYSHOGI_TEXTUI_INCLUDED_TEXT_USER_INTERFACE_H

#include    "FairyShogi/Common/MersenneTwister.h"
#include    "FairyShogi/Interface/GraphicalInterface.h"

#include    <ncurses.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  TextUI  {

//========================================================================
//
//    TextUserInterface  class.
//
/**
**    テキストユーザーインターフェイスクラス。
**/

class  TextUserInterface
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   カーソルの座標を指定する型。  **/
    typedef     int     CursorCoord;

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
    TextUserInterface();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~TextUserInterface();

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
    /**   内部座標をカーソル座標に変換する。
    **
    **  @param [in] xIntCol   内部座標。
    **  @return     カーソル座標。
    **/
    virtual  FileCol
    getCursorColFromInternal(
            const  FileCol  xIntCol)  const;

    //----------------------------------------------------------------
    /**   内部座標をカーソル座標に変換する。
    **
    **  @param [in] yIntRow   内部座標。
    **  @return     カーソル座標。
    **/
    virtual  RankRow
    getCursorRowFromInternal(
            const  RankRow  yIntRow)  const;

    //----------------------------------------------------------------
    /**   現在の盤面を表示する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    showCurrentState()  const;

    //----------------------------------------------------------------
    /**   追加の情報を表示する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    showInformations()  const;

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   端末制御ライブラリを終了する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    cleanupScreen();

    //----------------------------------------------------------------
    /**   端末座標に対応する内部座標を計算する。
    **
    **  @param [in] sY    画面全体での端末座標。
    **  @param [in] sX    画面全体での端末座標。
    **  @param[out] cW    カーソルを持つウィンドウ。
    **  @param[out] cY    カーソル座標。
    **  @param[out] cX    カーソル座標。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    computeCursorPosition(
            const  CursorCoord  sY,
            const  CursorCoord  sX,
            WINDOW  *        &  cW,
            RankRow          &  cY,
            FileCol          &  cX)  const;

    //----------------------------------------------------------------
    /**   カーソルを表示する端末座標を計算する。
    **
    **  @param[out] sY    画面全体での座標。
    **  @param[out] sX    画面全体での座標。
    **  @param[out] cW    カーソルを持つウィンドウ。
    **  @param[out] wY    ウィンドウ内での座標。
    **  @param[out] wX    ウィンドウ内での座標。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    computeScreenPosition(
            CursorCoord  &  sY,
            CursorCoord  &  sX,
            WINDOW  *    &  cW,
            CursorCoord  &  wY,
            CursorCoord  &  wX)  const;

    //----------------------------------------------------------------
    /**   現在のカーソル位置を取得する。
    **
    **  @param[out] yCurRow   垂直方向。
    **  @param[out] xCurCol   水平方向。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    getCursorPosition(
            RankRow  &  yCurRow,
            FileCol  &  xCurCol)  const;

    //----------------------------------------------------------------
    /**   カーソル位置を変更する。
    **
    **  @param [in] yIncRow   垂直方向の増分。
    **  @param [in] xIncCol   水平方向の増分。
    **/
    ErrCode
    incrementCursorPosition(
            const  RankRow  yIncRow,
            const  FileCol  xIncCol);

    //----------------------------------------------------------------
    /**   カーソル位置を変更する。
    **
    **  @param [in] yNewRow
    **  @param [in] xNewCol
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setCursorPosition(
            const  RankRow  yNewRow,
            const  FileCol  xNewCol);

    //----------------------------------------------------------------
    /**   色を準備する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setupColors();

    //----------------------------------------------------------------
    /**   端末制御ライブラリを初期化する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setupScreen();

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   移動元の座標を設定する。
    **
    **  @param [in] ySrcRow
    **  @param [in] xSrcCol
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setSourcePosition(
            const  RankRow  ySrcRow,
            const  FileCol  xSrcCol);

    //----------------------------------------------------------------
    /**   移動先の座標を設定する。
    **
    **  @param [in] yTrgRow
    **  @param [in] yTrgCol
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setTargetPosition(
            const  RankRow  yTrgRow,
            const  FileCol  xTrgCol);

//========================================================================
//
//    For Internal Use Only.
//
private:

    typedef     Interface::GraphicalInterface       GameInterface;

    typedef     Common::MersenneTwister             RandomGenerator;

    typedef     RandomGenerator::TResultInt         RandResult;

    static  CONSTEXPR_VAR   RandResult
    RANDOM_MAX_VALUE    = RandomGenerator::MaxValue<28>::VALUE;

private:

    //----------------------------------------------------------------
    /**   端末座標が指定したウィンドウ内にあるか判定する。
    **
    **  @param [in] wndTest   テストするウィンドウ。
    **  @param [in] sY        画面全体での端末座標。
    **  @param [in] sX        画面全体での端末座標。
    **  @param[out] wY        ウィンドウ内での端末座標。
    **  @param[out] wX        ウィンドウ内での端末座標。
    **  @retval     BOOL_TRUE   : ウィンドウ内。
    **  @retval     BOOL_FALSE  : ウィンドウ外。
    **/
    Boolean
    checkCoordInWindow(
            WINDOW  *  const    wndTest,
            const  CursorCoord  sY,
            const  CursorCoord  sX,
            CursorCoord      &  wY,
            CursorCoord      &  wX)  const;

//========================================================================
//
//    Member Variables.
//
private:

    /**   ゲームコントローラ。  **/
    GameInterface       m_giGameCtrl;

    /**   乱数のジェネレータ。  **/
    RandomGenerator     m_rndGen;

    /**   端末制御の初期化フラグ。  **/
    Boolean             m_flgInitScr;

    /**
    **    端末内のウィンドウ（スクリーン全体）。
    **/
    WINDOW  *           m_wScreen;

    /**
    **    端末内のウィンドウ（盤面表示）。
    **/
    WINDOW  *           m_wBoard;

    /**
    **    端末内のウィンドウ（持ち駒表示）。
    **/
    WINDOW  *           m_wHands[2];

    /**
    **    情報／コマンドウィンドウ。
    **/
    WINDOW  *           m_wInfos;

    /**   カーソルの座標（内部座標）。  **/
    RankRow             m_yCurRow;

    /**   カーソルの座標（内部座標）。  **/
    FileCol             m_xCurCol;

    /**   選択した移動元座標。  **/
    RankRow             m_ySrcRow;

    /**   選択した移動元座標。  **/
    FileCol             m_xSrcCol;

    /**   選択した移動先座標。  **/
    RankRow             m_yTrgRow;

    /**   選択した移動先座標。  **/
    FileCol             m_xTrgCol;

//========================================================================
//
//    Other Features.
//
private:
    typedef     TextUserInterface   This;
    TextUserInterface   (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   TextUserInterfaceTest;
};

}   //  End of namespace  TextUI
FAIRYSHOGI_NAMESPACE_END

#endif
