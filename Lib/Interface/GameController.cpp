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
//    現在の局面の合法手を列挙する。
//

ErrCode
GameController::makeLegalActionList(
        ActionList  &actList)  const
{
    return ( this->m_gcBoard.makeLegalActionList(actList) );
}

//----------------------------------------------------------------
//    駒を移動する指し手を入力して盤面を進める。
//

ErrCode
GameController::playMoveAction(
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        const  PieceIndex   flgProm)
{
    const  Game::BoardState::ActionData
        act = this->m_gcBoard.encodeMoveAction(
                    xOldCol, yOldRow, xNewCol, yNewRow, flgProm);

    const  ErrCode  retErr  = this->m_gcBoard.playForward(act);

    if ( retErr == ERR_SUCCESS ) {
        this->m_actList.push_back(act);
    }

    return ( retErr );
}

//----------------------------------------------------------------
//    持ち駒を打つ指し手を入力して盤面を進める。
//

ErrCode
GameController::playPutAction(
        const  PosCol       xPutCol,
        const  PosRow       yPutRow,
        const  PieceIndex   pHand)
{
    const  Game::BoardState::ActionData
        act = this->m_gcBoard.encodePutAction(
                    xPutCol, yPutRow, pHand);

    const  ErrCode  retErr  = this->m_gcBoard.playForward(act);

    if ( retErr == ERR_SUCCESS ) {
        this->m_actList.push_back(act);
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
//    合法手の制約を指定する。
//

ErrCode
GameController::setConstraint(
        const  int  vCons)
{
    this->m_curDice = vCons;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    コンピュータの思考を開始する。
//

ErrCode
GameController::startThinking(
        ActionData  &actRet)
{
    typedef     ActionList::const_iterator      ActIter;

    ActionList  actList;

    makeLegalActionList(actList);

    const  ActIter  itrEnd  = actList.end();
    ActIter         itrHead = actList.begin();
    for ( ; itrHead != itrEnd; ++ itrHead ) {
        if ( (itrHead->xNewCol) == (this->m_curDice) ) {
            break;
        }
    }

    ActIter         itrTail = itrHead;
    for ( ActIter itr = itrHead; itr != itrEnd; ++ itr ) {
        if ( (itr->xNewCol) != (this->m_curDice) ) {
            itrTail = itr;
            break;
        }
    }

    if ( itrHead == itrTail ) {
        //  指定したダイスの目で合法手が無い場合。  //
        //  ダイスの目が六の場合もここを通過する。  //
        itrHead = actList.begin();
        itrTail = itrEnd;
    }
    const  int  numAct  = (itrTail - itrHead);
    if ( numAct == 0 ) {
        return ( ERR_ILLEGAL_ACTION );
    }

    int  r  =  rand() % numAct;
    actRet  =  *(itrHead + r);
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
    outStr  <<  (5 - actView.xNewCol)
            <<  (actView.yNewRow + 1)
            <<  ' '
            <<  s_tblPieceName[actView.fpAfter];
    if ( (actView.putHand) == 0 ) {
        outStr  <<  " ("
                <<  (5 - actView.xOldCol)
                <<  (actView.yOldRow + 1)
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
    typedef     ActionList::const_iterator  ActIter;

    const  ActionList  &obj = (this->m_actList);

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

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
