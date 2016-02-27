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
**      An Implementation of GameController class.
**
**      @file       Interface/GameController.cpp
**/

#include    "FairyShogi/Interface/GameController.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/ViewBuffer.h"

#include    <ostream>
#include    <stdlib.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

namespace  {

/**
**    棋譜に表示する駒の名称。
**/

constexpr   const   char  *
s_tblPieceName[]    = {
    "",
    "+Pawn",  "+Silver",  "+Gold",  "+Bishop",  "+Rook",  "+King",
    "+Tokin", "+NariGin", "+Uma",   "+Ryu",
    "-Pawn",  "-Silver",  "-Gold",  "-Bishop",  "-Rook",  "-King",
    "-Tokin", "-NariGin", "-Uma",   "-Ryu"
};

/**
**    持ち駒の名前。
**/

CONSTEXPR_VAR   const   char
s_tblHandName[Game::BoardState::NUM_HAND_TYPES] = {
    'W',
    'P',  'S',  'G',  'B',  'R',  'K',
    'p',  's',  'g',  'b',  'r',  'k'
};

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
    0,
    BoardState::FIELD_BLACK_PR_PAWN,
    BoardState::FIELD_BLACK_PR_SILVER,
    BoardState::FIELD_BLACK_GOLD,
    BoardState::FIELD_BLACK_HORSE,
    BoardState::FIELD_BLACK_DRAGON,
    BoardState::FIELD_BLACK_KING,
    BoardState::FIELD_BLACK_PR_PAWN,
    BoardState::FIELD_BLACK_PR_SILVER,
    BoardState::FIELD_BLACK_HORSE,
    BoardState::FIELD_BLACK_DRAGON,

    BoardState::FIELD_WHITE_PR_PAWN,
    BoardState::FIELD_WHITE_PR_SILVER,
    BoardState::FIELD_WHITE_GOLD,
    BoardState::FIELD_WHITE_HORSE,
    BoardState::FIELD_WHITE_DRAGON,
    BoardState::FIELD_WHITE_KING,
    BoardState::FIELD_WHITE_PR_PAWN,
    BoardState::FIELD_WHITE_PR_SILVER,
    BoardState::FIELD_WHITE_HORSE,
    BoardState::FIELD_WHITE_DRAGON,
};

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    GameController  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

GameController::GameController()
    : m_gcBoard(),
      m_actList(),
      m_flgShow(SCF_NORMAL_SHOW),
      m_curTurn(0),
      m_curDice(0)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

GameController::~GameController()
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
//    現在の局面の合法手を列挙する。
//

ErrCode
GameController::makeLegalActionList(
        ActionDataList  &actList)  const
{
    return ( this->m_gcBoard.makeLegalActionList(
                     this->m_curTurn, 0, actList) );
}

//----------------------------------------------------------------
//    現在の局面の合法手を列挙する。
//

