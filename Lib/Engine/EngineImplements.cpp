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
#include    "FairyShogi/Game/BoardState.h"

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
//    現在の局面の合法手を列挙する。
//

ErrCode
EngineImplements::makeLegalActionList(
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

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Engine
FAIRYSHOGI_NAMESPACE_END
