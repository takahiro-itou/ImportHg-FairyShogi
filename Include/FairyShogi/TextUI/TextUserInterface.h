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
    /**   カーソル位置を変更する。
    **
    **  @param [in] yNewRow
    **  @param [in] xNewCol
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    changeCursorPosition(
            const  RankRow  yNewRow,
            const  FileCol  xNewCol);

    //----------------------------------------------------------------
    /**   カーソル位置を変更する。
    **
    **/
    virtual  ErrCode
    incrementCursorPosition(
            const  RankRow  yIncRow,
            const  FileCol  xIncCol);

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

    /**   カーソル位置。    **/
    RankRow             m_yCurRow;

    /**   カーソル位置。    **/
    FileCol             m_xCurCol;

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
