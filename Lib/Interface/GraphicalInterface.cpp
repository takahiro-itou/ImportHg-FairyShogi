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
**      An Implementation of GraphicalInterface class.
**
**      @file       Interface/GraphicalInterface.cpp
**/

#include    "FairyShogi/Interface/GraphicalInterface.h"

#include    "FairyShogi/Common/ActionView.h"

#include    <sstream>
#include    <windows.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

namespace  {

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
    BoardState::FIELD_EMPTY_SQUARE,

    BoardState::FIELD_BLACK_PR_PAWN,
    BoardState::FIELD_BLACK_PR_SILVER,
    BoardState::FIELD_BLACK_GOLD,
    BoardState::FIELD_BLACK_HORSE,
    BoardState::FIELD_BLACK_DRAGON,
    BoardState::FIELD_BLACK_KING,
    BoardState::FIELD_EMPTY_SQUARE,
    BoardState::FIELD_EMPTY_SQUARE,
    BoardState::FIELD_EMPTY_SQUARE,
    BoardState::FIELD_EMPTY_SQUARE,

    BoardState::FIELD_WHITE_PR_PAWN,
    BoardState::FIELD_WHITE_PR_SILVER,
    BoardState::FIELD_WHITE_GOLD,
    BoardState::FIELD_WHITE_HORSE,
    BoardState::FIELD_WHITE_DRAGON,
    BoardState::FIELD_WHITE_KING,
    BoardState::FIELD_EMPTY_SQUARE,
    BoardState::FIELD_EMPTY_SQUARE,
    BoardState::FIELD_EMPTY_SQUARE,
    BoardState::FIELD_EMPTY_SQUARE
};

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    ConsoleInterface  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

GraphicalInterface::GraphicalInterface()
    : Super()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

GraphicalInterface::~GraphicalInterface()
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
//    指定したマウス入力を、指し手データに変換する。
//

ErrCode
GraphicalInterface::setupMoveActionFromMouse(
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        PromoteList  *      vProms,
        ActionView   *      ptrAct)  const
{
    const  ShowCoordFlags      flgShow  =  getShowFlag();
    const  Game::BoardState  & curStat  =  getBoardState();

    ActionView  actTmp;
    if ( ptrAct == (nullptr) ) {
        ptrAct  =  &(actTmp);
    }

    ptrAct->xDispNewCol = xNewCol;
    ptrAct->yDispNewRow = yNewRow;
    convertCoordsFromMouse(
            flgShow,  xNewCol,  yNewRow,
            &(ptrAct->xPlayNewCol), &(ptrAct->yPlayNewRow) );

    ptrAct->xDispOldCol = xOldCol;
    ptrAct->yDispOldRow = yOldRow;
    convertCoordsFromMouse(
            flgShow,  xOldCol,  yOldRow,
            &(ptrAct->xPlayOldCol), &(ptrAct->yPlayOldRow) );

    ptrAct->fpCatch = curStat.getFieldPiece(
                            ptrAct->xPlayNewCol - 1,
                            ptrAct->yPlayNewRow - 1);
    ptrAct->fpMoved = curStat.getFieldPiece(
                            ptrAct->xPlayOldCol - 1,
                            ptrAct->yPlayOldRow - 1);
    ptrAct->fpAfter = (ptrAct->fpMoved);
    ptrAct->hpiDrop = Game::BoardState::HAND_EMPTY_PIECE;
    ptrAct->fLegals = Common::ALF_LEGAL_ACTION;

    vProms->clear();
    if ( (ptrAct->fpMoved) == Game::BoardState::FIELD_EMPTY_SQUARE ) {
        return ( ERR_FAILURE );
    }

    vProms->push_back(ptrAct->fpMoved);
    const  PieceIndex   piProm  =  s_tblPromotion[ptrAct->fpMoved];
    if ( piProm != Game::BoardState::FIELD_EMPTY_SQUARE ) {
        vProms->push_back(piProm);
    };

    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    指定したマウス入力を、指し手データに変換する。
//

ErrCode
GraphicalInterface::setupPutActionFromMouse(
        const  PosCol       xPutCol,
        const  PosRow       yPutRow,
        const  PieceIndex   pHand,
        PromoteList  *      vProms,
        ActionView   *      ptrAct)  const
{
    const  ShowCoordFlags      flgShow  =  getShowFlag();
    const  Game::BoardState  & curStat  =  getBoardState();

    ptrAct->xDispNewCol = xPutCol;
    ptrAct->yDispNewRow = yPutRow;
    convertCoordsFromMouse(
            flgShow,  xPutCol,  yPutRow,
            &(ptrAct->xPlayNewCol), &(ptrAct->yPlayNewRow) );

    ptrAct->xPlayOldCol = 0;
    ptrAct->yPlayOldRow = 0;
    ptrAct->xDispOldCol = 0;
    ptrAct->yDispOldRow = 0;
    ptrAct->fpCatch = curStat.getFieldPiece(
                            ptrAct->xPlayNewCol - 1,
                            ptrAct->yPlayNewRow - 1);
    ptrAct->fpMoved = Game::BoardState::FIELD_EMPTY_SQUARE;
    ptrAct->fpAfter = s_tblHandConv[pHand];
    ptrAct->hpiDrop = pHand;
    ptrAct->fLegals = Common::ALF_LEGAL_ACTION;

    vProms->clear();
    vProms->push_back(ptrAct->hpiDrop);

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
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    入力した座標を内部処理用に変換する。
//

ErrCode
GraphicalInterface::convertCoordsFromMouse(
        const   ShowCoordFlags  flgShow,
        const   PosCol          xInCol,
        const   PosRow          yInRow,
        PosCol  *   const       ptrCol,
        PosRow  *   const       ptrRow)
{
    PosCol  xColTmp = xInCol;
    PosRow  yRowTmp = yInRow;

    //  マウス入力では、左上を (0, 0) とする座標系である。  //
    //  これは画面を回転させている場合でもそのままである。  //
    //  この場合には、入力値を内部で扱う座標系に戻す。      //
    if ( (flgShow) & SCF_ROTATE_BOARD ) {
        //  回転を戻す場合の処理。                          //
        //  変換：0 -> 4, 1 -> 3, 2 -> 2, 3 -> 1, 4 -> 0    //
        xColTmp =  (Game::BoardState::POS_NUM_COLS - 1 - xColTmp);
        yRowTmp =  (Game::BoardState::POS_NUM_ROWS - 1 - yRowTmp);
    }

    //  マウス入力では、左上を (0, 0) とする座標系である。  //
    //  従って、水平方向の座標を反転させなければならない。  //
    //                                                      //
    //  なお、水平方向の反転表示フラグは無視して構わない。  //
    //  マウス入力処理に関しては、常に左端がゼロであり、    //
    //  受け付ける内部形に於いては、常に右端が壱である。    //
    //  反転表示フラグに関係なく、反転させる必要がある。    //
    //  変換：0 -> 5, 1 -> 4, 2 -> 3, 3 -> 2, 1 -> 4.       //
    (* ptrCol)  =  (Game::BoardState::POS_NUM_COLS - xColTmp);
    (* ptrRow)  =  (yRowTmp + 1);

    return ( ERR_FAILURE );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
