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

#include    "FairyShogi/Common/FairyShogiConst.h"

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
public:

    typedef     int     PlayerType;

    /**
    **    操作を自動化するオプション。
    **/
    enum  AutoManual  {
        /**   操作を自動実行する。  **/
        OPERATION_AUTO      =  0,

        /**   操作は手動で行う。    **/
        OPERATION_MANUAL    =  1
    };

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
public:

    //----------------------------------------------------------------
    /**   ダイアログを初期化する。
    **
    **  @return     メッセージを処理した場合は TRUE を返す。
    **      メッセージを処理しなかった場合は FALSE  を返す。
    **/
    virtual  BOOL
    initializeDialog();

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   ダイスの自動／手動フラグを取得する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @return     ダイスの自動／手動フラグ。
    **/
    AutoManual
    getDiceRollMode(
            const  PlayerIndex  cPlayer)  const;

    //----------------------------------------------------------------
    /**   ダイスの自動／手動フラグを設定する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @param [in] valNew    設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setDiceRollMode(
            const  PlayerIndex  cPlayer,
            const  AutoManual   valNew);

    //----------------------------------------------------------------
    /**   エンジン思考開始の自動／手動フラグを取得する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @return     ダイスの自動／手動フラグ。
    **/
    AutoManual
    getEngineStart(
            const  PlayerIndex  cPlayer)  const;

    //----------------------------------------------------------------
    /**   エンジン思考開始の自動／手動フラグを設定する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @param [in] valNew    設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setEngineStart(
            const  PlayerIndex  cPlayer,
            const  AutoManual   valNew);

    //----------------------------------------------------------------
    /**   プレーヤーのタイプを取得する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @return     プレーヤータイプ。
    **/
    PlayerType
    getPlayerType(
            const  PlayerIndex  cPlayer)  const;

    //----------------------------------------------------------------
    /**   プレーヤーのタイプを設定する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @param [in] valNew    設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setPlayerType(
            const  PlayerIndex  cPlayer,
            const  PlayerType   valNew);

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
private:

    /**   プレーヤーのタイプ。  **/
    PlayerType      m_playTypes[Common::NUM_PLAYERS];

    /**   ダイスを自動で振る。  **/
    AutoManual      m_fDiceRoll[Common::NUM_PLAYERS];

    /**   思考開始を自動開始。  **/
    AutoManual      m_fEngStart[Common::NUM_PLAYERS];

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
