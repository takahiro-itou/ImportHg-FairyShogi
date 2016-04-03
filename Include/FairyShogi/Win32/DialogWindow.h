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
public:

    typedef     int     TDialogResult;

    typedef     int     ComponentID;

    typedef     int     TListItemIndex;;

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
    /**   現在チェックされているラジオボタンを取得する。
    **
    **  @param [in] idFirst   グループの最初のボタン。
    **  @param [in] idLast    グループの最後のボタン。
    **  @return     選択されているラジオボタンの ID を返す。
    **      何も選択されていない場合はゼロを返す。
    **/
    ComponentID
    getCheckedRadioButton(
            const  ComponentID  idFirst,
            const  ComponentID  idLast)  const;

    //----------------------------------------------------------------
    /**   コンボボックスの選択項目を取得する。
    **
    **  @param [in] idItem    アイテムの識別子。
    **  @return     選択されている項目のインデックス。
    **/
    TListItemIndex
    getComboSelectedIndex(
            const  ComponentID  idItem)  const;

    //----------------------------------------------------------------
    /**   ダイアログ内のアイテムのハンドルを取得する。
    **
    **  @param [in] idItem    アイテムの識別子。
    **  @return     指定したアイテムのハンドル。
    **/
    HWND
    getDialogItem(
            const  ComponentID  idItem)  const;

    //----------------------------------------------------------------
    /**   ボタンコントロールのチェック状態を取得する。
    **
    **  @param [in] idItem    ボタンの識別子。
    **  @retval     BST_CHECKED   ボタン
    **  @return     選択されているラジオボタンの ID を返す。
    **      何も選択されていない場合はゼロを返す。
    **/
    UINT
    isButtonChecked(
            const  ComponentID  idItem)  const;

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
            const  LPARAM       lParam)  const;

    //----------------------------------------------------------------
    /**   コンボボックスの選択項目を設定する。
    **
    **  @param [in] idItem    アイテムの識別子。
    **  @param [in] idxSel    選択する項目のインデックス。
    **  @retval     BOOL_TRUE     正常終了。
    **  @retval     BOOL_FALSE    異常終了。
    **/
    Boolean
    setComboSelectedIndex(
            const  ComponentID      idItem,
            const  TListItemIndex   idxSel);

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
