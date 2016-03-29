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
**      An Interface of DialogWindow class.
**
**      @file       Win32/DialogWindow.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_DIALOG_WINDOW_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_DIALOG_WINDOW_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    DialogWindow  class.
//
/**
**    ダイアログウィンドウクラス。
**/

class  DialogWindow
{

//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     int     TDialogResult;

    typedef     int     ComponentID;

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
    DialogWindow();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~DialogWindow();

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
    /**   ダイアログ内のアイテムのハンドルを取得する。
    **
    **  @param [in] idItem    アイテムの識別子。
    **  @return     指定したアイテムのハンドル。
    **/
    HWND
    getDialogItem(
            const  ComponentID  idItem);

    //----------------------------------------------------------------
    /**   ダイアログ内のアイテムにメッセージを送信する。
    **
    **  @param [in] idItem    アイテムの識別子。
    **  @param [in] uiMsg     メッセージ。
    **  @param [in] wParam    パラメータ。
    **  @param [in] lParam    パラメータ。
    **/
    LONG
    sendDialogItemMessage(
            const  ComponentID  idItem,
            const  UINT         uiMsg,
            const  WPARAM       wParam,
            const  LPARAM       lParam);

    //----------------------------------------------------------------
    /**   モーダルダイアログを表示する。
    **
    **  @param [in] idRes     ダイアログリソースの識別子。
    **  @param [in] hParent   ダイアログを所有するウィンドウ。
    **  @return     ダイアログボックスを終了するための、
    **      EndDialog 関数の呼び出しで指定された値を返す。
    **/
    TDialogResult
    showModalDialog(
            const   UINT    idRes,
            const   HWND    hParent);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   ダイアログボックスのハンドルを取得する。
    **
    **  @return     ダイアログのウィンドウハンドル。
    **/
    HWND
    getWindowHandle()  const;

//========================================================================
//
//    Protected Member Functions (Virtual Functions).
//
protected:

    //----------------------------------------------------------------
    /**   ダイアログプロシージャ。
    **
    **  @param [in] hDlgWnd   ダイアログボックスのハンドル。
    **  @param [in] uiMsg     メッセージ。
    **  @param [in] wParam    パラメータ。
    **  @param [in] lParam    パラメータ。
    **  @return     メッセージを処理した場合は TRUE を返す。
    **      メッセージを処理しなかった場合は FALSE  を返す。
    **/
    virtual  BOOL
    dialogProc(
            const   UINT    uiMsg,
            const   WPARAM  wParam,
            const   LPARAM  lParam);

//========================================================================
//
//    For Internal Use Only.
//
private:

    //----------------------------------------------------------------
    /**   ダイアログプロシージャ。
    **
    **  @param [in] hDlgWnd   ダイアログボックスのハンドル。
    **  @param [in] uiMsg     メッセージ。
    **  @param [in] wParam    パラメータ。
    **  @param [in] lParam    パラメータ。
    **  @return     メッセージを処理した場合は TRUE を返す。
    **      メッセージを処理しなかった場合は FALSE  を返す。
    **/
    static  BOOL    CALLBACK
    dialogProcStatic(
            HWND    hDlgWnd,
            UINT    uiMsg,
            WPARAM  wParam,
            LPARAM  lParam);

//========================================================================
//
//    Member Variables.
//
protected:

    /**   ダイアログボックスのウィンドウハンドル。  **/
    HWND        m_hDlgWnd;

//========================================================================
//
//    Other Features.
//
private:
    typedef     DialogWindow    This;
    DialogWindow        (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   DialogWindowTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
