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

#include    <ostream>
#include    <stdlib.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

namespace  {

/**
**    棋譜に表示する駒の名称。
**/

constexpr   const   char  *
s_tblPieceName[]    = {
    "",
    "+Pawn",  "+Silver",  "+Gold",  "+Bishop",  "+Rook",  "+King",
    "+Tokin", "+NariGin", "+Uma",   "+Ryu",
    "-Pawn",  "-Silver",  "-Gold",  "-Bishop",  "-Rook",  "-King",
    "-Tokin", "-NariGin", "-Uma",   "-Ryu"
};

/**
**    持ち駒の名前。
**/

CONSTEXPR_VAR   const   char
s_tblHandName[Game::BoardState::NUM_HAND_TYPES] = {
    'W',
    'P',  'S',  'G',  'B',  'R',  'K',
    'p',  's',  'g',  'b',  'r',  'k'
};

using   Game::BoardState;

CONSTEXPR_VAR   PieceIndex
s_tblHandConv[BoardState::NUM_HAND_TYPES]   = {
    BoardState::FIELD_EMPTY_SQUARE,

    BoardState::FIELD_BLACK_PAWN,
    BoardState::FIELD_BLACK_SILVER,
    BoardState::FIELD_BLACK_GOLD,
    BoardState::FIELD_BLACK_BISHOP,
    BoardState::FIELD_BLACK_ROOK,
    BoardState::FIELD_BLACK_KING,

    BoardState::FIELD_WHITE_PAWN,
    BoardState::FIELD_WHITE_SILVER,
    BoardState::FIELD_WHITE_GOLD,
    BoardState::FIELD_WHITE_BISHOP,
    BoardState::FIELD_WHITE_ROOK,
    BoardState::FIELD_WHITE_KING
};

CONSTEXPR_VAR   const   int
s_tblPromotion[]    = {
    0,
    BoardState::FIELD_BLACK_PR_PAWN,
    BoardState::FIELD_BLACK_PR_SILVER,
    BoardState::FIELD_BLACK_GOLD,
    BoardState::FIELD_BLACK_HORSE,
    BoardState::FIELD_BLACK_DRAGON,
    BoardState::FIELD_BLACK_KING,
    BoardState::FIELD_BLACK_PR_PAWN,
    BoardState::FIELD_BLACK_PR_SILVER,
    BoardState::FIELD_BLACK_HORSE,
    BoardState::FIELD_BLACK_DRAGON,

    BoardState::FIELD_WHITE_PR_PAWN,
    BoardState::FIELD_WHITE_PR_SILVER,
    BoardState::FIELD_WHITE_GOLD,
    BoardState::FIELD_WHITE_HORSE,
    BoardState::FIELD_WHITE_DRAGON,
    BoardState::FIELD_WHITE_KING,
    BoardState::FIELD_WHITE_PR_PAWN,
    BoardState::FIELD_WHITE_PR_SILVER,
    BoardState::FIELD_WHITE_HORSE,
    BoardState::FIELD_WHITE_DRAGON,
};

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    GameController  class.
//

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
      m_curDice(0)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

GameController::~GameController()
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
//    コンピュータの思考を開始する。
//

ErrCode
GameController::computeBestAction(
        ActionView  &actRet)
{
    return ( startThinking(actRet) );
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
        decodeActionData( SCF_NORMAL_SHOW, (* itrHead), &actView );
        if ( (actView.xPlayNewCol) >= curDice ) {
            break;
        }
    }

    size_t      cntLegs = 0;
    for ( ActIter itr = itrHead; itr != itrEnd; ++ itr ) {
        //  ダイスの目を内部形式に揃えているので、  //
        //  比較の時は、座標を反転させないで行う。  //
        decodeActionData( SCF_NORMAL_SHOW, (* itr), &actView );
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
        decodeActionData( this->m_flgShow, (* itr), &actView);
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

    retErr  =  BoardState::encodeActionData(actBwd, &actData);
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

    retErr  =  BoardState::encodeActionData(actFwd, &actData);
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
    return ( this->m_gcBoard.resetGameBoard() );
}

//----------------------------------------------------------------
//    コンピュータの思考を開始する。
//

ErrCode
GameController::startThinking(
        ActionView  &actRet)
{
    ActionViewList  actList;

    makeLegalActionList(0,  this->m_curDice,  actList);
    const  int  numAct  = actList.size();
    if ( numAct == 0 ) {
        return ( ERR_ILLEGAL_ACTION );
    }
    if ( numAct == 1 ) {
        actRet  =  actList[0];
        return ( ERR_SUCCESS );
    }

    BoardState      bsClone;
    ActionData      actData;
    ActionDataList  vActs;
    int             idxMin  =  0;
    double          scrMin  =  100000;

    for ( int r = 0;  r < numAct;  ++ r ) {
        bsClone.cloneFrom(this->m_gcBoard);
        BoardState::encodeActionData(actList[r], &actData);
        bsClone.playForward(actData);

        vActs.clear();
        bsClone.makeLegalActionList(this->m_curTurn ^ 1,  0,  vActs);
        size_t  cntLegs =  vActs.size();
        if ( cntLegs == 0 ) {
            idxMin  =  r;
            scrMin  =  0;
            break;
        }

        BoardState::TBitBoard   bbCheck;
        if ( bsClone.isCheckState(this->m_curTurn ^ 1, bbCheck) > 0 ) {
            cntLegs *= 3;
        }

        const  double  dblRnd   =  (rand() * 4.0 / RAND_MAX);
        const  size_t  scrCur   =  (cntLegs) * (dblRnd + 8);
        if ( scrCur < scrMin ) {
            idxMin  =  r;
            scrMin  =  cntLegs;
        }
    }

    actRet  =  actList[idxMin];

    return ( ERR_SUCCESS );
}


//----------------------------------------------------------------
//    表示用棋譜データの内容をストリームに出力する。
//

std::ostream  &
GameController::writeActionView(
        const  ActionView   &actView,
        std::ostream        &outStr)
{
    outStr  <<  (actView.xDispNewCol)
            <<  (actView.yDispNewRow)
            <<  ' '
            <<  s_tblPieceName[actView.fpAfter];
    if ( (actView.hpiDrop) == 0 ) {
        outStr  <<  " ("
                <<  (actView.xDispOldCol)
                <<  (actView.yDispOldRow)
                <<  ")";
        if ( (actView.fpAfter) != (actView.fpMoved) ) {
            outStr  <<  " (PROMOTE)";
        }
    } else {
        outStr  <<  " (PUT)";
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

    size_t          idx     = 0;
    const  ActIter  itrEnd  = obj.end();
    for ( ActIter itr = obj.begin(); itr != itrEnd; ++ itr, ++ idx )
    {
        this->m_gcBoard.decodeActionData( *itr, &actList[idx] );
    }

    return ( ERR_SUCCESS );
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
        return ( vCons < 6 ? (6 - vCons) : 6 );
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
