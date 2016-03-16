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
**      An Implementation of GameController class.
**
**      @file       Interface/GameController.cpp
**/

#include    "FairyShogi/Interface/GameController.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/ViewBuffer.h"

#include    "FairyShogi/Engine/EngineBase.h"

#include    <ostream>
#include    <stdlib.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

namespace  {

/**
**    棋譜に表示する駒の名称。
**/

CONSTEXPR_VAR   const   char  *
s_tblPieceCsaName[Common::NUM_FIELD_PIECE_TYPES]   =  {
    "",
    "FU",  "KY",  "KE",  "GI",  "KI",  "KA",  "HI",  "OU",
    "TO",  "NY",  "NK",  "NG",  "UM",  "RY",
    "FU",  "KY",  "KE",  "GI",  "KI",  "KA",  "HI",  "OU",
    "TO",  "NY",  "NK",  "NG",  "UM",  "RY"
};

CONSTEXPR_VAR   const   char  *
s_tblPieceSfenName[Common::NUM_FIELD_PIECE_TYPES]  =  {
    "  ",
    " P",  " L",  " N",  " S",  " G",  " B",  " R",  " K",
    "+P",  "+L",  "+N",  "+S",         "+B",  "+R",
    " p",  " l",  " n",  " s",  " g",  " b",  " r",  " k",
    "+p",  "+l",  "+n",  "+s",         "+b",  "+r"
};

CONSTEXPR_VAR   const   char  *
s_tblHandSfenName [Common::NUM_HAND_TYPES]  =  {
    "WALL",
    "P", "L", "N", "S", "G", "B", "R", "K",
    "p", "l", "n", "s", "g", "b", "r", "k"
};

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    GameController  class.
//

const   Common::EFieldPiece
GameController::s_tblHandConv[Common::NUM_HAND_TYPES]   =
{
    Common::FIELD_EMPTY_SQUARE,

    Common::FIELD_BLACK_PAWN,
    Common::FIELD_BLACK_LANCE,
    Common::FIELD_BLACK_KNIGHT,
    Common::FIELD_BLACK_SILVER,
    Common::FIELD_BLACK_GOLD,
    Common::FIELD_BLACK_BISHOP,
    Common::FIELD_BLACK_ROOK,
    Common::FIELD_BLACK_KING,

    Common::FIELD_WHITE_PAWN,
    Common::FIELD_WHITE_LANCE,
    Common::FIELD_WHITE_KNIGHT,
    Common::FIELD_WHITE_SILVER,
    Common::FIELD_WHITE_GOLD,
    Common::FIELD_WHITE_BISHOP,
    Common::FIELD_WHITE_ROOK,
    Common::FIELD_WHITE_KING
};

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

GameController::GameController()
    : m_gcBoard(),
      m_actList(),
      m_flgShow(SCF_NORMAL_SHOW),
      m_curTurn(0),
      m_curDice(Common::DICE_DEFAULT_VALUE),
      m_ptrEngines(),
      m_fStatus(Common::GAME_IS_RUNNING),
      m_gResult(Common::GAME_RESULT_DRAW)
{
    for ( PlayerIndex pi = 0; pi < Common::NUM_PLAYERS; ++ pi ) {
        this->m_ptrEngines[pi]  =  TEngineBase::createEngine("default");
    }
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

GameController::~GameController()
{
    for ( PlayerIndex pi = 0; pi < Common::NUM_PLAYERS; ++ pi ) {
        TEngineBase::destroyEngine( this->m_ptrEngines[pi] );
        this->m_ptrEngines[pi]  =  (nullptr);
    }
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
//    コンピュータの思考を開始する。
//

ErrCode
GameController::computeBestAction(
        ActionView  &actRet)
{
    Common::ViewBuffer  vbCur;
    ErrCode             retErr  =  ERR_SUCCESS;

    const  TConstraint  ccDice  =  convertConstraintCoord(
            this->m_flgShow,  (this->m_curDice) );

    this->m_gcBoard.copyToViewBuffer(vbCur);
    retErr  =  this->m_ptrEngines[this->m_curTurn]->computeBestAction(
                    vbCur,   this->m_curTurn,
                    ccDice,  actRet);

    setupActionDisplayCoord( this->m_flgShow, &actRet );

    return ( retErr );
}

//----------------------------------------------------------------
//    王手が掛かっているかどうかを判定する。
//

Boolean
GameController::isCheckState(
        const  PlayerIndex  dPlayer)  const
{
    Game::BoardState::TBitBoard     bbFrom;
    const  size_t
        numChk  = this->m_gcBoard.isCheckState(dPlayer, bbFrom);
    if ( numChk >= 1 ) {
        return ( BOOL_TRUE );
    }
    return ( BOOL_FALSE );
}

//----------------------------------------------------------------
//    現在の局面の合法手を列挙する。
//

ErrCode
GameController::makeLegalActionList(
        const   ActionFlag  fLegals,
        const   int         vCons,
        ActionViewList      &actList)  const
{
    typedef     ActionDataList::const_iterator      ActIter;

    //  まず、全ての合法手を列挙する。  //
    ActionDataList  vActs;
    const  ErrCode
        retErr  = this->m_gcBoard.makeLegalActionList(
                        this->m_curTurn,  fLegals,  vActs);

    actList.clear();
    actList.reserve( vActs.size() );

    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    const  ActIter  itrEnd  = vActs.end();
    ActIter         itrHead = vActs.begin();
    ActIter         itrTail = itrEnd;

    //  合法手のリストは、内部の座標系で昇順ソートされている。  //
    //  従って、ダイスの目を内部形式に合わせてから比較を行う。  //
    const  TConstraint  curDice = convertConstraintCoord(
            this->m_flgShow, (vCons < 0 ? (this->m_curDice) : vCons) );

    ActionView      actView;
    for ( ; itrHead != itrEnd; ++ itrHead ) {
        //  ダイスの目を内部形式に揃えているので、  //
        //  比較の時は、座標を反転させないで行う。  //
        //  表示用座標ではなく、内部用座標で比較。  //
        Game::BoardState::decodeActionData( (* itrHead),  &actView );
        if ( (actView.xPlayNewCol) >= curDice ) {
            break;
        }
    }

    size_t      cntLegs = 0;
    for ( ActIter itr = itrHead; itr != itrEnd; ++ itr ) {
        //  ダイスの目を内部形式に揃えているので、  //
        //  比較の時は、座標を反転させないで行う。  //
        //  表示用座標ではなく、内部用座標で比較。  //
        Game::BoardState::decodeActionData( (* itr),  &actView );
        if ( (actView.xPlayNewCol) != curDice ) {
            itrTail = itr;
            break;
        }
        if ( (actView.fLegals) == Common::ALF_LEGAL_ACTION ) {
            ++  cntLegs;
        }
    }
    if ( (cntLegs == 0) ) {
        //  指定した条件で合法手がない時は、何でもできる。  //
        itrHead = vActs.begin();
        itrTail = itrEnd;
    }

    for ( ActIter itr = itrHead; itr != itrTail; ++ itr ) {
        //  今度は表示を行うので、必要なら座標を反転する。  //
        decodeActionData( this->m_flgShow,  (* itr),  &actView);
        actList.push_back(actView);
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    最後に入力した指し手で盤面を戻す。
//

ErrCode
GameController::playBackward()
{
    if ( (this->m_actList.empty()) ) {
        return ( ERR_INVALID_COMMAND );
    }

    const  ActionData  actData  =  (this->m_actList.back());

    ErrCode     retErr  = ERR_SUCCESS;
    retErr  =  this->m_gcBoard.playBackward(actData);

    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    this->m_actList.pop_back();
    return ( retErr );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を戻す。
//

ErrCode
GameController::playBackward(
        const  ActionView   &actBwd)
{
    ErrCode     retErr  = ERR_SUCCESS;
    ActionData  actData;

    retErr  =  Game::BoardState::encodeActionData(actBwd, &actData);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( this->m_gcBoard.playBackward(actData) );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を進める。
//

ErrCode
GameController::playForward(
        const  ActionView   &actFwd)
{
    ErrCode     retErr  = ERR_SUCCESS;
    ActionData  actData;

    retErr  =  Game::BoardState::encodeActionData(actFwd, &actData);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    retErr  =  this->m_gcBoard.playForward(actData);
    if ( retErr == ERR_SUCCESS ) {
        this->m_actList.push_back(actData);
    }

    return ( retErr );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
GameController::resetGame()
{
    const  ErrCode  retErr  =  this->m_gcBoard.resetGameBoard();

    this->m_fStatus         =  Common::GAME_IS_RUNNING;
    this->m_gResult         =  Common::GAME_RESULT_DRAW;

    return ( retErr );
}

//----------------------------------------------------------------
//    コンピュータの思考エンジンを指定する。
//

ErrCode
GameController::setComputerEngine(
        const  PlayerIndex  pIndex,
        const  std::string  &engName)
{
    TEngineBase::destroyEngine( this->m_ptrEngines[pIndex] );
    this->m_ptrEngines[pIndex]  =  TEngineBase::createEngine(engName);

    if ( (this->m_ptrEngines[pIndex]) == (nullptr) ) {
        return ( ERR_FAILURE );
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ゲームの状態と勝敗を判定する。
//

GameStateFlags
GameController::testGameStateResult()
{
    GameResultVals  resVal  =  Common::GAME_RESULT_DRAW;
    GameStateFlags  fgStat  =  Common::GAME_IS_RUNNING;

    Game::BoardState::TBitBoard     bbCheck;

    ActionDataList  vActs;

    //  現局面での先手の合法手を確認する。  //
    vActs.clear();
    this->m_gcBoard.makeLegalActionList(
            Common::PLAYER_BLACK,  Common::ALF_LEGAL_ACTION,  vActs);
    if ( vActs.empty() ) {
        //  先手に合法手が存在しない。  //
        this->m_gcBoard.isCheckState(Common::PLAYER_WHITE,  bbCheck);
        if ( bbCheck.empty() ) {
            //  王手が掛かっていないので、ステイルメイトである。    //
            resVal  |=  Common::GAME_BLACK_WON_STALEMATE;
        } else {
            //  王手が掛かっていて合法手が無いのでチェックメイト。  //
            resVal  |=  Common::GAME_WHITE_WON_CHECKMATE;
        }
        fgStat  =  Common::GAME_IS_OVER;
    }

    //  現局面での先手の合法手を確認する。  //
    vActs.clear();
    this->m_gcBoard.makeLegalActionList(
            Common::PLAYER_WHITE,  Common::ALF_LEGAL_ACTION,  vActs);
    if ( vActs.empty() ) {
        //  後手に合法手が存在しない。  //
        this->m_gcBoard.isCheckState(Common::PLAYER_WHITE,  bbCheck);
        if ( bbCheck.empty() ) {
            //  王手が掛かっていないので、ステイルメイトである。    //
            resVal  |=  Common::GAME_WHITE_WON_STALEMATE;
        } else {
            //  王手が掛かっていて合法手が無いのでチェックメイト。  //
            resVal  |=  Common::GAME_BLACK_WON_CHECKMATE;
        }
        fgStat  =  Common::GAME_IS_OVER;
    }

    this->m_fStatus = fgStat;
    this->m_gResult = resVal;
    return ( fgStat );
}

//----------------------------------------------------------------
//    表示用棋譜データの内容をストリームに出力する。
//

std::ostream  &
GameController::writeActionViewSfen(
        const  ActionView   &actView,
        const  Boolean      flgName,
        std::ostream        &outStr)  const
{
    if ( actView.hpiDrop == Common::HAND_EMPTY_PIECE ) {
        //  駒を移動させた時は、移動元、移動先の座標。  //
        outStr  <<  (actView.xDispOldCol)   <<  (actView.yDispOldRow)
                <<  (actView.xDispNewCol)   <<  (actView.yDispNewRow);
        if ( (actView.fpAfter) != (actView.fpMoved) ) {
            outStr  <<  '+';
        } else {
            outStr  <<  ' ';
        }
    } else {
        //  持ち駒を打った時は、持ち駒、移動先の座標。  //
        outStr  <<  (s_tblHandSfenName[actView.hpiDrop])
                <<  '*'
                <<  (actView.xDispNewCol)   <<  (actView.yDispNewRow)
                <<  ' ';
    }

    //  移動した駒を表示する。  //
    if ( flgName ) {
        outStr  <<  (s_tblPieceSfenName[actView.fpMoved])   <<  ' ';
        if ( (actView.fpCatch) != Common::FIELD_EMPTY_SQUARE )  {
           outStr   <<  "(x"
                    <<  s_tblPieceSfenName[actView.fpCatch]
                    <<   ") ";
        } else {
            outStr  <<  "(x--) ";
        }
    }

    return ( outStr );
}

//----------------------------------------------------------------
//    表示用棋譜データの内容をストリームに出力する。
//

std::ostream  &
GameController::writeActionViewCsa(
        const  ActionView   &actView,
        std::ostream        &outStr)  const
{
    if ( actView.hpiDrop == Common::HAND_EMPTY_PIECE ) {
        //  駒を移動させた時は、移動元、移動先、移動後の駒。    //
        outStr  <<  (actView.xDispOldCol)   <<  (actView.yDispOldRow)
                <<  (actView.xDispNewCol)   <<  (actView.yDispNewRow)
                <<  s_tblPieceCsaName[actView.fpAfter];
    } else {
        //  持ち駒を打った時は、駒台(00)、移動先、移動後の駒。  //
        outStr  <<  "00"
                <<  (actView.xDispNewCol)   <<  (actView.yDispNewRow)
                <<  s_tblPieceCsaName[actView.fpAfter];
    }

    return ( outStr );
}

//----------------------------------------------------------------
//    棋譜データを表示用に変換する。
//

ErrCode
GameController::writeActionList(
        ActionViewList  &actList)  const
{
    typedef     ActionDataList::const_iterator  ActIter;

    const  ActionDataList  &obj = (this->m_actList);

    actList.clear();
    actList.resize(obj.size());

    ErrCode         retErr  =  ERR_SUCCESS;
    ErrCode         tmpErr;
    size_t          idx     =  0;
    const  ActIter  itrEnd  =  obj.end();
    for ( ActIter itr = obj.begin(); itr != itrEnd; ++ itr, ++ idx )
    {
        tmpErr  = decodeActionData(this->m_flgShow, (* itr), &actList[idx]);
        if ( tmpErr != ERR_SUCCESS ) {
            retErr  =  tmpErr;
        }
    }

    return ( retErr );
}

//----------------------------------------------------------------
//    現在の盤面を表示用バッファにコピーする。
//

ErrCode
GameController::writeToViewBuffer(
        Common::ViewBuffer  &bufView)  const
{
    return ( this->m_gcBoard.copyToViewBuffer(bufView) );
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    指し手の表示用形式を比較して、等しいかどうかを返す。
//

bool
GameController::isEquals(
        const  ActionView  &avLhs,
        const  ActionView  &avRhs)
{
    if (       ( (avLhs.xPlayNewCol) != (avRhs.xPlayNewCol) )
            || ( (avLhs.yPlayNewRow) != (avRhs.yPlayNewRow) )
            || ( (avLhs.xPlayOldCol) != (avRhs.xPlayOldCol) )
            || ( (avLhs.yPlayOldRow) != (avRhs.yPlayOldRow) )
            || ( (avLhs.fpMoved) != (avRhs.fpMoved) )
            || ( (avLhs.fpAfter) != (avRhs.fpAfter) )
            || ( (avLhs.hpiDrop) != (avRhs.hpiDrop) )
            || ( (avLhs.fpCatch) != (avRhs.fpCatch) )
    )
    {
        return ( false );
    }
    return ( true );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    現在の盤面の状態を取得する。
//

const   Game::BoardState  &
GameController::getBoardState()  const
{
    return ( this->m_gcBoard );
}

//----------------------------------------------------------------
//    合法手の制約を取得する。
//

GameController::TConstraint
GameController::getConstraint()  const
{
    return ( this->m_curDice );
}

//----------------------------------------------------------------
//    合法手の制約を指定する。
//

ErrCode
GameController::setConstraint(
        const  TConstraint  vCons)
{
    this->m_curDice = vCons;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    現在の手番を持つプレーヤーを取得する。
//

PlayerIndex
GameController::getCurrentPlayer()  const
{
    return ( this->m_curTurn );
}

//----------------------------------------------------------------
//    現在の手番を持つプレーヤーを設定する。
//

ErrCode
GameController::setCurrentPlayer(
        const  PlayerIndex  cPlayer)
{
    this->m_curTurn = cPlayer;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    指定した座標にある駒を取得する。
//

Common::EFieldPiece
GameController::getFieldPiece(
        const  PosCol   xCol,
        const  PosRow   yRow)  const
{
    return ( this->m_gcBoard.decodeFieldPiece(xCol, yRow) );
}

//----------------------------------------------------------------
//    ゲームの勝敗を取得する。
//

GameResultVals
GameController::getGameResult()  const
{
    return ( this->m_gResult );
}

//----------------------------------------------------------------
//    現在のゲームの状態を取得する。
//

GameStateFlags
GameController::getGameStateFlags()  const
{
    return ( this->m_fStatus );
}

//----------------------------------------------------------------
//    手番を次のプレーヤーに設定する。
//

PlayerIndex
GameController::setPlayerToNext()
{
    return ( (this->m_curTurn) ^= Common::PLAYER_OPPOSITE );
}

//----------------------------------------------------------------
//    現在の盤面の表示フラグを取得する。
//

GameController::ShowCoordFlags
GameController::getShowFlag()  const
{
    return ( this->m_flgShow );
}

//----------------------------------------------------------------
//    盤面の表示フラグを設定する。
//

ErrCode
GameController::setShowFlag(
        const   ShowCoordFlags  scFlag)

{
    this->m_flgShow = scFlag;
    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    入力したダイスの出目を、内部処理用に変換する。
//

GameController::TConstraint
GameController::convertConstraintCoord(
        const   ShowCoordFlags  flgShow,
        const   TConstraint     vCons)
{
    if ( (flgShow) & SCF_FLIP_COLUMNS ) {
        //  水平方向の座標を反転させる。ただし六を除く。    //
        //  つまり、123456 -> 543216 となるように変換する。 //
        return ( vCons < Common::DICE_ANY_MOVE
                 ?  (Common::DICE_MAX_VALUE - vCons)
                 :  Common::DICE_ANY_MOVE );
    }

    //  水平方向の座標をそのまま使う。      //
    return ( vCons );
}

//----------------------------------------------------------------
//    指し手の内部形式を表示用データに変換する。
//

ErrCode
GameController::decodeActionData(
        const   ShowCoordFlags  flgShow,
        const   ActionData   &  actData,
        ActionView  *  const    pvAct)
{
    //  指し手の内部形式を表示用データに変換。  //
    const  ErrCode
        retErr  = Game::BoardState::decodeActionData( actData, pvAct );
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( setupActionDisplayCoord(flgShow, pvAct) );
}

//----------------------------------------------------------------
//    指し手データの内、表示用座標を設定する。
//

ErrCode
GameController::setupActionDisplayCoord(
        const   ShowCoordFlags  flgShow,
        ActionView  *  const    pvAct)
{
    //  表示フラグを確認して座標の調整を行う。  //
    if ( (flgShow) & SCF_FLIP_COLUMNS ) {
        //  水平方向の座標を反転させる。    //
        pvAct->xDispNewCol  = (5 + 1 - (pvAct->xPlayNewCol));
        pvAct->xDispOldCol  = (5 + 1 - (pvAct->xPlayOldCol));
    } else {
        pvAct->xDispNewCol  = (pvAct->xPlayNewCol);
        pvAct->xDispOldCol  = (pvAct->xPlayOldCol);
    }

    //  垂直方向の座標はそのまま。  //
    pvAct->yDispNewRow  =  (pvAct->yPlayNewRow);
    pvAct->yDispOldRow  =  (pvAct->yPlayOldRow);

    return ( ERR_SUCCESS );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
