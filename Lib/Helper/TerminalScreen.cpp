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
**      An Implementation of TerminalScreen class.
**
**      @file       Helper/TerminalScreen.cpp
**/

#include    "FairyShogi/Helper/TerminalScreen.h"

#include    <iostream>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Helper  {

//========================================================================
//
//    TerminalScreen  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

TerminalScreen::TerminalScreen()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

TerminalScreen::~TerminalScreen()
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

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    画面をコンソールモードに変更する。
//

ErrCode
TerminalScreen::setupConsoleMode()
{
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    端末画面をスクリーンモードに変更する。
//

ErrCode
TerminalScreen::setupScreenMode()
{
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    標準出力に文字列と改行を出力する。
//

ErrCode
TerminalScreen::writeLineToStdOut(
        const  std::string  &strText)
{
    std::cout   <<  strText
                <<  std::endl;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    標準出力に文字列を出力する。
//

ErrCode
TerminalScreen::writeTextToStdOut(
        const  std::string  &strText)
{
    std::cout   <<  strText;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    標準エラー出力に文字列と改行を出力する。
//

ErrCode
TerminalScreen::writeLineToStdErr(
        const  std::string  &strText)
{
    std::cerr   <<  strText
                <<  std::endl;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    標準エラー出力に文字列を出力する。
//

ErrCode
TerminalScreen::writeTextToStdErr(
        const  std::string  &strText)
{
    std::cerr   <<  strText;
    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Helper
FAIRYSHOGI_NAMESPACE_END
