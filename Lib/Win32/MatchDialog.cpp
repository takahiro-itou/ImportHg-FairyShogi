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
    : Super(),
      m_playTypes(),
      m_fDiceRoll(),
      m_fEngStart()
{
    //  デフォルトの設定値を用意する。  //
    this->m_playTypes[Common::PLAYER_BLACK] = 0;
    this->m_playTypes[Common::PLAYER_WHITE] = 3;
    this->m_fDiceRoll[Common::PLAYER_BLACK] = OPERATION_AUTO;
    this->m_fDiceRoll[Common::PLAYER_WHITE] = OPERATION_AUTO;
    this->m_fEngStart[Common::PLAYER_BLACK] = OPERATION_MANUAL;
    this->m_fEngStart[Common::PLAYER_WHITE] = OPERATION_AUTO;
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
    setupAutoManualOptions(
            IDD_RADIO_BLACK_DICE_AUTO,
            IDD_RADIO_BLACK_DICE_MANUAL,
            this->m_fDiceRoll[Common::PLAYER_BLACK]);
    setupAutoManualOptions(
            IDD_RADIO_WHITE_DICE_AUTO,
            IDD_RADIO_WHITE_DICE_MANUAL,
            this->m_fDiceRoll[Common::PLAYER_WHITE]);

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
//    プレーヤーのタイプを取得する。
//

MatchDialog::PlayerType
MatchDialog::getPlayerType(
        const  PlayerIndex  cPlayer)  const
{
    return ( this->m_playTypes[cPlayer] );
}

//----------------------------------------------------------------
//    プレーヤーのタイプを設定する。
//

ErrCode
MatchDialog::setPlayerType(
        const  PlayerIndex  cPlayer,
        const  PlayerType   valNew)
{
    this->m_playTypes[cPlayer]  = valNew;
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

//----------------------------------------------------------------
//    設定をラジオボタンに反映する。
//

Boolean
MatchDialog::setupAutoManualOption(
        const  ComponentID  idItem,
        const  AutoManual   curVal,
        const  AutoManual   btnVal)
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
        const  ComponentID  idAuto,
        const  ComponentID  idMan,
        const  AutoManual   curVal)
{
    setupAutoManualOption(idAuto, curVal, OPERATION_AUTO);
    setupAutoManualOption(idMan,  curVal, OPERATION_MANUAL);
    return ( BOOL_TRUE );
}

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
