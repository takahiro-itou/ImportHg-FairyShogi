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

//----------------------------------------------------------------
//    現在チェックされているラジオボタンを取得する。
//

DialogWindow::ComponentID
DialogWindow::getCheckedRadioButton(
        const  ComponentID  idFirst,
        const  ComponentID  idLast)  const
{
    for ( ComponentID cID = idFirst; cID <= idLast; ++ cID )
    {
        if ( isButtonChecked(cID) == BST_CHECKED ) {
            return ( cID );
        }
    }
    return ( 0 );
}

//----------------------------------------------------------------
//    コンボボックスの選択項目を取得する。
//

DialogWindow::TListItemIndex
DialogWindow::getComboSelectedIndex(
        const  ComponentID  idItem)  const
{
    return ( sendDialogItemMessage(idItem, CB_GETCURSEL, 0, 0) );
}

//----------------------------------------------------------------
//    ダイアログ内のアイテムのハンドルを取得する。
//

HWND
DialogWindow::getDialogItem(
        const  ComponentID  idItem)  const
{
    return ( ::GetDlgItem(this->m_hDlgWnd,  idItem) );
}

//----------------------------------------------------------------
//    ボタンコントロールのチェック状態を取得する。
//

UINT
DialogWindow::isButtonChecked(
        const  ComponentID  idItem)  const
{
    return ( sendDialogItemMessage(idItem, BM_GETCHECK, 0, 0) );
}

//----------------------------------------------------------------
//    ダイアログ内のアイテムにメッセージを送信する。
//

LONG
DialogWindow::sendDialogItemMessage(
        const  ComponentID  idItem,
        const  UINT         uiMsg,
        const  WPARAM       wParam,
        const  LPARAM       lParam)  const
{
    return ( ::SendDlgItemMessage(
                     this->m_hDlgWnd, idItem,
                     uiMsg,  wParam,  lParam)
    );
}

//----------------------------------------------------------------
//    コンボボックスの選択項目を設定する。
//

Boolean
DialogWindow::setComboSelectedIndex(
        const  ComponentID      idItem,
        const  TListItemIndex   idxSel)
{
    sendDialogItemMessage(idItem, CB_SETCURSEL, idxSel, 0);
    return ( BOOL_TRUE );
}

//----------------------------------------------------------------
//    モーダルダイアログを表示する。
//

DialogWindow::TDialogResult
DialogWindow::showModalDialog(
        const   UINT    idRes,
        const   HWND    hParent)
{
    HINSTANCE   hInstance   =  reinterpret_cast<HINSTANCE>(
            ::GetWindowLongPtr(hParent, GWLP_HINSTANCE) );

    return ( ::DialogBoxParam(
                     hInstance,  MAKEINTRESOURCE(idRes),
                     hParent,
                     reinterpret_cast<DLGPROC>(& dialogProcStatic),
                     reinterpret_cast<LPARAM>(this)) );
}

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
