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
**      An Implementation of EngineLevel3 class.
**
**      @file       Engine/EngineLevel3.cpp
**/

#include    "EngineLevel3.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Game/BoardState.h"

#include    <iostream>
#include    <stdlib.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Engine  {

namespace  {

CONSTEXPR_VAR   int
s_tblCatchScore[21] =  {
    0,
    10, 50, 60, 70, 80, 0,  10, 50, 70, 80,
    10, 50, 60, 70, 80, 0,  10, 50, 70, 80,
};

CONSTEXPR_VAR   int
s_tblPieceScore[21] =  {
    0,
    10, 50, 60, 70, 80, 0,  35, 55, 90, 100,
    10, 50, 60, 70, 80, 0,  35, 55, 90, 100
};

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    EngineLevel3  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

EngineLevel3::EngineLevel3()
    : Super()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

EngineLevel3::~EngineLevel3()
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
EngineLevel3::computeBestAction(
        const  ViewBuffer   &vbCur,
        const  PlayerIndex  piTurn,
        const  TConstraint  vCons,
        ActionView          &actRet)
{
    //  現在の局面を、内部形式に変換する。  //
    BoardState      bsCur;
    InternState     curStat;
    ActionViewList  actList;
    ActViewIter     itrView;

    bsCur.encodeFromViewBuffer(vbCur);
    bsCur.cloneInternState(&curStat);

    actList.clear();
    makeLegalActionList(bsCur,  piTurn,  vCons,  actList);

    const  int  numAct  =  actList.size();
    if ( numAct == 0 ) {
        return ( ERR_ILLEGAL_ACTION );
    }
    if ( numAct == 1 ) {
        actRet  =  actList[0];
        return ( ERR_SUCCESS );
    }

    BoardState  bsClone;
    BoardState  bsClone2;
    ActionData  actData;
    ActionList  vActsS;
    ActionList  vActsE;

    int         idxMax  =  0;
    int         idxTmr  =  -1;
    int         scrTmr  =  -1;
    int         scrMax  =  -10000000;

    if ( findCheckMateAction(curStat, piTurn, actList, &itrView) ) {
        //  チェックメイトを発見したので、それを選択して終了。  //
        std::cerr   <<  "CHECK MATE."   <<  std::endl;
        actRet  =  (* itrView);
        return ( ERR_SUCCESS );
    }

    for ( int r = 0;  r < numAct;  ++ r ) {
        BoardState::TBitBoard   bbCheck;

        bsClone.cloneFrom(bsCur);
        BoardState::encodeActionData(actList[r], &actData);
        bsClone.playForward(actData);

        int     cntLegOppn  =  0;
        int     cntLegSelf  =  0;

        vActsE.clear();
        bsClone.makeLegalActionList(piTurn ^ 1,  0,  vActsE);
        cntLegOppn  =  vActsE.size();

        std::cerr   <<  "# INFO : "
                    <<  '['  <<  r  <<  "] "
                    <<  (actData.xOldCol) + 1
                    <<  (actData.yOldRow) + 1
                    <<  "->"
                    <<  (actData.xNewCol) + 1
                    <<  (actData.yNewRow) + 1
                    <<  '='
                    <<  (actData.fpAfter)
                    <<  "...";

        if ( bsClone.isCheckState(piTurn ^ 1,  bbCheck) > 0 ) {
            if ( cntLegOppn == 0 ) {
                //  チェックメイトなので、それを選択して勝ち。  //
                std::cerr   <<  " CHECK MATE"   <<  std::endl;
                actRet  =  actList[r];
                return ( ERR_SUCCESS );
            }
        } else {
            if ( cntLegOppn == 0 ) {
                //  王手が掛かっていない時は、選択しない。  //
                //  ステイルメイトなので、逆転負けになる。  //
                std::cerr   <<  "STALE MATE"    <<  std::endl;
                continue;
            }

            //  相手側の手番をパスして、その次の自分の合法手を考える。  //
            size_t  numWinPats  =  0;
            size_t  numWinDice  =  0;

            vActsS.clear();
            bsClone.makeLegalActionList(piTurn,  0,  vActsS);
            int     flgWins[6]  =  { 0, 0, 0, 0, 0, 0 };
            const  ActIter  itrEndS  =  vActsS.end();
            for ( ActIter itrS = vActsS.begin(); itrS != itrEndS; ++ itrS )
            {
                bsClone2.cloneFrom(bsClone);
                bsClone2.playForward(* itrS);

                ActionList  vActsT;
                vActsT.clear();
                bsClone2.makeLegalActionList(piTurn ^ 1,  0,  vActsT);
                if ( vActsT.empty() ) {
                    //  相手側の合法手が無い。勝ちの局面。  //
                    //  換言すると壱手詰めの詰めろの状態。  //
                    //  ここではステイルメイトを無視した。  //
                    if ( ++ flgWins[itrS->xNewCol] == 1 ) {
                        ++  numWinDice;
                    }
                    std::cerr   <<  "["
                                <<  (itrS->xOldCol + 1)
                                <<  (itrS->yOldRow + 1)
                                <<  (itrS->xNewCol + 1)
                                <<  (itrS->yNewRow + 1)
                                <<  (itrS->fpAfter)
                                <<  "] ";
                    ++  numWinPats;
                }
            }   //  Next  itrE

            if ( numWinPats > 0 ) {
                //  詰めろを掛けられる時は掛ける。  //
                const  int  scrCur  =  numWinDice * 1000 + numWinPats;
                if ( scrTmr < scrCur ) {
                    std::cerr   <<  "*SEL ";
                    idxMax  =  r;
                    idxTmr  =  r;
                    scrTmr  =  scrCur;
                    scrMax  =  scrCur;
                }
                std::cerr   <<  "  TUMERO : "   <<  scrCur
                            <<  " / "   <<  scrTmr  <<  std::endl;
                continue;
            }
        }

        //  それ以外は、駒の損得と、合法手の数で計算する。  //

        //  まず、捕獲した相手の駒の点数を加算する。        //
        const  int  scrCatchUp  =  s_tblCatchScore[actData.fpCatch] * 6;

        //  次に相手に取られる自分の駒の期待値を計算する。  //
        int     scrCatchMe  =  0;
        int     scrAtkMaxs[6]  =  { 0, 0, 0, 0, 0, 0 };
        const  ActIter  itrEndE = vActsE.end();
        for ( ActIter itrE = vActsE.begin(); itrE != itrEndE; ++ itrE )
        {
            if ( (itrE->fpCatch) == 0 ) { continue; }
            const  int  nx  = (itrE->xNewCol);
            int         sc  = s_tblPieceScore[itrE->fpCatch];
            if ( ((actData.hpiDrop) == (BoardState::IHAND_EMPTY_PIECE))
                    && ((itrE->xNewCol) == (actData.xNewCol))
                    && ((itrE->yNewRow) == (actData.yNewRow))
                    && ((actData.fpAfter) != (actData.fpMoved))
            )
            {
                sc  = s_tblPieceScore[actData.fpMoved];
            }
            if ( scrAtkMaxs[nx] < sc ) {
                if ( scrAtkMaxs[ 5] < sc ) {
                    scrAtkMaxs[ 5]  =  sc;
                }
                scrAtkMaxs[nx]  =  sc;
            }
        }

        //  自分の合法手。本当は、相手の手番だが無視。  //
        vActsS.clear();
        bsClone.makeLegalActionList(piTurn,  0,  vActsS);
        cntLegSelf  =  vActsS.size();

        //  相手の合法手の総数は既に計算済み。  //
        //  そこから期待値を算出する。          //
        if ( bsClone.isCheckState(piTurn ^ 1, bbCheck) > 0 ) {
            std::cerr   <<  "CHECK.";
            cntLegOppn  *=  3;
            scrCatchMe  =   scrAtkMaxs[5] * 6;
        } else {
            scrCatchMe  =   scrAtkMaxs[0] + scrAtkMaxs[1]
                    +  scrAtkMaxs[2] + scrAtkMaxs[3]
                    +  scrAtkMaxs[4] + scrAtkMaxs[5];
        }

        //  成りボーナスを加算する。    //
        int         sbProm  =  0;
        if ( actData.hpiDrop == 0 ) {
            sbProm  =  s_tblPieceScore[actData.fpAfter]
                    -  s_tblPieceScore[actData.fpMoved];
        }

        const  int  scrCur  =  (scrCatchUp - scrCatchMe)
            +  ((cntLegSelf - cntLegOppn)) + sbProm;
        if ( scrMax < scrCur ) {
            std::cerr   <<  "*SEL ";
            idxMax  =  r;
            scrMax  =  scrCur;
        }
        std::cerr   <<  "@ "    <<  scrCur
                    <<  " / "   <<  scrMax
                    <<  ", # +CU="  <<  scrCatchUp
                    <<  ", -CM="    <<  scrCatchMe
                    <<  ", +MS="    <<  cntLegSelf
                    <<  ", -ME="    <<  cntLegOppn
                    <<  std::endl;
    }

    if ( idxTmr >= 0 ) {
        std::cerr   <<  "# INFO : TUMERO (or HISSI) Finded ."
                    <<  std::endl;
        idxMax  =  idxTmr;
    }

    std::cerr   <<  "# INFO : Select Index = "  <<  idxMax  <<  std::endl;
    actRet  =  actList[idxMax];

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
