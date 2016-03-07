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
**      An Implementation of EngineBase class.
**
**      @file       Engine/EngineBase.cpp
**/

#include    "FairyShogi/Engine/EngineBase.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Game/BoardState.h"

#include    <stdlib.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Engine  {

//========================================================================
//
//    EngineBase  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

EngineBase::EngineBase()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

EngineBase::~EngineBase()
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
EngineBase::computeBestAction(
        const  ViewBuffer   &vbCur,
        const  PlayerIndex  piTurn,
        const  TConstraint  vCons,
        ActionView          &actRet)
{
    typedef     BoardState::ActionData          ActionData;
    typedef     std::vector<ActionData>         ActionDataList;

    //  現在の局面を、内部形式に変換する。  //
    BoardState      curStat;
    ActionViewList  actList;

    curStat.encodeFromViewBuffer(vbCur);

    actList.clear();
    makeLegalActionList(curStat,  piTurn,  vCons,  actList);

    const  int  numAct  =  actList.size();
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
        bsClone.cloneFrom(curStat);
        BoardState::encodeActionData(actList[r], &actData);
        bsClone.playForward(actData);

        vActs.clear();
        bsClone.makeLegalActionList(piTurn ^ 1,  0,  vActs);
        size_t  cntLegs =  vActs.size();
        if ( cntLegs == 0 ) {
            idxMin  =  r;
            scrMin  =  0;
            break;
        }

        BoardState::TBitBoard   bbCheck;
        if ( bsClone.isCheckState(piTurn ^ 1, bbCheck) > 0 ) {
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
//    Protected Member Functions.
//
//

//----------------------------------------------------------------
//    現在の局面の合法手を列挙する。
//

ErrCode
EngineBase::makeLegalActionList(
        const  BoardState   &curStat,
        const  PlayerIndex  piTurn,
        const  TConstraint  vCons,
        ActionViewList      &actList)
{
    typedef     std::vector<BoardState::ActionData> ActionDataList;
    typedef     ActionDataList::const_iterator      ActIter;

    //  まず、全ての合法手を列挙する。  //
    ActionDataList  vActs;
    ErrCode         retErr  =  ERR_SUCCESS;


    retErr  =  curStat.makeLegalActionList(
                    piTurn,  Common::ALF_LEGAL_ACTION,  vActs);

    actList.clear();
    actList.reserve( vActs.size() );

    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    const  ActIter  itrEnd  = vActs.end();
    ActIter         itrHead = vActs.begin();
    ActIter         itrTail = itrEnd;

    ActionView      actView;
    for ( ; itrHead != itrEnd; ++ itrHead ) {
        BoardState::decodeActionData( (* itrHead),  &actView );
        if ( (actView.xPlayNewCol) >= vCons )  {
            break;
        }
    }

    for ( ActIter itr = itrHead; itr != itrEnd; ++ itr ) {
        BoardState::decodeActionData( (* itr),  &actView );
        if ( (actView.xPlayNewCol) != vCons ) {
            itrTail = itr;
            break;
        }
    }

    if ( (itrHead == itrTail) ) {
        //  指定した条件で合法手がない時は、何でもできる。  //
        itrHead = vActs.begin();
        itrTail = itrEnd;
    }

    for ( ActIter itr = itrHead; itr != itrTail; ++ itr ) {
        BoardState::decodeActionData( (* itr),  &actView );
        actList.push_back(actView);
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Engine
FAIRYSHOGI_NAMESPACE_END
