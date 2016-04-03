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

#if !defined( FAIRYSHOGI_SYS_INCLUDED_STL_STRING )
#    include    <string>
#    define     FAIRYSHOGI_SYS_INCLUDED_STL_STRING
#endif

#if !defined( FAIRYSHOGI_SYS_INCLUDED_STL_VECTOR )
#    include    <vector>
#    define     FAIRYSHOGI_SYS_INCLUDED_STL_VECTOR
#endif

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

    /**
    **    操作を自動化するオプション。
    **/
    enum  AutoManual  {
        /**   操作は手動で行う。    **/
        OPERATION_MANUAL    =  0,

        /**   操作を自動実行する。  **/
        OPERATION_AUTO      =  1
    };

    /**
    **    プレーヤーの種類。
    **/
    enum  PlayerType
    {
        PLAYER_TYPE_MAN     =  0,
        PLAYER_TYPE_COM     =  1
    };

    /**
    **    思考エンジンのレベル。
    **/
    typedef     int     EngineLevel;

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
    /**   思考エンジンのレベルを取得する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @return     思考エンジンのレベル。
    **/
    EngineLevel
    getEngineLevel(
            const  PlayerIndex  cPlayer)  const;

    //----------------------------------------------------------------
    /**   思考エンジンのレベルを設定する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @param [in] valNew    設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setEngineLevel(
            const  PlayerIndex  cPlayer,
            const  EngineLevel  valNew);

    //----------------------------------------------------------------
    /**   エンジン思考開始の自動／手動フラグを取得する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @return     エンジン思考開始の自動／手動フラグ。
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
    /**   対局のコメントを取得する。
    **
    **  @return     コメント文字列を返す。
    **/
    const  std::string  &
    getMatchComment()  const;

    //----------------------------------------------------------------
    /**   対局のコメントを設定する。
    **
    **  @param [in] valNew    設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setMatchComment(
            const  std::string  &valNew);

    //----------------------------------------------------------------
    /**   プレーヤーの名前を取得する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @return     プレーヤーの名前。
    **/
    const  std::string  &
    getPlayerName(
            const  PlayerIndex  cPlayer)  const;

    //----------------------------------------------------------------
    /**   プレーヤーの名前を設定する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @param [in] valNew    設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setPlayerName(
            const  PlayerIndex  cPlayer,
            const  std::string  &valNew);

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

    //----------------------------------------------------------------
    /**   ダイアログの内容を変数に保存する。
    **
    **  @retval     BOOL_TRUE     正常終了。
    **  @retval     BOOL_FALSE    異常終了。
    **/
    virtual  Boolean
    saveDialogItems();

//========================================================================
//
//    Protected Member Functions (Virtual Functions).
//
protected:

    //----------------------------------------------------------------
    /**   ボタンをクリックした時のイベントハンドラ。
    **
    **  @param [in] wID
    **  @param [in] wNotifyCode
    **  @param [in] hWndControl
    **  @return     メッセージを処理した場合は TRUE を返す。
    **      メッセージを処理しなかった場合は FALSE  を返す。
    **/
    virtual  BOOL
    onCommand(
            const   UINT    wID,
            const   UINT    wNotifyCode,
            const   HWND    hWndControl);

//========================================================================
//
//    For Internal Use Only.
//
private:

    //----------------------------------------------------------------
    /**   ラジオボタンの設定内容を取得する。
    **
    **  @param [in] idManual    手動ボタンの識別子。
    **  @param [in] idAuto      自動ボタンの識別子。
    **  @param [in] defVal      デフォルトの設定値。
    **  @return     現在の設定値を返す。
    **/
    AutoManual
    readAutoManualOption(
            const  ComponentID  idManual,
            const  ComponentID  idAuto,
            const  AutoManual   defVal);

    //----------------------------------------------------------------
    /**   ラジオボタンの設定内容を取得する。
    **
    **  @param [in] idMan     人間ボタンの識別子。
    **  @param [in] idCom     エンジンボタンの識別子。
    **  @param [in] defVal    デフォルトの設定値。
    **  @return     現在の設定値を返す。
    **/
    PlayerType
    readPlayerTypeOption(
            const  ComponentID  idMan,
            const  ComponentID  idCom,
            const  PlayerType   defVal);

    //----------------------------------------------------------------
    /**   設定をラジオボタンに反映する。
    **
    **  @param [in] idItem    ボタンの識別子。
    **  @param [in] curVal    現在の設定値。
    **  @param [in] btnVal    ボタンの設定値。
    **  @retval     BOOL_TRUE     正常終了。
    **  @retval     BOOL_FALSE    異常終了。
    **/
    template  <typename  TValueType>
    inline  Boolean
    setupRadioButton(
            const  ComponentID  idItem,
            const  TValueType   curVal,
            const  TValueType   btnVal);

    //----------------------------------------------------------------
    /**   設定をラジオボタンに反映する。
    **
    **  @param [in] idManual    手動ボタンの識別子。
    **  @param [in] idAuto      自動ボタンの識別子。
    **  @param [in] curVal      現在の設定値。
    **  @retval     BOOL_TRUE     正常終了。
    **  @retval     BOOL_FALSE    異常終了。
    **/
    Boolean
    setupAutoManualOptions(
            const  ComponentID  idManual,
            const  ComponentID  idAuto,
            const  AutoManual   curVal);

    //----------------------------------------------------------------
    /**   設定をラジオボタンに反映する。
    **
    **  @param [in] idMan     人間ボタンの識別子。
    **  @param [in] idCom     エンジンボタンの識別子。
    **  @param [in] curVal    現在の設定値。
    **  @retval     BOOL_TRUE     正常終了。
    **  @retval     BOOL_FALSE    異常終了。
    **/
    Boolean
    setupPlayerTypeOptions(
            const  ComponentID  idMan,
            const  ComponentID  idCom,
            const  PlayerType   curVal);

//========================================================================
//
//    Member Variables.
//
private:

    /**   プレーヤーのタイプ。  **/
    PlayerType      m_etPlayers[Common::NUM_PLAYERS];

    /**   人プレーヤーの名前。  **/
    std::string     m_pManNames[Common::NUM_PLAYERS];

    /**   思考エンジンレベル。  **/
    EngineLevel     m_engLevels[Common::NUM_PLAYERS];

    /**   ダイスを自動で振る。  **/
    AutoManual      m_fDiceRoll[Common::NUM_PLAYERS];

    /**   思考開始を自動開始。  **/
    AutoManual      m_fEngStart[Common::NUM_PLAYERS];

    /**   対局の追加コメント。  **/
    std::string     m_strComment;

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
