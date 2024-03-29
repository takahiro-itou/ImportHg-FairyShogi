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
**      An Implementation of ConsoleInterface class.
**
**      @file       Interface/ConsoleInterface.cpp
**/

#include    "FairyShogi/Interface/ConsoleInterface.h"

#include    "FairyShogi/Common/ActionView.h"

#include    <memory.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

namespace  {

/**
**    持ち駒の名前。
**/

CONSTEXPR_VAR   const   char
s_tblHandName[Common::NUM_HAND_TYPES]  =  {
    'W',
    'P',  'L',  'N',  'S',  'G',  'B',  'R',  'K',
    'p',  'l',  'n',  's',  'g',  'b',  'r',  'k'
};

using   Game::BoardState;

CONSTEXPR_VAR   const   Common::EFieldPiece
s_tblPromotion[Common::NUM_FIELD_PIECE_TYPES]  =  {
    Common::FIELD_EMPTY_SQUARE,

    Common::FIELD_BLACK_PR_PAWN,
    Common::FIELD_BLACK_PR_LANCE,
    Common::FIELD_BLACK_PR_KNIGHT,
    Common::FIELD_BLACK_PR_SILVER,
    Common::FIELD_BLACK_GOLD,
    Common::FIELD_BLACK_PR_BISHOP,
    Common::FIELD_BLACK_PR_ROOK,
    Common::FIELD_BLACK_KING,
    Common::FIELD_BLACK_PR_PAWN,
    Common::FIELD_BLACK_PR_LANCE,
    Common::FIELD_BLACK_PR_KNIGHT,
    Common::FIELD_BLACK_PR_SILVER,
    Common::FIELD_BLACK_PR_BISHOP,
    Common::FIELD_BLACK_PR_ROOK,

    Common::FIELD_WHITE_PR_PAWN,
    Common::FIELD_WHITE_PR_LANCE,
    Common::FIELD_WHITE_PR_KNIGHT,
    Common::FIELD_WHITE_PR_SILVER,
    Common::FIELD_WHITE_GOLD,
    Common::FIELD_WHITE_PR_BISHOP,
    Common::FIELD_WHITE_PR_ROOK,
    Common::FIELD_WHITE_KING,
    Common::FIELD_WHITE_PR_PAWN,
    Common::FIELD_WHITE_PR_LANCE,
    Common::FIELD_WHITE_PR_KNIGHT,
    Common::FIELD_WHITE_PR_SILVER,
    Common::FIELD_WHITE_PR_BISHOP,
    Common::FIELD_WHITE_PR_ROOK
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

ConsoleInterface::ConsoleInterface()
    : Super()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ConsoleInterface::~ConsoleInterface()
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
//    指定した入力文字列を、指し手データに変換する。
//

ErrCode
ConsoleInterface::parseActionText(
        const  std::string  &strPlay,
        ActionView  *       ptrAct)  const
{
    if ( strPlay.length() < 4 ) {
        return ( ERR_INVALID_COMMAND );
    }

    Common::EFieldPiece     pifSrc  =  Common::FIELD_EMPTY_SQUARE;
    Common::EFieldPiece     pifTrg  =  Common::FIELD_EMPTY_SQUARE;
    const  BoardState   &   curStat =  getBoardState();
    const  ShowCoordFlags   flgShow =  getShowFlag();

    ::memset( ptrAct, 0, sizeof(ActionView) );

    {
        PosCol  xNewCol = strPlay[2] - '0';
        PosRow  yNewRow = strPlay[3] - '0';
        if (       (xNewCol < 1) || (5 < xNewCol)
                || (yNewRow < 1) || (5 < yNewRow) )
        {
            return ( ERR_INVALID_COMMAND );
        }

        ptrAct->xDispNewCol = xNewCol;
        ptrAct->yDispNewRow = yNewRow;

        convertCoordsFromConsole(flgShow, &xNewCol, &yNewRow);
        ptrAct->xPlayNewCol = xNewCol;
        ptrAct->yPlayNewRow = yNewRow;

        pifTrg  =  curStat.decodeFieldPiece(xNewCol - 1, yNewRow - 1);
    }

    //  移動先にある駒を捕獲する。  //
    ptrAct->fpCatch = pifTrg;

    if ( strPlay[1] == '*' ) {
        //  持ち駒を打つ。  //
        ptrAct->xDispOldCol = 0;
        ptrAct->yDispOldRow = 0;
        ptrAct->xPlayOldCol = 0;
        ptrAct->yPlayOldRow = 0;

        ptrAct->fpAfter = Common::FIELD_EMPTY_SQUARE;
        ptrAct->fpMoved = Common::FIELD_EMPTY_SQUARE;
        ptrAct->hpiDrop = Common::HAND_EMPTY_PIECE;

        for ( int i = 0; i < Common::NUM_HAND_TYPES; ++ i ) {
            if ( strPlay[0] == s_tblHandName[i] ) {
                ptrAct->hpiDrop = i;
                pifSrc  =  s_tblHandConv[i];
                break;
            }
        }
        if ( ptrAct->hpiDrop == Common::HAND_EMPTY_PIECE ) {
            return ( ERR_INVALID_COMMAND );
        }

    } else {
        //  盤上の駒を移動させる。  //
        PosCol  xOldCol = strPlay[0] - '0';
        PosRow  yOldRow = strPlay[1] - '0';
        if (       (xOldCol < 1) || (5 < xOldCol)
                || (yOldRow < 1) || (5 < yOldRow) )
        {
            return ( ERR_FAILURE );
        }

        ptrAct->xDispOldCol = xOldCol;
        ptrAct->yDispOldRow = yOldRow;

        convertCoordsFromConsole(flgShow, &xOldCol, &yOldRow);
        ptrAct->xPlayOldCol = xOldCol;
        ptrAct->yPlayOldRow = yOldRow;

        pifSrc  =  curStat.decodeFieldPiece(xOldCol - 1, yOldRow - 1);
        ptrAct->fpMoved = pifSrc;
        ptrAct->hpiDrop = Common::HAND_EMPTY_PIECE;
    }

    size_t  posRead = 4;
    if ( (strPlay.length() > posRead) && (strPlay[posRead] == '+') ) {
        ptrAct->fpAfter = s_tblPromotion[pifSrc];
    } else {
        ptrAct->fpAfter = pifSrc;
    }
    ptrAct->fLegals = Common::ALF_LEGAL_ACTION;

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
ConsoleInterface::convertCoordsFromConsole(
        const   ShowCoordFlags  flgShow,
        PosCol  *   const       ptrCol,
        PosRow  *   const       ptrRow)
{
    PosCol  xColTmp = (* ptrCol);
    PosRow  yRowTmp = (* ptrRow);

    if ( (flgShow) & SCF_FLIP_COLUMNS ) {
        //  水平方向の座標を反転させる。        //
        //  入力が 1..5 で出力が 5..1 である。  //
        xColTmp = (6 - xColTmp);
    }

    (* ptrCol)  = xColTmp;
    (* ptrRow)  = yRowTmp;

    return ( ERR_SUCCESS );

}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