ErrCode
GameController::makeLegalActionList(
        const   ActionFlag  fLegals,
        const   int         vCons,
        ActionViewList      &actList)  const
{
    typedef     ActionDataList::const_iterator      ActIter;

    //  まず、全ての合法手を列挙する。  //
    ActionDataList  vActs;
    const  ErrCode
        retErr  = this->m_gcBoard.makeLegalActionList(
                        this->m_curTurn,  fLegals,  vActs);

    actList.clear();
    actList.reserve( vActs.size() );

    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    const  ActIter  itrEnd  = vActs.end();
    ActIter         itrHead = vActs.begin();
    ActIter         itrTail = itrEnd;

    //  合法手のリストは、内部の座標系で昇順ソートされている。  //
    //  従って、ダイスの目を内部形式に合わせてから比較を行う。  //
    const  TConstraint  curDice = convertConstraintCoord(
            this->m_flgShow, (vCons < 0 ? (this->m_curDice) : vCons) );

    ActionView      actView;

    for ( ; itrHead != itrEnd; ++ itrHead ) {
        //  ダイスの目を内部形式に揃えているので、  //
        //  比較の時は、座標を反転させないで行う。  //
        decodeActionData( SCF_NORMAL_SHOW, (* itrHead), &actView );
        if ( (actView.xNewCol) >= curDice ) {
            break;
        }
    }

    for ( ActIter itr = itrHead; itr != itrEnd; ++ itr ) {
        //  ダイスの目を内部形式に揃えているので、  //
        //  比較の時は、座標を反転させないで行う。  //
        decodeActionData( SCF_NORMAL_SHOW, (* itr), &actView );
        if ( (actView.xNewCol) != curDice ) {
            itrTail = itr;
            break;
        }
    }
    if ( itrHead == itrTail ) {
        //  指定した条件で合法手がない時は、何でもできる。  //
        itrHead = vActs.begin();
        itrTail = itrEnd;
    }

    for ( ActIter itr = itrHead; itr != itrTail; ++ itr ) {
        //  今度は表示を行うので、必要なら座標を反転する。  //
        decodeActionData( this->m_flgShow, (* itr), &actView);
        actList.push_back(actView);
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    指定した入力文字列を、指し手データに変換する。
//

ErrCode
GameController::parseActionText(
        const  std::string  &strPlay,
        ActionView  *       ptrAct)  const
{
    PieceIndex  pifSrc  =  Game::BoardState::FIELD_EMPTY_SQUARE;
    PieceIndex  pifTrg  =  Game::BoardState::FIELD_EMPTY_SQUARE;

    {
        PosCol  xNewCol = strPlay[2] - '0';
        PosRow  yNewRow = strPlay[3] - '0';
        if (       (xNewCol < 1) || (5 < xNewCol)
                || (yNewRow < 1) || (5 < yNewRow) )
        {
            return ( ERR_FAILURE );
        }
        convertCoordsFromConsole(this->m_flgShow, &xNewCol, &yNewRow);
        ptrAct->xNewCol = xNewCol;
        ptrAct->yNewRow = yNewRow;
        pifTrg  = getBoardState().getFieldPiece(xNewCol - 1, yNewRow - 1);
    }

    //  移動先にある駒を捕獲する。  //
    ptrAct->fpCatch = pifTrg;

    if ( strPlay[1] == '*' ) {
        //  持ち駒を打つ。  //
        ptrAct->xOldCol = 0;
        ptrAct->yOldRow = 0;
        ptrAct->fpAfter = Game::BoardState::FIELD_EMPTY_SQUARE;
        ptrAct->fpMoved = Game::BoardState::FIELD_EMPTY_SQUARE;
        ptrAct->putHand = Game::BoardState::HAND_EMPTY_PIECE;

        for ( int i = 0; i < Game::BoardState::NUM_HAND_TYPES; ++ i ) {
            if ( strPlay[0] == s_tblHandName[i] ) {
                ptrAct->putHand = i;
                pifSrc  = s_tblHandConv[i];
                break;
            }
        }
    } else {
        PosCol  xOldCol = strPlay[0] - '0';
        PosRow  yOldRow = strPlay[1] - '0';
        if (       (xOldCol < 1) || (5 < xOldCol)
                || (yOldRow < 1) || (5 < yOldRow) )
        {
            return ( ERR_FAILURE );
        }

        convertCoordsFromConsole(this->m_flgShow, &xOldCol, &yOldRow);
        ptrAct->xOldCol = xOldCol;
        ptrAct->yOldRow = yOldRow;
        pifSrc  = getBoardState().getFieldPiece(xOldCol - 1, yOldRow - 1);
        ptrAct->fpMoved = pifSrc;
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

//----------------------------------------------------------------
//    指定した指し手で盤面を進める。
//

ErrCode
GameController::playForward(
        const  ActionView   &actFwd)
{
    ErrCode     retErr  = ERR_SUCCESS;
    ActionData  actData;

    retErr  =  BoardState::encodeActionData(actFwd, &actData);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    return ( this->m_gcBoard.playForward(actData) );
}

//----------------------------------------------------------------
//    駒を移動する指し手を入力して盤面を進める。
//

ErrCode
GameController::playMoveAction(
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        const  PieceIndex   flgProm)
{
    const  Game::BoardState::ActionData
        act = this->m_gcBoard.encodeMoveAction(
                    xOldCol, yOldRow, xNewCol, yNewRow, flgProm);

    const  ErrCode  retErr  = this->m_gcBoard.playForward(act);

    if ( retErr == ERR_SUCCESS ) {
        this->m_actList.push_back(act);
    }

    return ( retErr );
}

//----------------------------------------------------------------
//    持ち駒を打つ指し手を入力して盤面を進める。
//

ErrCode
GameController::playPutAction(
        const  PosCol       xPutCol,
        const  PosRow       yPutRow,
        const  PieceIndex   pHand)
{
    const  Game::BoardState::ActionData
        act = this->m_gcBoard.encodePutAction(
                    xPutCol, yPutRow, pHand);

    const  ErrCode  retErr  = this->m_gcBoard.playForward(act);

    if ( retErr == ERR_SUCCESS ) {
        this->m_actList.push_back(act);
    }

    return ( retErr );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
GameController::resetGame()
{
    return ( this->m_gcBoard.resetGameBoard() );
}

//----------------------------------------------------------------
//    指定したマウス入力を、指し手データに変換する。
//

ErrCode
GameController::setupMoveActionFromMouse(
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        PromoteList  *      vProms,
        ActionView   *      ptrAct)  const
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    指定したマウス入力を、指し手データに変換する。
//

ErrCode
GameController::setupPutActionFromMouse(
        const  PosCol       xPutCol,
        const  PosRow       yPutRow,
        const  PieceIndex   pHand,
        PromoteList  *      vProms,
        ActionView   *      ptrAct)  const
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    コンピュータの思考を開始する。
//

ErrCode
GameController::startThinking(
        ActionView  &actRet)
{
    ActionViewList  actList;

    makeLegalActionList(0,  this->m_curDice,  actList);
    const  int  numAct  = actList.size();
    if ( numAct == 0 ) {
        return ( ERR_ILLEGAL_ACTION );
    }

    int  r  =  rand() % numAct;
    actRet  =  actList[r];

    return ( ERR_SUCCESS );
}


//----------------------------------------------------------------
//    表示用棋譜データの内容をストリームに出力する。
//

std::ostream  &
GameController::writeActionView(
        const  ActionView   &actView,
        std::ostream        &outStr)
{
    outStr  <<  (5 - actView.xNewCol)
            <<  (actView.yNewRow + 1)
            <<  ' '
            <<  s_tblPieceName[actView.fpAfter];
    if ( (actView.putHand) == 0 ) {
        outStr  <<  " ("
                <<  (5 - actView.xOldCol)
                <<  (actView.yOldRow + 1)
                <<  ")";
        if ( (actView.fpAfter) != (actView.fpMoved) ) {
            outStr  <<  " (PROMOTE)";
        }
    } else {
        outStr  <<  " (PUT)";
    }

    return ( outStr );
}

//----------------------------------------------------------------
//    棋譜データを表示用に変換する。
//

ErrCode
GameController::writeActionList(
        ActionViewList  &actList)  const
{
    typedef     ActionDataList::const_iterator  ActIter;

    const  ActionDataList  &obj = (this->m_actList);

    actList.clear();
    actList.resize(obj.size());

    size_t          idx     = 0;
    const  ActIter  itrEnd  = obj.end();
    for ( ActIter itr = obj.begin(); itr != itrEnd; ++ itr, ++ idx )
    {
        this->m_gcBoard.decodeActionData( *itr, &actList[idx] );
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    現在の盤面を表示用バッファにコピーする。
//

ErrCode
GameController::writeToViewBuffer(
        Common::ViewBuffer  &bufView)  const
{
    return ( this->m_gcBoard.copyToViewBuffer(bufView) );
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    指し手の表示用形式を比較して、等しいかどうかを返す。
//

bool
GameController::isEquals(
        const  ActionView  &avLhs,
        const  ActionView  &avRhs)
{
    if (       ( (avLhs.xNewCol) != (avRhs.xNewCol) )
            || ( (avLhs.yNewRow) != (avRhs.yNewRow) )
            || ( (avLhs.xOldCol) != (avRhs.xOldCol) )
            || ( (avLhs.yOldRow) != (avRhs.yOldRow) )
            || ( (avLhs.fpMoved) != (avRhs.fpMoved) )
            || ( (avLhs.fpAfter) != (avRhs.fpAfter) )
            || ( (avLhs.putHand) != (avRhs.putHand) )
            || ( (avLhs.fpCatch) != (avRhs.fpCatch) )
    )
    {
        return ( false );
    }
    return ( true );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    現在の盤面の状態を取得する。
//

const   Game::BoardState  &
GameController::getBoardState()  const
{
    return ( this->m_gcBoard );
}

//----------------------------------------------------------------
//    合法手の制約を取得する。
//

GameController::TConstraint
GameController::getConstraint()  const
{
    return ( this->m_curDice );
}

//----------------------------------------------------------------
//    合法手の制約を指定する。
//

ErrCode
GameController::setConstraint(
        const  TConstraint  vCons)
{
    this->m_curDice = vCons;
    return ( ERR_SUCCESS );
}


//----------------------------------------------------------------
//    現在の手番を持つプレーヤーを取得する。
//

PlayerIndex
GameController::getCurrentPlayer()  const
{
    return ( this->m_curTurn );
}

//----------------------------------------------------------------
//    現在の手番を持つプレーヤーを設定する。
//

ErrCode
GameController::setCurrentPlayer(
        const  PlayerIndex  cPlayer)
{
    this->m_curTurn = cPlayer;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    現在の盤面の表示フラグを取得する。
//

GameController::ShowCoordFlags
GameController::getShowFlag()  const
{
    return ( this->m_flgShow );
}

//----------------------------------------------------------------
//    盤面の表示フラグを設定する。
//

ErrCode
GameController::setShowFlag(
        const   ShowCoordFlags  scFlag)

{
    this->m_flgShow = scFlag;
    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    入力した座標を内部処理用に変換する。
//

ErrCode
GameController::convertCoordsFromConsole(
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

//----------------------------------------------------------------
//    入力したダイスの出目を、内部処理用に変換する。
//

GameController::TConstraint
GameController::convertConstraintCoord(
        const   ShowCoordFlags  flgShow,
        const   TConstraint     vCons)
{
    if ( (flgShow) & SCF_FLIP_COLUMNS ) {
        //  水平方向の座標を反転させる。ただし六を除く。    //
        //  つまり、123456 -> 543216 となるように変換する。 //
        return ( vCons < 6 ? (6 - vCons) : 6 );
    }

    //  水平方向の座標をそのまま使う。      //
    return ( vCons );
}

//----------------------------------------------------------------
//    入力した座標を内部処理用に変換する。
//

ErrCode
GameController::convertCoordsFromMouse(
        const   ShowCoordFlags  flgShow,
        PosCol  *   const       ptrCol,
        PosRow  *   const       ptrRow)
{
}

//----------------------------------------------------------------
//    指し手の内部形式を表示用データに変換する。
//

ErrCode
GameController::decodeActionData(
        const   ShowCoordFlags  flgShow,
        const   ActionData   &  actData,
        ActionView  *  const    pvAct)
{
    //  指し手の内部形式を表示用データに変換。  //
    const  ErrCode
        retErr  = Game::BoardState::decodeActionData( actData, pvAct );
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    //  表示フラグを確認して座標の調整を行う。  //
    if ( (flgShow) & SCF_FLIP_COLUMNS ) {
        //  水平方向の座標を反転させる。    //
        pvAct->xNewCol  = (6 - (pvAct->xNewCol));
        pvAct->xOldCol  = (6 - (pvAct->xOldCol));
    };

    return ( ERR_SUCCESS );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
