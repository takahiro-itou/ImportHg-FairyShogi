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
    typedef     ActionDataList::const_iterator  ActIter;


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
    BoardState      bsClone2;
    ActionData      actData;
    ActionDataList  vActs;
    ActionDataList  vActs2;

    int             idxMin  =  0;
    double          scrMin  =  100000;

    for ( int r = 0;  r < numAct;  ++ r ) {
        BoardState::TBitBoard   bbCheck;

        bsClone.cloneFrom(curStat);
        BoardState::encodeActionData(actList[r], &actData);
        bsClone.playForward(actData);

        vActs.clear();
        bsClone.makeLegalActionList(piTurn ^ 1,  0,  vActs);
        size_t  cntLegs =  vActs.size();

        if ( bsClone.isCheckState(piTurn ^ 1,  bbCheck) > 0 ) {
            if ( cntLegs == 0 ) {
                //  チェックメイトなので、それを選択して勝ち。  //
                idxMin  =  r;
                scrMin  =  0;
                break;
            }
        } else {
            if ( cntLegs == 0 ) {
                //  王手が掛かっていない時は、選択しない。  //
                //  ステイルメイトなので、逆転負けになる。  //
                continue;
            }

            //  相手側の手番をパスして、その次の自分の合法手を考える。  //
            size_t  numRch  =  0;
            vActs.clear();
            bsClone.makeLegalActionList(piTurn,  0,  vActs);
            const  ActIter  itrEnd  =  vActs.end();
            for ( ActIter itr = vActs.begin(); itr != itrEnd; ++ itr )
            {
                bsClone2.cloneFrom(bsClone);
                bsClone2.playForward(* itr);

                vActs2.clear();
                bsClone2.makeLegalActionList(piTurn ^ 1,  0,  vActs2);
                if ( vActs.empty() ) {
                    //  相手側の合法手が無い。勝ちの局面。  //
                    //  換言すると壱手詰めの詰めろの状態。  //
                    //  ここではステイルメイトを無視した。  //
                    ++  numRch;
                }
            }
            if ( numRch > 0 ) {
                //  詰めろを掛けられる時は掛ける。  //
                idxMin  =  r;
                const   double  scrCur  =  -1.0 * numRch;
                if ( scrCur < scrMin ) {
                    idxMin  =  r;
                    scrMin  =  scrCur;
                }
                continue;
            }
        }

        //  それ以外は、相手の合法手を減らす。  //
        if ( bsClone.isCheckState(piTurn ^ 1, bbCheck) > 0 ) {
            cntLegs *= 3;
        }

        const   double  dblRnd  =  (rand() * 4.0 / RAND_MAX);
        const   double  scrCur  =  (cntLegs) * (dblRnd + 8);
        if ( scrCur < scrMin ) {
            idxMin  =  r;
            scrMin  =  scrCur;
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
