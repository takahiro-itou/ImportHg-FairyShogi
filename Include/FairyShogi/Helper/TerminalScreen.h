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
**      An Interface of TerminalScreen class.
**
**      @file       Helper/TerminalScreen.h
**/

#if !defined( FAIRYSHOGI_HELPER_INCLUDED_TERMINAL_SCREEN_H )
#    define   FAIRYSHOGI_HELPER_INCLUDED_TERMINAL_SCREEN_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#if !defined( FAIRYSHOGI_SYS_INCLUDED_STL_STRING )
#    include    <string>
#    define     FAIRYSHOGI_SYS_INCLUDED_STL_STRING
#endif

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Helper  {

//========================================================================
//
//    TerminalScreen  class.
//
/**
**    端末の画面を制御するクラス。
**/

class  TerminalScreen
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
    TerminalScreen();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~TerminalScreen();

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

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   端末画面をコンソールモードに変更する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    setupConsoleMode();

    //----------------------------------------------------------------
    /**   端末画面をスクリーンモードに変更する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    setupScreenMode();

    //----------------------------------------------------------------
    /**   標準出力に文字列と改行を出力する。
    **
    **  @param [in] strText   出力する文字列。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    writeLineToStdOut(
            const  std::string  &strText);

    //----------------------------------------------------------------
    /**   標準出力に文字列を出力する。
    **
    **  @param [in] strText   出力する文字列。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    writeTextToStdOut(
            const  std::string  &strText);

    //----------------------------------------------------------------
    /**   標準エラー出力に文字列と改行を出力する。
    **
    **  @param [in] strText   出力する文字列。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    writeLineToStdErr(
            const  std::string  &strText);

    //----------------------------------------------------------------
    /**   標準エラー出力に文字列を出力する。
    **
    **  @param [in] strText   出力する文字列。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    writeTextToStdErr(
            const  std::string  &strText);

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//

//========================================================================
//
//    Other Features.
//
private:
    typedef     TerminalScreen      This;
    TerminalScreen      (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   TerminalScreenTest;
};

}   //  End of namespace  Helper
FAIRYSHOGI_NAMESPACE_END

#endif
