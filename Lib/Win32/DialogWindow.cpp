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
**      An Implementation of DialogWindow class.
**
**      @file       Win32/DialogWindow.cpp
**/

#include    "FairyShogi/Win32/DialogWindow.h"

#include    "FairyShogi/Common/HelperMacros.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    DialogWindow  class.
//

//========================================================================
//
//    Internal Type Definitions.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  デフォルトコンストラクタ）。
//

DialogWindow::DialogWindow()
    : m_hDlgWnd(NULL)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

DialogWindow::~DialogWindow()
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

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    ダイアログボックスのハンドルを取得する。
//

HWND
DialogWindow::getWindowHandle()  const
{
    return ( this->m_hDlgWnd );
}

//========================================================================
//
//    Protected Member Functions (Virtual Functions).
//

//----------------------------------------------------------------
//    ダイアログプロシージャ。
//

BOOL
DialogWindow::dialogProc(
        const   UINT    uiMsg,
        const   WPARAM  wParam,
        const   LPARAM  lParam)
{
    UTL_HELP_UNUSED_ARGUMENT(uiMsg);
    UTL_HELP_UNUSED_ARGUMENT(wParam);
    UTL_HELP_UNUSED_ARGUMENT(lParam);

    return ( FALSE );
}

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    ダイアログプロシージャ。
//

BOOL    CALLBACK
DialogWindow::dialogProcStatic(
        HWND    hDlgWnd,
        UINT    uiMsg,
        WPARAM  wParam,
        LPARAM  lParam)
{
    DialogWindow  *  ptrDlg = reinterpret_cast<DialogWindow *>(
            ::GetWindowLongPtr(hDlgWnd,  DWLP_USER));
    if ( uiMsg == WM_INITDIALOG ) {
        ptrDlg  = reinterpret_cast<DialogWindow *>(lParam);
        ptrDlg->m_hDlgWnd   =  hDlgWnd;
        ::SetWindowLongPtr(hDlgWnd,  DWLP_USER,  lParam);
    } else if ( ptrDlg == (nullptr) ) {
        return ( FALSE );
    }

    return ( ptrDlg->dialogProc(uiMsg, wParam, lParam) );
}


}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
