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

#include    "FairyShogi/Common/ActionView.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Game  {

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
//    指し手の内部形式を表示用データに変換する。
//

ErrCode
BoardState::decodeActionData(
        const   ActionData   &  actData,
        Common::ActionView  *   actView)
{
    actView->xNewCol    = actData.xNewCol;
    actView->yNewRow    = actData.yNewRow;
    actView->xOldCol    = actData.xOldCol;
    actView->yOldRow    = actData.yOldRow;
    actView->fpAfter    = actData.fpAfter;
    actView->fpMoved    = actData.fpMoved;
    actView->fpCatch    = actData.fpCatch;
    actView->putHand    = actData.putHand;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    駒を移動する指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodeMoveAction(
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        const  PieceIndex   flgProm)  const
{
    return ( encodeMoveAction(
                     this->m_icState,
                     xOldCol, yOldRow, xNewCol, yNewRow,
                     flgProm) );
}

//----------------------------------------------------------------
//    駒を移動する指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodeMoveAction(
        const  InternState  &curStat,
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        const  PieceIndex   flgProm)
{
    const  PieceIndex   piPrev  = curStat.m_bsField[
            getMatrixPos(xOldCol, yOldRow) ];

    ActionData  act = {
        xNewCol,    yNewRow,
        xOldCol,    yOldRow,
        curStat.m_bsField[getMatrixPos(xNewCol, yNewRow)],
        piPrev,
        flgProm,
        FIELD_EMPTY_SQUARE
    };

    return ( act );
}

//----------------------------------------------------------------
//    持ち駒を打つ指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodePutAction(
        const  PosCol       xPutCol,
        const  PosRow       yPutRow,
        const  PieceIndex   pHand)  const
{
    return ( encodePutAction(this->m_icState, xPutCol, yPutRow, pHand) );
}

//----------------------------------------------------------------
//    持ち駒を打つ指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodePutAction(
        const  InternState  &curStat,
        const  PosCol       xPutCol,
        const  PosRow       yPutRow,
        const  PieceIndex   pHand)
{
    constexpr   PieceIndex  s_tblHandConv[] = {
        FIELD_EMPTY_SQUARE,

        FIELD_BLACK_PAWN,
        FIELD_BLACK_SILVER,
        FIELD_BLACK_GOLD,
        FIELD_BLACK_BISHOP,
        FIELD_BLACK_ROOK,
        FIELD_BLACK_KING,

        FIELD_WHITE_PAWN,
        FIELD_WHITE_SILVER,
        FIELD_WHITE_GOLD,
        FIELD_WHITE_BISHOP,
        FIELD_WHITE_ROOK,
        FIELD_WHITE_KING
    };

    const   ActionData  act = {
        xPutCol,    yPutRow,
        -1,         -1,
        curStat.m_bsField[ getMatrixPos(xPutCol, yPutRow) ],
        FIELD_EMPTY_SQUARE,
        s_tblHandConv[pHand],
        pHand
    };

    return ( act );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を進める。
//

ErrCode
BoardState::playForward(
        const  ActionData   &actFwd)
{
    InternState  & icSt = (this->m_icState);

    constexpr   PieceIndex  piCatchTable[]  = {
        HAND_EMPTY_PIECE,

        HAND_WHITE_PAWN,
        HAND_WHITE_SILVER,
        HAND_WHITE_GOLD,
        HAND_WHITE_BISHOP,
        HAND_WHITE_ROOK,
        HAND_WHITE_KING,
        HAND_WHITE_PAWN,
        HAND_WHITE_SILVER,
        HAND_WHITE_BISHOP,
        HAND_WHITE_ROOK,

        HAND_BLACK_PAWN,
        HAND_BLACK_SILVER,
        HAND_BLACK_GOLD,
        HAND_BLACK_BISHOP,
        HAND_BLACK_ROOK,
        HAND_BLACK_KING,
        HAND_BLACK_PAWN,
        HAND_BLACK_SILVER,
        HAND_BLACK_BISHOP,
        HAND_BLACK_ROOK
    };

    //  移動元のマスを空きマスにする。  //
    if ( (actFwd.fpMoved) != FIELD_EMPTY_SQUARE ) {
        icSt.m_bsField[ getMatrixPos(actFwd.xOldCol, actFwd.yOldRow) ]
                = FIELD_EMPTY_SQUARE;
    }

    //  移動先に指定した駒を書き込む。  //
    icSt.m_bsField[ getMatrixPos(actFwd.xNewCol, actFwd.yNewRow) ]
            = actFwd.fpAfter;

    //  取った相手の駒を持ち駒にする。  //
    if ( actFwd.fpCatch != FIELD_EMPTY_SQUARE ) {
        const  PieceIndex   piHand  = piCatchTable[actFwd.fpCatch];
        ++  icSt.m_nHands[piHand];
    }

    //  駒を打つ場合は持ち駒を減らす。  //
    if ( actFwd.putHand != HAND_EMPTY_PIECE ) {
        --  icSt.m_nHands[actFwd.putHand];
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
    for ( int i = 0; i < POS_NUM_ROWS * POS_NUM_COLS; ++ i ) {
        pCurStat->m_bsField[i]  = FIELD_EMPTY_SQUARE;
    }

    pCurStat->m_bsField[getMatrixPos(0, 0)] = FIELD_WHITE_ROOK;
    pCurStat->m_bsField[getMatrixPos(1, 0)] = FIELD_WHITE_BISHOP;
    pCurStat->m_bsField[getMatrixPos(2, 0)] = FIELD_WHITE_SILVER;
    pCurStat->m_bsField[getMatrixPos(3, 0)] = FIELD_WHITE_GOLD;
    pCurStat->m_bsField[getMatrixPos(4, 0)] = FIELD_WHITE_KING;
    pCurStat->m_bsField[getMatrixPos(4, 1)] = FIELD_WHITE_PAWN;

    pCurStat->m_bsField[getMatrixPos(0, 3)] = FIELD_BLACK_PAWN;
    pCurStat->m_bsField[getMatrixPos(0, 4)] = FIELD_BLACK_KING;
    pCurStat->m_bsField[getMatrixPos(1, 4)] = FIELD_BLACK_GOLD;
    pCurStat->m_bsField[getMatrixPos(2, 4)] = FIELD_BLACK_SILVER;
    pCurStat->m_bsField[getMatrixPos(3, 4)] = FIELD_BLACK_BISHOP;
    pCurStat->m_bsField[getMatrixPos(4, 4)] = FIELD_BLACK_ROOK;

    for ( int hp = 0; hp < NUM_HAND_TYPES; ++ hp ) {
        pCurStat->m_nHands[hp]  = 0;
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
    for ( int yr = 0; yr < POS_NUM_ROWS; ++ yr ) {
        for ( int xc = 0; xc < POS_NUM_COLS; ++ xc ) {
            const  int  pi  = (yr * POS_NUM_COLS) + (xc);
            bufView.piBoard[pi] = curStat.m_bsField[getMatrixPos(xc, yr)];
        }
    }

    for ( int hp = 0; hp < NUM_HAND_TYPES; ++ hp ) {
        bufView.nHands[hp]  = curStat.m_nHands[hp];
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

//----------------------------------------------------------------
//    盤面の座標をインデックスに変換する。
//

inline  FieldIndex
BoardState::getMatrixPos(
        const   PosCol  xCol,
        const   PosRow  yRow)
{
    return ( ((POS_NUM_COLS - xCol - 1) * POS_NUM_ROWS) + yRow );
}

}   //  End of namespace  GAME
FAIRYSHOGI_NAMESPACE_END
