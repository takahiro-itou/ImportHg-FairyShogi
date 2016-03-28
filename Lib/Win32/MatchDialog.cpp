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
**      An Implementation of MatchDialog class.
**
**      @file       Win32/MatchDialog.cpp
**/

#include    "FairyShogi/Win32/MatchDialog.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    MatchDialog  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

MatchDialog::MatchDialog()
    : Super()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

MatchDialog::~MatchDialog()
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

//========================================================================
//
//    Protected Member Functions (Overrides).
//

//----------------------------------------------------------------
//    ダイアログプロシージャ。
//

BOOL
MatchDialog::dialogProc(
        const   UINT    uiMsg,
        const   WPARAM  wParam,
        const   LPARAM  lParam)
{
    switch ( uiMsg ) {
    case  WM_COMMAND:
        return ( onCommand(
                         LOWORD(wParam),
                         HIWORD(wParam),
                         reinterpret_cast<HWND>(lParam)) );
        break;
    default:
        return ( FALSE );
    }

    return ( TRUE );
}

//========================================================================
//
//    Protected Member Functions (Virtual Functions).
//

//----------------------------------------------------------------

BOOL
MatchDialog::onCommand(
        const   UINT    wID,
        const   UINT    wNotifyCode,
        const   HWND    hWndControl)
{
    switch ( wID ) {
    case  IDOK:
        ::EndDialog(this->m_hDlgWnd,  IDOK);
        break;
    case  IDCANCEL:
        ::EndDialog(this->m_hDlgWnd,  IDCANCEL);
        break;
    default:
        return ( FALSE );
    }

    return ( TRUE );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
