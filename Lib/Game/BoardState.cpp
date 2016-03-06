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
**      An Implementation of BoardState class.
**
**      @file       Game/BoardState.cpp
**/

#include    "FairyShogi/Game/BoardState.h"

#include    "FairyShogi/Game/RuleTables.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/FairyShogiConst.h"

#include    <iostream>
#include    <memory.h>

#include    <assert.h>
#include    <iomanip>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Game  {

namespace  {

CONSTEXPR_VAR   Common::EFieldPiece
s_tblDecodeField[BoardState::NUM_PIECE_TYPES]   =  {
    Common::FIELD_EMPTY_SQUARE,

    Common::FIELD_BLACK_PAWN,
    Common::FIELD_BLACK_SILVER,
    Common::FIELD_BLACK_GOLD,
    Common::FIELD_BLACK_BISHOP,
    Common::FIELD_BLACK_ROOK,
    Common::FIELD_BLACK_KING,
    Common::FIELD_BLACK_PR_PAWN,
    Common::FIELD_BLACK_PR_SILVER,
    Common::FIELD_BLACK_PR_BISHOP,
    Common::FIELD_BLACK_PR_ROOK,

    Common::FIELD_WHITE_PAWN,
    Common::FIELD_WHITE_SILVER,
    Common::FIELD_WHITE_GOLD,
    Common::FIELD_WHITE_BISHOP,
    Common::FIELD_WHITE_ROOK,
    Common::FIELD_WHITE_KING,
    Common::FIELD_WHITE_PR_PAWN,
    Common::FIELD_WHITE_PR_SILVER,
    Common::FIELD_WHITE_PR_BISHOP,
    Common::FIELD_WHITE_PR_ROOK
};

CONSTEXPR_VAR   PieceIndex
s_tblEncodeField[Common::NUM_FIELD_PIECE_TYPES]  =  {
    BoardState::BOARD_EMPTY_SQUARE,

    BoardState::BOARD_BLACK_PAWN,
    BoardState::BOARD_EMPTY_SQUARE,         //  香車。  //
    BoardState::BOARD_EMPTY_SQUARE,         //  桂馬。  //
    BoardState::BOARD_BLACK_SILVER,
    BoardState::BOARD_BLACK_GOLD,
    BoardState::BOARD_BLACK_BISHOP,
    BoardState::BOARD_BLACK_ROOK,
    BoardState::BOARD_BLACK_KING,
    BoardState::BOARD_BLACK_PR_PAWN,
    BoardState::BOARD_EMPTY_SQUARE,         //  成香。  //
    BoardState::BOARD_EMPTY_SQUARE,         //  成桂。  //
    BoardState::BOARD_BLACK_PR_SILVER,
    BoardState::BOARD_BLACK_PR_BISHOP,
    BoardState::BOARD_BLACK_PR_ROOK,

    BoardState::BOARD_WHITE_PAWN,
    BoardState::BOARD_EMPTY_SQUARE,         //  香車。  //
    BoardState::BOARD_EMPTY_SQUARE,         //  桂馬。  //
    BoardState::BOARD_WHITE_SILVER,
    BoardState::BOARD_WHITE_GOLD,
    BoardState::BOARD_WHITE_BISHOP,
    BoardState::BOARD_WHITE_ROOK,
    BoardState::BOARD_WHITE_KING,
    BoardState::BOARD_WHITE_PR_PAWN,
    BoardState::BOARD_EMPTY_SQUARE,         //  成香。  //
    BoardState::BOARD_EMPTY_SQUARE,         //  成桂。  //
    BoardState::BOARD_WHITE_PR_SILVER,
    BoardState::BOARD_WHITE_PR_BISHOP,
    BoardState::BOARD_WHITE_PR_ROOK
};

CONSTEXPR_VAR   Common::EHandPiece
s_tblDecodeHands[BoardState::NUM_IHAND_TYPES]   =  {
    Common::HAND_EMPTY_PIECE,

    Common::HAND_BLACK_PAWN,
    Common::HAND_BLACK_SILVER,
    Common::HAND_BLACK_GOLD,
    Common::HAND_BLACK_BISHOP,
    Common::HAND_BLACK_ROOK,
    Common::HAND_BLACK_KING,

    Common::HAND_WHITE_PAWN,
    Common::HAND_WHITE_SILVER,
    Common::HAND_WHITE_GOLD,
    Common::HAND_WHITE_BISHOP,
    Common::HAND_WHITE_ROOK,
    Common::HAND_WHITE_KING
};

CONSTEXPR_VAR   PieceIndex
s_tblEncodeHands[Common::NUM_HAND_TYPES]  =  {
    BoardState::IHAND_EMPTY_PIECE,

    BoardState::IHAND_BLACK_PAWN,
    BoardState::IHAND_EMPTY_PIECE,          //  香車。  //
    BoardState::IHAND_EMPTY_PIECE,          //  桂馬。  //
    BoardState::IHAND_BLACK_SILVER,
    BoardState::IHAND_BLACK_GOLD,
    BoardState::IHAND_BLACK_BISHOP,
    BoardState::IHAND_BLACK_ROOK,
    BoardState::IHAND_BLACK_KING,

    BoardState::IHAND_WHITE_PAWN,
    BoardState::IHAND_EMPTY_PIECE,          //  香車。  //
    BoardState::IHAND_EMPTY_PIECE,          //  桂馬。  //
    BoardState::IHAND_WHITE_SILVER,
    BoardState::IHAND_WHITE_GOLD,
    BoardState::IHAND_WHITE_BISHOP,
    BoardState::IHAND_WHITE_ROOK,
    BoardState::IHAND_WHITE_KING
};

CONSTEXPR_VAR   PieceIndex
s_tblPromNew[BoardState::NUM_PIECE_TYPES]   =  {
    -1,
    BoardState::BOARD_BLACK_PR_PAWN,
    BoardState::BOARD_BLACK_PR_SILVER,
    -1,
    BoardState::BOARD_BLACK_PR_BISHOP,
    BoardState::BOARD_BLACK_PR_ROOK,
    -1,     -1,  -1,  -1,  -1,

    BoardState::BOARD_WHITE_PR_PAWN,
    BoardState::BOARD_WHITE_PR_SILVER,
    -1,
    BoardState::BOARD_WHITE_PR_BISHOP,
    BoardState::BOARD_WHITE_PR_ROOK,
    -1,     -1,  -1,  -1,  -1,
};


CONSTEXPR_VAR   int
s_tblPieceOwner[BoardState::NUM_PIECE_TYPES]    =  {
    -1,
    0, 0, 0, 0, 0, 0,   0, 0, 0, 0,
    1, 1, 1, 1, 1, 1,   1, 1, 1, 1
};

CONSTEXPR_VAR   int
s_tblHandsOwner[BoardState::NUM_IHAND_TYPES]    =  {
    -1,     0, 0, 0, 0, 0, 0,   1, 1, 1, 1, 1, 1
};

CONSTEXPR_VAR   PieceIndex
s_tblHandConv[BoardState::NUM_IHAND_TYPES]  =  {
    BoardState::BOARD_EMPTY_SQUARE,

    BoardState::BOARD_BLACK_PAWN,
    BoardState::BOARD_BLACK_SILVER,
    BoardState::BOARD_BLACK_GOLD,
    BoardState::BOARD_BLACK_BISHOP,
    BoardState::BOARD_BLACK_ROOK,
    BoardState::BOARD_BLACK_KING,

    BoardState::BOARD_WHITE_PAWN,
    BoardState::BOARD_WHITE_SILVER,
    BoardState::BOARD_WHITE_GOLD,
    BoardState::BOARD_WHITE_BISHOP,
    BoardState::BOARD_WHITE_ROOK,
    BoardState::BOARD_WHITE_KING
};

CONSTEXPR_VAR   PieceIndex
s_tblCatchToHand[BoardState::NUM_PIECE_TYPES] = {
    BoardState::IHAND_EMPTY_PIECE,

    BoardState::IHAND_WHITE_PAWN,
    BoardState::IHAND_WHITE_SILVER,
    BoardState::IHAND_WHITE_GOLD,
    BoardState::IHAND_WHITE_BISHOP,
    BoardState::IHAND_WHITE_ROOK,
    BoardState::IHAND_WHITE_KING,
    BoardState::IHAND_WHITE_PAWN,
    BoardState::IHAND_WHITE_SILVER,
    BoardState::IHAND_WHITE_BISHOP,
    BoardState::IHAND_WHITE_ROOK,

    BoardState::IHAND_BLACK_PAWN,
    BoardState::IHAND_BLACK_SILVER,
    BoardState::IHAND_BLACK_GOLD,
    BoardState::IHAND_BLACK_BISHOP,
    BoardState::IHAND_BLACK_ROOK,
    BoardState::IHAND_BLACK_KING,
    BoardState::IHAND_BLACK_PAWN,
    BoardState::IHAND_BLACK_SILVER,
    BoardState::IHAND_BLACK_BISHOP,
    BoardState::IHAND_BLACK_ROOK
};

/**
**    ダミーのグローバル変数。
**
**    インスタンスを壱個だけ生成して、
**  コンストラクタで表を構築させる。
**/
RuleTables  g_objRules;

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    BoardState  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

BoardState::BoardState()
    : m_icState()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BoardState::~BoardState()
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

//----------------------------------------------------------------
//    指定した局面のクローンを作成する。
//

ErrCode
BoardState::cloneFrom(
        const  BoardState  &objSrc)
{
    ::memcpy( &(this->m_icState),  &(objSrc.m_icState),
              sizeof(this->m_icState) );
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    指し手の内部形式を表示用データに変換する。
//

ErrCode
BoardState::decodeActionData(
        const   ActionData   &  actData,
        ActionView  *  const    actView)
{
    ::memset( actView, 0, sizeof(ActionView) );

    actView->xPlayNewCol    =  (actData.xNewCol + 1);
    actView->yPlayNewRow    =  (actData.yNewRow + 1);
    actView->xPlayOldCol    =  (actData.xOldCol + 1);
    actView->yPlayOldRow    =  (actData.yOldRow + 1);

    actView->fpAfter        =  s_tblDecodeField[ actData.fpAfter ];
    actView->fpMoved        =  s_tblDecodeField[ actData.fpMoved ];
    actView->fpCatch        =  s_tblDecodeField[ actData.fpCatch ];
    actView->hpiDrop        =  s_tblDecodeHands[ actData.hpiDrop ];

    actView->fLegals        =  (actData.fLegals);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    指定した座標にある駒を取得する。
//

Common::EFieldPiece
BoardState::decodeFieldPiece(
        const  PosCol   xCol,
        const  PosRow   yRow)  const
{
    return ( s_tblDecodeField[ getFieldPiece(xCol, yRow) ] );
}

//----------------------------------------------------------------
//    指し手の表示用形式を内部形式に変換する。
//

ErrCode
BoardState::encodeActionData(
        const   ActionView   &  actView,
        ActionData  *  const    actData)
{
    ::memset( actData, 0, sizeof(ActionData) );

    actData->xNewCol    =  (actView.xPlayNewCol - 1);
    actData->yNewRow    =  (actView.yPlayNewRow - 1);
    actData->xOldCol    =  (actView.xPlayOldCol - 1);
    actData->yOldRow    =  (actView.yPlayOldRow - 1);

    actData->fpCatch    =  s_tblEncodeField[ actView.fpCatch ];
    actData->fpMoved    =  s_tblEncodeField[ actView.fpMoved ];
    actData->fpAfter    =  s_tblEncodeField[ actView.fpAfter ];
    actData->hpiDrop    =  s_tblEncodeHands[ actView.hpiDrop ];

    actData->fLegals    =  (actView.fLegals);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    王手が掛かっているかどうかを判定する。
//

size_t
BoardState::isCheckState(
        const  PlayerIndex  dPlayer,
        TBitBoard           &bbFrom)  const
{
    return ( isCheckState(this->m_icState, dPlayer, bbFrom) );
}

//----------------------------------------------------------------
//    王手が掛かっているかどうかを判定する。
//

size_t
BoardState::isCheckState(
        const  InternState  &curStat,
        const  PlayerIndex  dPlayer,
        TBitBoard           &bbFrom)
{
    bbFrom.clear();

    //  守備側の玉の座標を計算する。    //
    const  PieceIndex
        piKing  = (dPlayer == 0 ? BOARD_BLACK_KING : BOARD_WHITE_KING);
    FieldIndex  posTrg  = 0;
    for ( ; posTrg < BOARD_SIZE; ++ posTrg ) {
        if ( (curStat.m_bsField[posTrg]) == piKing ) {
            break;
        }
    }
    if ( posTrg == BOARD_SIZE ) {
        //  致命的エラー。玉がどこにもいない。  //
        std::cerr   <<  "# FATAL ERROR : No King :"
                    <<  piKing  <<  std::endl;
        for ( PosRow y = 0; y < POS_NUM_ROWS; ++ y ) {
            for ( PosCol x = 0; x < POS_NUM_COLS; ++ x ) {
                const  FieldIndex   fi
                    = getMatrixPos(POS_NUM_COLS - 1 - x, y);
                std::cerr   <<  std::setw(2)
                            <<  curStat.m_bsField[fi]
                            <<  ", ";
            }
            std::cerr   <<  std::endl;
        }

        return ( 0 );
    }

    getAttackFromList(curStat, posTrg, dPlayer ^ 1, bbFrom);
    return ( bbFrom.size() );
}

//----------------------------------------------------------------
//    合法手を列挙する。
//

ErrCode
BoardState::makeLegalActionList(
        const  PlayerIndex  cPlayer,
        const  ActionFlag   fLegals,
        ActionList          &actList)  const
{
    return ( makeLegalActionList(
                     this->m_icState, cPlayer, fLegals, actList) );
}

//----------------------------------------------------------------
//    合法手を列挙する。
//

ErrCode
BoardState::makeLegalActionList(
        const  InternState  &curStat,
        const  PlayerIndex  cPlayer,
        const  ActionFlag   fLegals,
        ActionList          &actList)
{
    typedef     TBitBoard::const_iterator   BB_Iter;

    ActionData  actData;

    ActionData  actTemp;
    InternState tmpStat;
    TBitBoard   bbCheck;

    for ( FieldIndex posTrg = 0; posTrg < BOARD_SIZE; ++ posTrg ) {
        //  盤上の駒を動かす。  //
        const  PieceIndex   cpiTrg  = curStat.m_bsField[posTrg];

        //  対象の座標に自分の駒がある場合は移動不可。  //
        //  その場所には、持ち駒を打つこともできない。  //
        if ( s_tblPieceOwner[cpiTrg] == cPlayer )   { continue; }

        TBitBoard    bbFrom;
        getAttackFromList(curStat, posTrg, cPlayer, bbFrom);
        const  BB_Iter  itrEndB = bbFrom.end();
        for ( BB_Iter itrB = bbFrom.begin(); itrB != itrEndB; ++ itrB ) {
            const  FieldIndex   posSrc  = (* itrB);
            const  PieceIndex   p       = (curStat.m_bsField[posSrc]);

            ::memset( &actData, 0, sizeof(actData) );
            actData.xNewCol = (posTrg / POS_NUM_ROWS);
            actData.yNewRow = (posTrg % POS_NUM_ROWS);
            actData.xOldCol = (posSrc / POS_NUM_ROWS);
            actData.yOldRow = (posSrc % POS_NUM_ROWS);
            actData.fpCatch = cpiTrg;
            actData.fpMoved = p;
            actData.fpAfter = p;
            actData.hpiDrop = IHAND_EMPTY_PIECE;
            actData.fLegals = Common::ALF_LEGAL_ACTION;

            int cntProm = 0;
            PieceIndex  vProm[2] = { p, -1 };
            if ( s_tblPieceOwner[p] == Common::PLAYER_BLACK ) {
                if (       ((actData.yNewRow) == 0)
                        || ((actData.yOldRow) == 0)  )
                {
                    if ( p != BOARD_BLACK_PAWN ) {
                        vProm[cntProm ++]   = p;
                    }
                    vProm[cntProm]  = s_tblPromNew[p];
                }
            } else {
                if (       ((actData.yNewRow) == POS_NUM_ROWS - 1)
                        || ((actData.yOldRow) == POS_NUM_ROWS - 1)  )
                {
                    if ( p != BOARD_WHITE_PAWN ) {
                        vProm[cntProm ++]   = p;
                    }
                    vProm[cntProm]  = s_tblPromNew[p];
                }
            }
            actData.fpAfter = vProm[0];

            //  動かしてみて、自殺だったらスキップ。    //
            ::memcpy( &tmpStat, &curStat, sizeof(tmpStat) );
            ::memcpy( &actTemp, &actData, sizeof(actTemp) );
            playForward(actTemp, tmpStat);

            actData.fLegals = Common::ALF_LEGAL_ACTION;
            if ( isCheckState(tmpStat, cPlayer, bbCheck) > 0 ) {
                if ( !(fLegals & Common::ALF_IGNORE_CHECK) ) {
                    continue;
                }
                actData.fLegals |= Common::ALF_IGNORE_CHECK;
            }

            actList.push_back(actData);

            if ( vProm[1] == -1 ) { continue; }
            actData.fpAfter = vProm[1];
            actList.push_back(actData);
        }   //  Next  itrB

        //  持ち駒を打つ。  //
        if ( cpiTrg != BOARD_EMPTY_SQUARE ) { continue; }
        actData.xNewCol = (posTrg / POS_NUM_ROWS);
        actData.yNewRow = (posTrg % POS_NUM_ROWS);
        actData.xOldCol = -1;
        actData.yOldRow = -1;
        actData.fpCatch = BOARD_EMPTY_SQUARE;
        actData.fpMoved = BOARD_EMPTY_SQUARE;
        actData.fpAfter = BOARD_EMPTY_SQUARE;
        actData.hpiDrop = IHAND_EMPTY_PIECE;
        actData.fLegals = Common::ALF_LEGAL_ACTION;

        for ( int k = IHAND_BLACK_PAWN; k < IHAND_WHITE_KING; ++ k ) {
            if ( s_tblHandsOwner[k] != cPlayer )  { continue; }
            if ( curStat.m_hcHands[k] <= 0 )      { continue; }

            if ( (k == IHAND_BLACK_PAWN) && ((actData.yNewRow) == 0) ) {
                continue;
            }
            if ( (k == IHAND_WHITE_PAWN)
                    && ((actData.yNewRow) == POS_NUM_ROWS - 1) )
            {
                continue;
            }

            actData.fLegals = Common::ALF_LEGAL_ACTION;
            int     flgDps  = 0;
            if ( (k == IHAND_BLACK_PAWN) || (k == IHAND_WHITE_PAWN) ) {
                for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
                    if ( curStat.m_bsField[actData.xNewCol * POS_NUM_ROWS + y]
                            == k )
                    {
                        flgDps  = 1;
                    }
                }
            }
            if ( flgDps ) {
                if ( !(fLegals & Common::ALF_DOUBLE_PAWNS) ) {
                    continue;
                }
                actData.fLegals |= Common::ALF_DOUBLE_PAWNS;
            }

            actData.hpiDrop = k;
            actData.fpAfter = s_tblHandConv[k];

            //  動かしてみて、自殺だったらスキップ。    //
            ::memcpy( &tmpStat, &curStat, sizeof(tmpStat) );
            ::memcpy( &actTemp, &actData, sizeof(actTemp) );
            playForward(actTemp, tmpStat);

            if ( isCheckState(tmpStat, cPlayer, bbCheck) > 0 ) {
                if ( !(fLegals & Common::ALF_IGNORE_CHECK) ) {
                    continue;
                }
                actData.fLegals |= Common::ALF_IGNORE_CHECK;
            }

            assert( actData.fpAfter >= 0 );
            actList.push_back(actData);
        }   //  Next  k
    }   //  Next  posTrg

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を戻す。
//

ErrCode
BoardState::playBackward(
        const  ActionData   &actBwd)
{
    return ( playBackward(actBwd, this->m_icState) );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を戻す。
//

ErrCode
BoardState::playBackward(
        const  ActionData   &actBwd,
        InternState         &curStat)
{
    //  駒を打っていた時は、その駒を持ち駒に戻す。  //
    if ( actBwd.hpiDrop != IHAND_EMPTY_PIECE ) {
        ++  curStat.m_hcHands[actBwd.hpiDrop];
    }

    //  捕獲した相手の駒があれば元に戻す。  //
    //  これには、持ち駒を減らす処理と、    //
    //  盤上に戻す処理の二つの処理が必要。  //
    if ( actBwd.fpCatch != BOARD_EMPTY_SQUARE ) {
        const  PieceIndex   piHand  = s_tblCatchToHand[actBwd.fpCatch];
        --  curStat.m_hcHands[piHand];
    }
    curStat.m_bsField[ getMatrixPos(actBwd.xNewCol, actBwd.yNewRow) ]
            =  actBwd.fpCatch;

    //  移動した駒がある時は、元の位置に戻す。  //
    if ( (actBwd.fpMoved) != BOARD_EMPTY_SQUARE ) {
        curStat.m_bsField[ getMatrixPos(actBwd.xOldCol, actBwd.yOldRow) ]
                =  actBwd.fpMoved;
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を進める。
//

ErrCode
BoardState::playForward(
        const  ActionData   &actFwd)
{
    return ( playForward(actFwd, this->m_icState) );
}

ErrCode
BoardState::playForward(
        const  ActionData   &actFwd,
        InternState         &curStat)
{
    //  移動元のマスを空きマスにする。  //
    if ( (actFwd.fpMoved) != BOARD_EMPTY_SQUARE ) {
        curStat.m_bsField[ getMatrixPos(actFwd.xOldCol, actFwd.yOldRow) ]
                =  BOARD_EMPTY_SQUARE;
    }

    //  移動先に指定した駒を書き込む。  //
    curStat.m_bsField[ getMatrixPos(actFwd.xNewCol, actFwd.yNewRow) ]
            =  actFwd.fpAfter;

    //  取った相手の駒を持ち駒にする。  //
    if ( actFwd.fpCatch != BOARD_EMPTY_SQUARE ) {
        const  PieceIndex   piHand  = s_tblCatchToHand[actFwd.fpCatch];
        ++  curStat.m_hcHands[piHand];
    }

    //  駒を打つ場合は持ち駒を減らす。  //
    if ( actFwd.hpiDrop != IHAND_EMPTY_PIECE ) {
        --  curStat.m_hcHands[actFwd.hpiDrop];
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
BoardState::resetGameBoard()
{
    return ( resetGameBoard(&(this->m_icState)) );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
BoardState::resetGameBoard(
        InternState  *  pCurStat)
{
    for ( FieldIndex i = 0; i < POS_NUM_ROWS * POS_NUM_COLS; ++ i ) {
        pCurStat->m_bsField[i]  =  BOARD_EMPTY_SQUARE;
    }

    pCurStat->m_bsField[getMatrixPos(4, 0)] = BOARD_WHITE_ROOK;
    pCurStat->m_bsField[getMatrixPos(3, 0)] = BOARD_WHITE_BISHOP;
    pCurStat->m_bsField[getMatrixPos(2, 0)] = BOARD_WHITE_SILVER;
    pCurStat->m_bsField[getMatrixPos(1, 0)] = BOARD_WHITE_GOLD;
    pCurStat->m_bsField[getMatrixPos(0, 0)] = BOARD_WHITE_KING;
    pCurStat->m_bsField[getMatrixPos(0, 1)] = BOARD_WHITE_PAWN;

    pCurStat->m_bsField[getMatrixPos(4, 3)] = BOARD_BLACK_PAWN;
    pCurStat->m_bsField[getMatrixPos(4, 4)] = BOARD_BLACK_KING;
    pCurStat->m_bsField[getMatrixPos(3, 4)] = BOARD_BLACK_GOLD;
    pCurStat->m_bsField[getMatrixPos(2, 4)] = BOARD_BLACK_SILVER;
    pCurStat->m_bsField[getMatrixPos(1, 4)] = BOARD_BLACK_BISHOP;
    pCurStat->m_bsField[getMatrixPos(0, 4)] = BOARD_BLACK_ROOK;

    for ( PieceIndex hp = 0; hp < NUM_IHAND_TYPES; ++ hp ) {
        pCurStat->m_hcHands[hp] = 0;
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    現在の盤面を取得して、表示用バッファにコピーする。
//

ErrCode
BoardState::copyToViewBuffer(
        Common::ViewBuffer  &bufView)  const
{
    return ( copyToViewBuffer(this->m_icState, bufView) );
}

//----------------------------------------------------------------
//  現在の盤面を取得して、表示用バッファにコピーする。
//

ErrCode
BoardState::copyToViewBuffer(
        const  InternState  &curStat,
        Common::ViewBuffer  &bufView)
{
    bufView.numPlayers  =  Common::NUM_PLAYERS;
    bufView.numRows     =  POS_NUM_ROWS;
    bufView.numCols     =  POS_NUM_COLS;

    for ( PlayerIndex i = 0; i < Common::NUM_PLAYERS; ++ i ) {
        bufView.numHandTypes[i] = (NUM_IHAND_TYPES / 2);
    }

    for ( int yr = 0; yr < POS_NUM_ROWS; ++ yr ) {
        for ( int xc = 0; xc < POS_NUM_COLS; ++ xc ) {
            const  FieldIndex
                fi  =  (yr * POS_NUM_COLS) + (POS_NUM_COLS - 1 - xc);
            const  PieceIndex
                pi  =  curStat.m_bsField[ getMatrixPos(xc, yr) ];
            bufView.piBoard[fi] = s_tblDecodeField[pi];
        }
    }

    for ( PieceIndex hp = 0; hp < NUM_IHAND_TYPES; ++ hp ) {
        const   Common::EHandPiece  hpiTrg  =  s_tblDecodeHands[hp];
        bufView.piHands[hp] = hpiTrg;
        bufView.hcHands[hp] = curStat.m_hcHands[hp];
    }

    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    指定した座標にある駒を取得する。
//

PieceIndex
BoardState::getFieldPiece(
        const  PosCol   xCol,
        const  PosRow   yRow)  const
{
    return ( getFieldPiece(this->m_icState, xCol, yRow) );
}

//----------------------------------------------------------------
//    指定した座標にある駒を取得する。
//

PieceIndex
BoardState::getFieldPiece(
        const  InternState  &curStat,
        const  PosCol       xCol,
        const  PosRow       yRow)
{
    return ( curStat.m_bsField[ getMatrixPos(xCol, yRow) ] );
}

//========================================================================
//
//    For Internal Use Only.
//

ErrCode
BoardState::getAttackFromList(
        const  InternState  &curStat,
        const  FieldIndex   posTrg,
        const  PlayerIndex  oPlayer,
        TBitBoard           &bbFrom)
{
    typedef     uint32_t        TablePiece[NUM_PIECE_TYPES];

    const  TablePiece  & tblFr  = RuleTables::s_tblMoveFrom[posTrg];
    for ( PieceIndex p = BOARD_BLACK_PAWN; p < NUM_PIECE_TYPES; ++ p )
    {
        //  指定されたプレーヤーの駒以外はスキップ。    //
        if ( s_tblPieceOwner[p] != oPlayer ) { continue; }

        //  可能性のある移動元を順に調べる。    //
        const  uint32_t  tvMask = tblFr[p];
        for ( FieldIndex posSrc = 0; posSrc < BOARD_SIZE; ++ posSrc )
        {
            //  対象の座標に目的の駒がない場合。    //
            if ( curStat.m_bsField[posSrc] != p )   { continue; }

            //  対象座標から指定座標に来られない。  //
            if ( ((tvMask >> posSrc) & 1) == 0 )    { continue; }

            //  飛び駒のブロック判定を行う。        //
            const  RuleTables::BitBoardVal
                pinMask = RuleTables::getPinMask(p, posTrg, posSrc);
            int     bPinOK  = 1;
            for ( int c = 0; c < BOARD_SIZE; ++ c ) {
                if ( ((pinMask >> c) & 1) == 0 ) { continue; }
                if ( curStat.m_bsField[c] != BOARD_EMPTY_SQUARE ) {
                    bPinOK  = 0;
                    break;
                }
            }   //  Next  c

            if ( bPinOK == 0 ) { continue; }

            bbFrom.push_back(posSrc);
        }   //  Next  posSrc
    }   //  Next  p

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    盤面の座標をインデックスに変換する。
//

inline  FieldIndex
BoardState::getMatrixPos(
        const   PosCol  xCol,
        const   PosRow  yRow)
{
    return ( (xCol * POS_NUM_ROWS) + yRow );
}

}   //  End of namespace  GAME
FAIRYSHOGI_NAMESPACE_END
