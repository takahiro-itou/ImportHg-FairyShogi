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

#include    "FairyShogi/Win32/CommonResources.h"

#include    "FairyShogi/Common/HelperMacros.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

namespace  {

CONSTEXPR_VAR   LPCTSTR     s_tblEngines[]  =  {
    TEXT("Level 0"),
    TEXT("Level 1"),
    TEXT("Level 2"),
    TEXT("Level 3")
};

CONSTEXPR_VAR   int
NUM_ENGINE_TYPES    =  getArraySize(s_tblEngines);

CONSTEXPR_VAR   LPCTSTR     s_manNullName   =  "";

}   //  End of (Unnamed) namespace.

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
    : Super(),
      m_etPlayers(),
      m_pManNames(),
      m_engLevels(),
      m_fDiceRoll(),
      m_fEngStart(),
      m_strComment()
{
    //  デフォルトの設定値を用意する。  //
    this->m_etPlayers[Common::PLAYER_BLACK] = PLAYER_TYPE_MAN;
    this->m_etPlayers[Common::PLAYER_WHITE] = PLAYER_TYPE_COM;
    this->m_pManNames[Common::PLAYER_BLACK] = "No Name";
    this->m_pManNames[Common::PLAYER_WHITE] = "No Name";
    this->m_engLevels[Common::PLAYER_BLACK] = (NUM_ENGINE_TYPES - 1);
    this->m_engLevels[Common::PLAYER_WHITE] = (NUM_ENGINE_TYPES - 1);
    this->m_fDiceRoll[Common::PLAYER_BLACK] = OPERATION_AUTO;
    this->m_fDiceRoll[Common::PLAYER_WHITE] = OPERATION_AUTO;
    this->m_fEngStart[Common::PLAYER_BLACK] = OPERATION_MANUAL;
    this->m_fEngStart[Common::PLAYER_WHITE] = OPERATION_AUTO;
    this->m_strComment  =  "";
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

//----------------------------------------------------------------
//    ダイアログを初期化する。
//

BOOL
MatchDialog::initializeDialog()
{
    setupPlayerTypeOptions(
            IDD_RADIO_BLACK_MAN,
            IDD_RADIO_BLACK_COM,
            this->m_etPlayers[Common::PLAYER_BLACK]);
    setupPlayerTypeOptions(
            IDD_RADIO_WHITE_MAN,
            IDD_RADIO_WHITE_COM,
            this->m_etPlayers[Common::PLAYER_WHITE]);

    sendDialogItemMessage(
            IDD_COMBO_BLACK_MAN,
            CB_INSERTSTRING,
            0,
            reinterpret_cast<LPARAM>(s_manNullName));
    sendDialogItemMessage(
            IDD_COMBO_WHITE_MAN,
            CB_INSERTSTRING,
            0,
            reinterpret_cast<LPARAM>(s_manNullName));

    setDialogItemText(
            IDD_COMBO_BLACK_MAN,
            this->m_pManNames[Common::PLAYER_BLACK]);
    setDialogItemText(
            IDD_COMBO_WHITE_MAN,
            this->m_pManNames[Common::PLAYER_WHITE]);

    const   HWND    hCmbBlack   =  getDialogItem(IDD_COMBO_BLACK_COM);
    const   HWND    hCmbWhite   =  getDialogItem(IDD_COMBO_WHITE_COM);
    for ( int i = 0; i < NUM_ENGINE_TYPES; ++ i ) {
        ::SendMessage(
                hCmbBlack,  CB_INSERTSTRING,
                static_cast<WPARAM>(i),
                reinterpret_cast<LPARAM>(s_tblEngines[i])
        );
        ::SendMessage(
                hCmbWhite,  CB_INSERTSTRING,
                static_cast<WPARAM>(i),
                reinterpret_cast<LPARAM>(s_tblEngines[i])
        );
    }
    setComboSelectedIndex(
            IDD_COMBO_BLACK_COM,
            this->m_engLevels[Common::PLAYER_BLACK]);
    setComboSelectedIndex(
            IDD_COMBO_WHITE_COM,
            this->m_engLevels[Common::PLAYER_WHITE]);

    setupAutoManualOptions(
            IDD_RADIO_BLACK_DICE_MANUAL,
            IDD_RADIO_BLACK_DICE_AUTO,
            this->m_fDiceRoll[Common::PLAYER_BLACK]);

    setupAutoManualOptions(
            IDD_RADIO_WHITE_DICE_MANUAL,
            IDD_RADIO_WHITE_DICE_AUTO,
            this->m_fDiceRoll[Common::PLAYER_WHITE]);

    setupAutoManualOptions(
            IDD_RADIO_BLACK_THINK_MANUAL,
            IDD_RADIO_BLACK_THINK_AUTO,
            this->m_fEngStart[Common::PLAYER_BLACK]);

    setupAutoManualOptions(
            IDD_RADIO_WHITE_THINK_MANUAL,
            IDD_RADIO_WHITE_THINK_AUTO,
            this->m_fEngStart[Common::PLAYER_WHITE]);

    return ( TRUE );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    ダイスの自動／手動フラグを取得する。
//

MatchDialog::AutoManual
MatchDialog::getDiceRollMode(
        const  PlayerIndex  cPlayer)  const
{
    return ( this->m_fDiceRoll[cPlayer] );
}

//----------------------------------------------------------------
//    ダイスの自動／手動フラグを設定する。
//

ErrCode
MatchDialog::setDiceRollMode(
        const  PlayerIndex  cPlayer,
        const  AutoManual   valNew)
{
    this->m_fDiceRoll[cPlayer]  = valNew;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    思考エンジンのレベルを取得する。
//

MatchDialog::EngineLevel
MatchDialog::getEngineLevel(
        const  PlayerIndex  cPlayer)  const
{
    return ( this->m_engLevels[cPlayer] );
}

//----------------------------------------------------------------
//    思考エンジンのレベルを設定する。
//

ErrCode
MatchDialog::setEngineLevel(
        const  PlayerIndex  cPlayer,
        const  EngineLevel  valNew)
{
    this->m_engLevels[cPlayer]  = valNew;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    エンジン思考開始の自動／手動フラグを取得する。
//

MatchDialog::AutoManual
MatchDialog::getEngineStart(
        const  PlayerIndex  cPlayer)  const
{
    return ( this->m_fEngStart[cPlayer] );
}

//----------------------------------------------------------------
//    エンジン思考開始の自動／手動フラグを設定する。
//

ErrCode
MatchDialog::setEngineStart(
        const  PlayerIndex  cPlayer,
        const  AutoManual   valNew)
{
    this->m_fEngStart[cPlayer]  = valNew;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    対局のコメントを取得する。
//

const  std::string  &
MatchDialog::getMatchComment()  const
{
    return ( this->m_strComment );
}

//----------------------------------------------------------------
//    対局のコメントを設定する。
//

ErrCode
MatchDialog::setMatchComment(
        const  std::string  &valNew)
{
    this->m_strComment  = valNew;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    プレーヤーの名前を取得する。
//

const  std::string  &
MatchDialog::getPlayerName(
        const  PlayerIndex  cPlayer)  const
{
    return ( this->m_pManNames[cPlayer] );
}

//----------------------------------------------------------------
//    プレーヤーの名前を設定する。
//

ErrCode
MatchDialog::setPlayerName(
        const  PlayerIndex  cPlayer,
        const  std::string  &valNew)
{
    this->m_pManNames[cPlayer]  = valNew;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    プレーヤーのタイプを取得する。
//

MatchDialog::PlayerType
MatchDialog::getPlayerType(
        const  PlayerIndex  cPlayer)  const
{
    return ( this->m_etPlayers[cPlayer] );
}

//----------------------------------------------------------------
//    プレーヤーのタイプを設定する。
//

ErrCode
MatchDialog::setPlayerType(
        const  PlayerIndex  cPlayer,
        const  PlayerType   valNew)
{
    this->m_etPlayers[cPlayer]  = valNew;
    return ( ERR_SUCCESS );
}

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
    case  WM_INITDIALOG:
        return ( initializeDialog() );
        break;
    default:
        return ( FALSE );
    }

    return ( TRUE );
}

//----------------------------------------------------------------
//    ダイアログの内容を変数に保存する。
//

Boolean
MatchDialog::saveDialogItems()
{
    this->m_etPlayers[Common::PLAYER_BLACK] = readPlayerTypeOption(
            IDD_RADIO_BLACK_MAN,
            IDD_RADIO_BLACK_COM,
            this->m_etPlayers[Common::PLAYER_BLACK]);
    this->m_etPlayers[Common::PLAYER_WHITE] = readPlayerTypeOption(
            IDD_RADIO_WHITE_MAN,
            IDD_RADIO_WHITE_COM,
            this->m_etPlayers[Common::PLAYER_WHITE]);

    getDialogItemText(
            IDD_COMBO_BLACK_MAN,
            this->m_pManNames[Common::PLAYER_BLACK]);
    getDialogItemText(
            IDD_COMBO_WHITE_MAN,
            this->m_pManNames[Common::PLAYER_WHITE]);

    this->m_engLevels[Common::PLAYER_BLACK]
            = getComboSelectedIndex(IDD_COMBO_BLACK_COM);
    this->m_engLevels[Common::PLAYER_WHITE]
            = getComboSelectedIndex(IDD_COMBO_WHITE_COM);

    this->m_fDiceRoll[Common::PLAYER_BLACK] = readAutoManualOption(
            IDD_RADIO_BLACK_DICE_MANUAL,
            IDD_RADIO_BLACK_DICE_AUTO,
            this->m_fDiceRoll[Common::PLAYER_BLACK]);

    this->m_fDiceRoll[Common::PLAYER_WHITE] = readAutoManualOption(
            IDD_RADIO_WHITE_DICE_MANUAL,
            IDD_RADIO_WHITE_DICE_AUTO,
            this->m_fDiceRoll[Common::PLAYER_WHITE]);

    this->m_fEngStart[Common::PLAYER_BLACK] = readAutoManualOption(
            IDD_RADIO_BLACK_THINK_MANUAL,
            IDD_RADIO_BLACK_THINK_AUTO,
            this->m_fEngStart[Common::PLAYER_BLACK]);

    this->m_fEngStart[Common::PLAYER_WHITE] = readAutoManualOption(
            IDD_RADIO_WHITE_THINK_MANUAL,
            IDD_RADIO_WHITE_THINK_AUTO,
            this->m_fEngStart[Common::PLAYER_WHITE]);

    return ( BOOL_TRUE );
}

//========================================================================
//
//    Protected Member Functions (Virtual Functions).
//

//----------------------------------------------------------------
//    ボタンをクリックした時のイベントハンドラ。
//

BOOL
MatchDialog::onCommand(
        const   UINT    wID,
        const   UINT    wNotifyCode,
        const   HWND    hWndControl)
{
    switch ( wID ) {
    case  IDOK:
        saveDialogItems();
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

//----------------------------------------------------------------
//    ラジオボタンの設定内容を取得する。
//

MatchDialog::AutoManual
MatchDialog::readAutoManualOption(
        const  ComponentID  idManual,
        const  ComponentID  idAuto,
        const  AutoManual   defVal)
{
    if ( isButtonChecked(idManual) == BST_CHECKED ) {
        return ( OPERATION_MANUAL );
    }
    if ( isButtonChecked(idAuto)   == BST_CHECKED ) {
        return ( OPERATION_AUTO );
    }
    return ( defVal );
}

//----------------------------------------------------------------
//    ラジオボタンの設定内容を取得する。
//

MatchDialog::PlayerType
MatchDialog::readPlayerTypeOption(
        const  ComponentID  idMan,
        const  ComponentID  idCom,
        const  PlayerType   defVal)
{
    if ( isButtonChecked(idMan) == BST_CHECKED ) {
        return ( PLAYER_TYPE_MAN );
    }
    if ( isButtonChecked(idCom) == BST_CHECKED ) {
        return ( PLAYER_TYPE_COM );
    }
    return ( defVal );
}

//----------------------------------------------------------------
//    設定をラジオボタンに反映する。
//

template  <typename  TValueType>
inline  Boolean
MatchDialog::setupRadioButton(
        const  ComponentID  idItem,
        const  TValueType   curVal,
        const  TValueType   btnVal)
{
    sendDialogItemMessage(
            idItem,     BM_SETCHECK,
            ((curVal == btnVal) ? BST_CHECKED : BST_UNCHECKED),
            0);
    return ( BOOL_TRUE );
}

//----------------------------------------------------------------
//    ダイスの設定をラジオボタンに反映する。
//

Boolean
MatchDialog::setupAutoManualOptions(
        const  ComponentID  idManual,
        const  ComponentID  idAuto,
        const  AutoManual   curVal)
{
    setupRadioButton(idManual,  curVal,  OPERATION_MANUAL);
    setupRadioButton(idAuto,    curVal,  OPERATION_AUTO  );
    return ( BOOL_TRUE );
}

//----------------------------------------------------------------
//    設定をラジオボタンに反映する。
//

Boolean
MatchDialog::setupPlayerTypeOptions(
        const  ComponentID  idMan,
        const  ComponentID  idCom,
        const  PlayerType   curVal)
{
    setupRadioButton(idMan,  curVal,  PLAYER_TYPE_MAN);
    setupRadioButton(idCom,  curVal,  PLAYER_TYPE_COM);
    return ( BOOL_TRUE );
}

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
