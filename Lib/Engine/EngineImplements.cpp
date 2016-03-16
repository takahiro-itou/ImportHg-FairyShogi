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
**      An Implementation of EngineImplements class.
**
**      @file       Engine/EngineImplements.cpp
**/

#include    "EngineImplements.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/FairyShogiConst.h"
#include    "FairyShogi/Game/BoardState.h"

#include    <memory.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Engine  {

//========================================================================
//
//    EngineImplements  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

EngineImplements::EngineImplements()
    : Super()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

EngineImplements::~EngineImplements()
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

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Protected Member Functions.
//

//----------------------------------------------------------------
//    相手の玉をチェックメイトできる手を検索する。
//

EngineImplements::ActionCount
EngineImplements::findCheckMateActions(
        const  InternState  &curStat,
        const  PlayerIndex  piTurn,
        const  ActionList   &actList,
        TCountArray         nCounts)
{
    const  PlayerIndex  piEnemy = piTurn ^ Common::PLAYER_OPPOSITE;

    for ( int i = 0; i < Common::DICE_MAX_VALUE; ++ i ) {
        nCounts[i]  =  -1;
    }
    nCounts[ENGINE_IDICE_ANY_MOVE]  =  0;

    InternState     stClone;
    const  ActIter  itrEnd  = actList.end();
    for ( ActIter itr = actList.begin(); itr != itrEnd; ++ itr ) {
        stClone = curStat;
        const   PosCol  nx  = (itr->xNewCol);

        BoardState::playForward(* itr, stClone);
        if ( nCounts[nx] < 0 ) {
            nCounts[nx] = 0;
        }
        if ( ! isCheckMateState(stClone, piEnemy) ) {
            continue;
        }
        ++  nCounts[nx];
        ++  nCounts[ENGINE_IDICE_ANY_MOVE];
    }

    ActionCount     retCnt  = 0;
    for ( int i = 0; i < 6; ++ i ) {
        if ( nCounts[i] < 0 ) {
            //  この目では合法手が無いので、六として扱う。  //
            nCounts[i]  = nCounts[ENGINE_IDICE_ANY_MOVE];
        }
        if ( nCounts[i] > 0 ) {
            ++  retCnt;
        }
    }

    return ( retCnt );
}

//----------------------------------------------------------------
//    相手の玉をチェックメイトできる手を検索する。
//

Boolean
EngineImplements::findCheckMateAction(
        const  InternState      &curStat,
        const  PlayerIndex      piTurn,
        const  ActionViewList   &actList,
        ActViewIter  *          itrRet)
{
    InternState     stClone;
    ActionData      actData;

    const  ActViewIter  itrEnd  = actList.end();
    for ( ActViewIter itr = actList.begin(); itr != itrEnd; ++ itr )
    {
        ::memcpy( &stClone, &curStat, sizeof(stClone) );
        BoardState::encodeActionData((* itr), &actData);
        BoardState::playForward(actData, stClone);
        if ( isCheckMateState(stClone, piTurn ^ Common::PLAYER_OPPOSITE) )
        {
            //  チェックメイトを発見。  //
            (* itrRet)  = itr;
            return ( BOOL_TRUE );
        }
    }

    (* itrRet)  = itrEnd;
    return ( BOOL_FALSE );
}

//----------------------------------------------------------------
//    現在の局面がチェックメイトかどうかを判定する。
//

Boolean
EngineImplements::isCheckMateState(
        const  InternState  &curStat,
        const  PlayerIndex  piTurn)
{
    ActionList  vActs;
    TBitBoard   bbTemp;

    if ( BoardState::isCheckState(curStat, piTurn, bbTemp) <= 0 ) {
        //  王手が掛かっていない。  //
        return ( BOOL_FALSE );
    }

    BoardState::makeLegalActionList(
            curStat,  piTurn,  Common::ALF_LEGAL_ACTION,  vActs);
    if ( vActs.empty() ) {
        //  王手が掛かっていて、合法手が無い。  //
        return ( BOOL_TRUE );
    }

    return ( BOOL_FALSE );
}

//----------------------------------------------------------------
//    現在の局面の合法手を列挙する。
//

ErrCode
EngineImplements::makeLegalActionList(
        const  BoardState   &curStat,
        const  PlayerIndex  piTurn,
        const  TConstraint  vCons,
        ActionViewList      &actList)
{
    //  まず、全ての合法手を列挙する。  //
    ActionList  vActs;
    ErrCode     retErr  =  ERR_SUCCESS;

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

//----------------------------------------------------------------
//    現在の局面の合法手を列挙する。
//

ErrCode
EngineImplements::makeLegalActionList(
        const  InternState  &curStat,
        const  PlayerIndex  piTurn,
        const  TConstraint  vCons,
        ActionList          &actList)
{
    //  まず、全ての合法手を列挙する。  //
    ActionList  vActs;
    ErrCode     retErr  =  ERR_SUCCESS;

    if ( (vCons < 0) || (ENGINE_IDICE_ANY_MOVE <= vCons) ) {
        retErr  =  BoardState::makeLegalActionList(
                        curStat,  piTurn,  Common::ALF_LEGAL_ACTION,
                        actList);
        return ( retErr );
    }

    retErr  =  BoardState::makeLegalActionList(
                    curStat,  piTurn,  Common::ALF_LEGAL_ACTION,
                    vActs);
    actList.clear();
    actList.reserve( vActs.size() );

    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    const  ActIter  itrEnd  = vActs.end();
    ActIter         itrHead = vActs.begin();
    ActIter         itrTail = itrEnd;

    for ( ; itrHead != itrEnd; ++ itrHead ) {
        if ( (itrHead->xNewCol) >= vCons )  {
            break;
        }
    }

    for ( ActIter itr = itrHead; itr != itrEnd; ++ itr ) {
        if ( (itr->xNewCol) != vCons ) {
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
        actList.push_back(* itr);
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Engine
FAIRYSHOGI_NAMESPACE_END
