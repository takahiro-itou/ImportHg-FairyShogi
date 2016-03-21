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
**      An Implementation of EngineLevel1 class.
**
**      @file       Engine/EngineLevel1.cpp
**/

#include    "EngineLevel1.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Game/BoardState.h"

#include    <time.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Engine  {

//========================================================================
//
//    EngineLevel1  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

EngineLevel1::EngineLevel1()
    : Super(),
      m_rndGen()
{
#if defined( _DEBUG )
    this->m_rndGen.setSeedValue(4357);
#else
    this->m_rndGen.setSeedValue( ::time(nullptr) );
#endif
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

EngineLevel1::~EngineLevel1()
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
EngineLevel1::computeBestAction(
        const  ViewBuffer   &vbCur,
        const  PlayerIndex  piTurn,
        const  TConstraint  vCons,
        ActionView          &actRet)
{
    typedef     BoardState::ActionData          ActionData;
    typedef     BoardState::ActionList          ActionDataList;

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
        bsClone.cloneFrom(curStat);
        BoardState::encodeActionData(actList[r], &actData);
        bsClone.playForward(actData);

        vActs.clear();
        bsClone.makeLegalActionList(
                piTurn ^ Common::PLAYER_OPPOSITE,
                Common::ALF_LEGAL_ACTION,
                vActs);
        const  size_t  cntLegs  =  vActs.size();
        if ( cntLegs == 0 ) {
            idxMin  =  r;
            scrMin  =  0;
            break;
        }

        const  RandResult
            rndRet  =  (this->m_rndGen.getNext() & RANDOM_MAX_VALUE);
        const  double   dblRnd  =  (rndRet * 4.0 / RANDOM_MAX_VALUE);
        const  double   scrCur  =  (cntLegs) * (dblRnd + 8.0);
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

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Engine
FAIRYSHOGI_NAMESPACE_END
