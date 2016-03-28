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
**      An Interface of MatchDialog class.
**
**      @file       Win32/MatchDialog.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_MATCH_DIALOG_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_MATCH_DIALOG_H

#include    "FairyShogi/Win32/DialogWindow.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    MatchDialog  class.
//
/**
**    ダイアログウィンドウクラス。
**/

class  MatchDialog : public  DialogWindow
{

//========================================================================
//
//    Internal Type Definitions.
//

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
    MatchDialog();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~MatchDialog();

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
            const   LPARAM  lParam)  OVERRIDE;

//========================================================================
//
//    Protected Member Functions (Virtual Functions).
//
protected:

    virtual  BOOL
    onCommand(
            const   UINT    wID,
            const   UINT    wNotifyCode,
            const   HWND    hWndControl);

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
    /**   スーパークラス。  **/
    typedef     DialogWindow    Super;

private:
    typedef     MatchDialog     This;
    MatchDialog         (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   MatchDialogTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
