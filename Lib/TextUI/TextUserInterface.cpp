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
**      An Implementation of TextUserInterface class.
**
**      @file       TextUI/TextUserInterface.cpp
**/

#include    "FairyShogi/TextUI/TextUserInterface.h"

#include    <memory.h>
#include    <sstream>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  TextUI  {

namespace  {

CONSTEXPR_VAR   const   char  *
s_tblPieceName[]    = {
    "  ",
    " P",  " L",  " N",  " S",  " G",  " B",  " R",  " K",
    "+P",  "+L",  "+N",  "+S",         "+B",  "+R",
    " p",  " l",  " n",  " s",  " g",  " b",  " r",  " k",
    "+p",  "+l",  "+n",  "+s",         "+b",  "+r"
};

CONSTEXPR_VAR   const   char  *
s_tblPieceName2[]   = {
    "W",
    "P" ,  "L",  "N",  "S",  "G",  "B",  "R",  "K",
    "+P", "+L", "+N", "+S",       "+B", "+R",
    "p" ,  "l",  "n",  "s",  "g",  "b",  "r",  "k",
    "+p", "+l", "+n", "+s",       "+b", "+r"
};

CONSTEXPR_VAR   const   char  *
s_tblHandName[]     = {
    "WALL",
    "P", "L", "N", "S", "G", "B", "R", "K",
    "p", "l", "n", "s", "g", "b", "r", "k"
};

CONSTEXPR_VAR   Common::EHandPiece
s_tblHandEncBlack[] = {
    Common::HAND_BLACK_PAWN,
    Common::HAND_BLACK_SILVER,
    Common::HAND_BLACK_GOLD,
    Common::HAND_BLACK_BISHOP,
    Common::HAND_BLACK_ROOK,
    Common::HAND_BLACK_KING
};

CONSTEXPR_VAR   Common::EHandPiece
s_tblHandEncWhite[] = {
    Common::HAND_WHITE_PAWN,
    Common::HAND_WHITE_SILVER,
    Common::HAND_WHITE_GOLD,
    Common::HAND_WHITE_BISHOP,
    Common::HAND_WHITE_ROOK,
    Common::HAND_WHITE_KING
};

CONSTEXPR_VAR   const  char  *
s_tblPlayerNames[]  =  {
    "BLACK",
    "WHITE"
};

CONSTEXPR_VAR   RankRow     CURSOR_ROW_FIELD_FIRST  =  1;
CONSTEXPR_VAR   RankRow     CURSOR_ROW_WHITE_HANDS  =  0;
CONSTEXPR_VAR   RankRow     CURSOR_ROW_BLACK_HANDS  =  6;
CONSTEXPR_VAR   FileCol     CURSOR_COL_FIELD_FIRST  =  0;

CONSTEXPR_VAR   RankRow     FIELD_NUM_Y_ROWS        =  5;
CONSTEXPR_VAR   FileCol     FIELD_NUM_X_COLS        =  5;

CONSTEXPR_VAR   int         FIELD_LEFT_MARGIN       =  4;
CONSTEXPR_VAR   int         FIELD_TOP_MARGIN        =  3;
CONSTEXPR_VAR   int         FIELD_PIECE_WIDTH       =  5;
CONSTEXPR_VAR   int         FIELD_PIECE_HEIGHT      =  3;

CONSTEXPR_VAR   PieceIndex  HANDS_NUM_PIECE_TYPES   =  5;
CONSTEXPR_VAR   int         HANDS_LEFT_MARGIN       =  3;
CONSTEXPR_VAR   int         HANDS_TOP_MARGIN        =  2;
CONSTEXPR_VAR   int         HANDS_PIECE_WIDTH       =  5;

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    TextUserInterface  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

TextUserInterface::TextUserInterface()
    : m_giGameCtrl(),
      m_rndGen(),
      m_flgInitScr(BOOL_FALSE),
      m_wScreen(nullptr),
      m_wBoard (nullptr),
      m_wHands (),
      m_wInfos (nullptr),
      m_yCurRow(FIELD_NUM_Y_ROWS / 2 + CURSOR_ROW_FIELD_FIRST),
      m_xCurCol(FIELD_NUM_Y_ROWS / 2 + CURSOR_COL_FIELD_FIRST),
      m_ySrcRow(-1),
      m_xSrcCol(-1),
      m_yTrgRow(-1),
      m_xTrgCol(-1)
{
    this->m_giGameCtrl.resetGame();
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

TextUserInterface::~TextUserInterface()
{
    cleanupScreen();
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
//    端末座標に対応する内部座標を計算する。
//

ErrCode
TextUserInterface::computeCursorPosition(
        const  CursorCoord  sY,
        const  CursorCoord  sX,
        WINDOW  *        &  cW,
        RankRow          &  cY,
        FileCol          &  cX)  const
{
    CursorCoord     wX,  wY;

    //  盤面ウィンドウの中か？  //
    if ( checkCoordInWindow(this->m_wBoard, sY, sX, wY, wX) )
    {
        cW  =  (this->m_wBoard);
        cY  =  (wY - 2) / FIELD_PIECE_HEIGHT + CURSOR_ROW_FIELD_FIRST;
        cX  =  (wX - 3) / FIELD_PIECE_WIDTH;
        return ( ERR_SUCCESS );
    }

    //  先手（黒）の持ち駒ウィンドウの中か？。  //
    if ( checkCoordInWindow(this->m_wHands[0], sY, sX, wY, wX) )
    {
        cW  =  (this->m_wHands[0]);
        cY  =  CURSOR_ROW_BLACK_HANDS;
        cX  =  (wX - 1) / HANDS_PIECE_WIDTH;
        return ( ERR_SUCCESS );
    }

    //  後手（白）の持ち駒ウィンドウの中か？。  //
    if ( checkCoordInWindow(this->m_wHands[1], sY, sX, wY, wX) )
    {
        cW  =  (this->m_wHands[1]);
        cY  =  CURSOR_ROW_WHITE_HANDS;
        cX  =  (wX - 1) / HANDS_PIECE_WIDTH;
        return ( ERR_SUCCESS );
    }

    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    カーソルを表示する端末座標を計算する。
//

ErrCode
TextUserInterface::computeScreenPosition(
        CursorCoord  &  sY,
        CursorCoord  &  sX,
        WINDOW  *    &  cW,
        CursorCoord  &  wY,
        CursorCoord  &  wX)  const
{
    WINDOW  *   wCurIn  =  nullptr;
    int         tY,  tX;
    int         oY,  oX;

    if ( (this->m_yCurRow) == CURSOR_ROW_WHITE_HANDS ) {
        //  後手（白）の持ち駒ウィンドウ。  //
        wCurIn  =  (this->m_wHands[1]);
        tY  =  HANDS_TOP_MARGIN;
        tX  =  (this->m_xCurCol) * HANDS_PIECE_WIDTH
                +  HANDS_LEFT_MARGIN;
    } else if ( (this->m_yCurRow) == CURSOR_ROW_BLACK_HANDS ) {
        //  先手（黒）の持ち駒ウィンドウ。  //
        wCurIn  =  (this->m_wHands[0]);
        tY  =  HANDS_TOP_MARGIN;
        tX  =  (this->m_xCurCol) * HANDS_PIECE_WIDTH
                +  HANDS_LEFT_MARGIN;
    } else {
        //  盤面を表示しているウィンドウ。  //
        wCurIn  =  (this->m_wBoard);
        tY  =  (this->m_yCurRow - CURSOR_ROW_FIELD_FIRST)
                *  FIELD_PIECE_HEIGHT + FIELD_TOP_MARGIN;
        tX  =  (this->m_xCurCol - CURSOR_COL_FIELD_FIRST)
                *  FIELD_PIECE_WIDTH + FIELD_LEFT_MARGIN;
    }

    getbegyx(wCurIn,  oY,  oX);

    cW  =  wCurIn;
    wY  =  tY;
    wX  =  tX;
    sY  =  tY + oY;
    sX  =  tX + oX;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    内部座標をカーソル座標に変換する。
//

FileCol
TextUserInterface::getCursorColFromInternal(
        const  FileCol  xIntCol)  const
{
    const  GameInterface  & gcGame  =  (this->m_giGameCtrl);
    const  GameInterface::ShowCoordFlags
        flgShow = gcGame.getShowFlag();

    if ( (flgShow == GameInterface::SCF_FLIP_COLUMNS)
            || (flgShow == GameInterface::SCF_ROTATE_BOARD) )
    {
        return ( xIntCol );
    }
    return ( 5 - xIntCol - 1 );
}

//----------------------------------------------------------------
//    内部座標をカーソル座標に変換する。
//

RankRow
TextUserInterface::getCursorRowFromInternal(
        const  RankRow  yIntRow)  const
{
    const  GameInterface  & gcGame  =  (this->m_giGameCtrl);
    const  GameInterface::ShowCoordFlags
        flgShow = gcGame.getShowFlag();

    RankRow     yTmpRow = yIntRow;
    if ( (flgShow) & GameInterface::SCF_ROTATE_BOARD ) {
        yTmpRow = (FIELD_NUM_Y_ROWS - yIntRow - 1);
    }

    return ( yTmpRow + CURSOR_ROW_FIELD_FIRST );
}

//----------------------------------------------------------------
//    移動した先でなれる駒のリストを取得する。
//

ErrCode
TextUserInterface::getPromotionList(
        PromoteList  *  vProms,
        ActionView   *  ptrAct)  const
{
    const  GameInterface  & giCtrl  =  (this->m_giGameCtrl);

    if ( (this->m_ySrcRow) == CURSOR_ROW_WHITE_HANDS ) {
        giCtrl.setupPutActionFromMouse(
                (this->m_xTrgCol),  (this->m_yTrgRow),
                s_tblHandEncWhite[(this->m_xSrcCol)],
                vProms,  ptrAct);
    } else if ( (this->m_ySrcRow) == CURSOR_ROW_BLACK_HANDS ) {
        //  先手（黒）の持ち駒を打つ。  //
        giCtrl.setupPutActionFromMouse(
                (this->m_xTrgCol),  (this->m_yTrgRow),
                s_tblHandEncBlack[(this->m_xSrcCol)],
                vProms,  ptrAct);
    } else {
        //  盤上の駒を移動させる。      //
        giCtrl.setupMoveActionFromMouse(
                (this->m_xSrcCol),  (this->m_ySrcRow),
                (this->m_xTrgCol),  (this->m_yTrgRow),
                vProms,  ptrAct);

    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------

ErrCode
TextUserInterface::playForward(
        const  ActionView  &actView)
{
    GameInterface    &  giCtrl  =  (this->m_giGameCtrl);

    giCtrl.playForward(actView);
    giCtrl.setPlayerToNext();
    giCtrl.setConstraint(Common::DICE_DEFAULT_VALUE);

    this->m_ySrcRow =  -1;
    this->m_xSrcCol =  -1;
    this->m_yTrgRow =  -1;
    this->m_xTrgCol =  -1;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    現在の盤面を表示する。
//

ErrCode
TextUserInterface::showCurrentState()  const
{
    WINDOW  *  const        wBoard  =  (this->m_wBoard);
    const  GameInterface  & gcGame  =  (this->m_giGameCtrl);
    const  GameInterface::ShowCoordFlags
        flgShow = gcGame.getShowFlag();

    Common::ViewBuffer  vb;
    ::memset( &vb, 0, sizeof(vb) );
    gcGame.writeToViewBuffer(vb);

    //  画面をすべて消去する。  //
    wattrset(wBoard,  COLOR_PAIR(1));
    werase  (wBoard);
    wborder (wBoard,  0, 0, 0, 0,  0, 0, 0, 0);
    wbkgd   (wBoard,  COLOR_PAIR(2));

    //  盤面を表示する。    //
    wattrset(wBoard,  COLOR_PAIR(2));
    if ( (flgShow == GameInterface::SCF_FLIP_COLUMNS)
            || (flgShow == GameInterface::SCF_ROTATE_BOARD) )
    {
        wmove   (wBoard,   1,  1);
        waddstr (wBoard,  " |  1 |  2 |  3 |  4 |  5 | ");

        wmove   (wBoard,  18,  1);
        waddstr (wBoard,  " |  1 |  2 |  3 |  4 |  5 | ");
    } else {
        wmove   (wBoard,   1,  1);
        waddstr (wBoard,  " |  5 |  4 |  3 |  2 |  1 | ");

        wmove   (wBoard,  18,  1);
        waddstr (wBoard,  " |  5 |  4 |  3 |  2 |  1 | ");
    }

    //  盤面の罫線を表示する。  //
    for ( int y = 0; y < 6; ++ y ) {
        wmove   (wBoard,  y * 3 + 2,  2);
        whline  (wBoard,  0,  26);
    }

    int     ry  =  0;
    for ( int y = 0; y < 5; ++ y ) {
        std::stringstream   ssLine;

        if ( (flgShow) & GameInterface::SCF_ROTATE_BOARD ) {
            ry  =  (5 - y);
        } else {
            ry  =  (y + 1);
        }


        wattrset(wBoard,  COLOR_PAIR(2));
        wmove   (wBoard,  y * 3 + 3, 1);
        waddstr (wBoard,  " |    |    |    |    |    | ");

        wmove   (wBoard,  y * 3 + 4, 1);
        waddch  (wBoard,  ry + 'a' - 1);
        waddstr (wBoard,  "|    |    |    |    |    |");
        waddch  (wBoard,  ry + '0');

        for ( int x = 0; x < 5; ++ x ) {
            const  PieceIndex   dp  = vb.fpBoard[y][x];
            wattrset(wBoard,  COLOR_PAIR(2));
            wmove   (wBoard,  y * 3 + 3, x * 5 + 3);
            waddstr (wBoard,  "    ");
            wmove   (wBoard,  y * 3 + 4, x * 5 + 3);
            waddstr (wBoard,  "    ");

            if ( dp == 0 ) {
                wattrset(wBoard,  COLOR_PAIR(2));
                continue;
            } else if ( dp <= 14 ) {
                wattrset(wBoard,  COLOR_PAIR(3));
                wmove   (wBoard,  y * 3 + 3, x * 5 + 3);
                waddstr (wBoard,  "  ^ ");
                wmove   (wBoard,  y * 3 + 4, x * 5 + 3);
            } else {
                wattrset(wBoard,  COLOR_PAIR(4));
                wmove   (wBoard,  y * 3 + 4, x * 5 + 3);
                waddstr (wBoard,  "  v ");
                wmove   (wBoard,  y * 3 + 3, x * 5 + 3);
            }

            waddch  (wBoard,  ' ');
            waddstr (wBoard,  s_tblPieceName[dp]);
            waddch  (wBoard,  ' ');
        }

    }

    //  持ち駒を表示する。  //
    for ( PlayerIndex i = 0; i < vb.numPlayers; ++ i ) {
        WINDOW  *   wHands  =  (this->m_wHands[i]);

        wbkgd   (wHands,  COLOR_PAIR(i + 3));
        werase  (wHands);
        wborder (wHands,  0, 0, 0, 0,  0, 0, 0, 0);
        wattrset(wHands,  COLOR_PAIR(i + 3));


        std::stringstream   ssLine;
        ssLine  <<  s_tblPlayerNames[i]  <<  "  HANDS:";
        wmove   (wHands,  1, 1);
        waddstr (wHands,  ssLine.str().c_str());

        ssLine.clear();
        ssLine.str("");
        const  PieceIndex  numHand  =  vb.numHandTypes[i];
        for ( PieceIndex c = 0; c < numHand;  ++ c )
        {
            const  Common::EHandPiece   piHand  =  vb.hpIndex[i][c];
            const  THandCount           hcHand  =  vb.hpCount[i][c];
            if ( hcHand <= 0 ) { continue; }
            ssLine  <<  s_tblHandName[piHand]
                    <<  hcHand
                    <<  ", ";
        }

        wmove   (wHands,  2, 1);
        waddstr (wHands,  ssLine.str().c_str());
    }

    int         cx,  cy,  sx, sy;
    WINDOW  *   wCurIn;
    computeScreenPosition(sy,  sx,  wCurIn,  cy,  cx);

    // attrset(COLOR_PAIR(0));
    // mvprintw(40, 0, "# DEBUG : cy=%d, cx=%d",  cy, cx);

    wmove   (wCurIn,  cy,  cx);
    wattrset(wCurIn,  COLOR_PAIR(5));
    waddch  (wCurIn,  '>');

    for ( PlayerIndex i = 0; i < vb.numPlayers; ++ i ) {
        WINDOW  *   wHands  =  (this->m_wHands[i]);
        touchwin(wHands);
        wrefresh(wHands);
    }

    touchwin(wBoard);
    wrefresh(wBoard);
    wmove   (stdscr,  sy,  sx);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    追加の情報を表示する。
//

ErrCode
TextUserInterface::showInformations()  const
{
    WINDOW  *  const        wInfos  =  (this->m_wInfos);
    const  GameInterface  & gcGame  =  (this->m_giGameCtrl);

    const  PlayerIndex      piTurn  =  gcGame.getCurrentPlayer();

    std::stringstream       ssDice;
    ssDice  <<  gcGame.getConstraint();

    //  画面をすべて消去する。  //
    wattrset(wInfos,  COLOR_PAIR(1));
    werase  (wInfos);
    wborder (wInfos,  0, 0, 0, 0,  0, 0, 0, 0);
    wbkgd   (wInfos,  COLOR_PAIR(1));

    wattrset(wInfos,  COLOR_PAIR(1));
    wmove   (wInfos,  1, 1);
    waddstr (wInfos,  "TURN: ");
    wattrset(wInfos,  COLOR_PAIR(piTurn + 2) | A_BOLD);
    wmove   (wInfos,  2, 2);
    waddstr (wInfos,  s_tblPlayerNames[piTurn]);

    wattrset(wInfos,  COLOR_PAIR(1));
    wmove   (wInfos,  4, 1);
    waddstr (wInfos,  "DICE:");
    wattrset(wInfos,  COLOR_PAIR(piTurn + 2) | A_BOLD);
    wmove   (wInfos,  5, 2);
    waddstr (wInfos,  ssDice.str().c_str());

    wattrset(wInfos,  COLOR_PAIR(1));
    wmove   (wInfos,  7, 1);
    waddstr (wInfos,  "MOVE:");
    wmove   (wInfos,  8, 2);
    wprintw (wInfos,  "%d%d %d%d",
             m_ySrcRow,  m_xSrcCol, m_yTrgRow,  m_xTrgCol);

    touchwin(wInfos);
    wrefresh(wInfos);

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    端末制御ライブラリを終了する。
//

ErrCode
TextUserInterface::cleanupScreen()
{
    if ( this->m_flgInitScr == BOOL_FALSE ) {
        //  初期化されていない状態なので、何もしない。  //
        return ( ERR_FAILURE );
    }

    delwin(this->m_wBoard);
    this->m_wBoard  =  (nullptr);

    endwin();

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    色を準備する。
//

ErrCode
TextUserInterface::setupColors()
{
    init_pair( 1,  COLOR_WHITE,   COLOR_BLUE);      //  画面背景。  //
    init_pair( 2,  COLOR_BLACK,   COLOR_YELLOW);    //  将棋盤。    //
    init_pair( 3,  COLOR_CYAN,    COLOR_BLACK);     //  先手の駒。  //
    init_pair( 4,  COLOR_RED,     COLOR_WHITE);     //  後手の駒。  //
    init_pair( 5,  COLOR_BLACK,   COLOR_RED);       //  カーソル。  //
    bkgd   (COLOR_PAIR(1));
    clear();

    wbkgd     (this->m_wBoard,  COLOR_PAIR(1));
    wborder   (this->m_wBoard,  0, 0, 0, 0,  0, 0, 0, 0);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    端末制御ライブラリを初期化する。
//

ErrCode
TextUserInterface::setupScreen()
{
    if ( (this->m_flgInitScr) != BOOL_FALSE ) {
        //  既に初期化されているので、何もしない。  //
        return ( ERR_SUCCESS );
    }

    initscr();

    if ( has_colors() == FALSE || start_color() == ERR ) {
        return ( ERR_FAILURE );
    }

    //  画面のサイズを取得、検査する。  //
    //  最低でも w48 x h30 以上が必要。  //
    int         sxW,  syH;
    getmaxyx(stdscr,  syH,  sxW);
    if ( (sxW < 48) || (syH < 30) ) {
        return ( ERR_FAILURE );
    }

    //  以下の条件でウィンドウを作成する。  //
    //  ボード表示：w30 x h20               //
    //  持ち駒表示：w30 x h 4               //
    //  その他表示：w16 x h30               //
    //  さらに画面の中央に表示する。        //
    const  int  sxCent  =  (sxW - 48) / 2;
    const  int  syCent  =  (syH - 30) / 2;

    WINDOW  *   wBoard  =  subwin(stdscr,  20,  30,  syCent +  5,  sxCent);
    WINDOW  *   wHandB  =  subwin(stdscr,   4,  30,  syCent + 26,  sxCent);
    WINDOW  *   wHandW  =  subwin(stdscr,   4,  30,  syCent +  0,  sxCent);
    WINDOW  *   wInfos  =  subwin(stdscr,  30,  16,  syCent,  sxCent + 32);
    noecho();
    cbreak();
    keypad(stdscr,  TRUE);

    mousemask(BUTTON1_PRESSED | REPORT_MOUSE_POSITION,  NULL);

    this->m_wScreen     =  stdscr;
    this->m_wBoard      =  wBoard;
    this->m_wHands[0]   =  wHandB;
    this->m_wHands[1]   =  wHandW;
    this->m_wInfos      =  wInfos;
    this->m_flgInitScr  =  BOOL_TRUE;

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    現在のカーソル位置を取得する。
//

ErrCode
TextUserInterface::getCursorPosition(
        RankRow  &  yCurRow,
        FileCol  &  xCurCol)  const
{
    yCurRow = (this->m_yCurRow);
    xCurCol = (this->m_xCurCol);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    カーソル位置を変更する。
//

ErrCode
TextUserInterface::incrementCursorPosition(
        const  RankRow  yIncRow,
        const  FileCol  xIncCol)
{
    const  RankRow  yNewRow = (this->m_yCurRow) + yIncRow;
    const  FileCol  xNewCol = (this->m_xCurCol) + xIncCol;
    return ( setCursorPosition(yNewRow,  xNewCol) );
}

//----------------------------------------------------------------
//    カーソル位置を変更する。
//

ErrCode
TextUserInterface::setCursorPosition(
        const  RankRow  yNewRow,
        const  FileCol  xNewCol)
{
    RankRow     yTmpRow = (yNewRow - CURSOR_ROW_FIELD_FIRST);
    FileCol     xMaxCol = 0;

    if ( yNewRow == CURSOR_ROW_BLACK_HANDS ) {
        //  先手（黒）の持ち駒ウィンドウ。  //
        xMaxCol = HANDS_NUM_PIECE_TYPES;
    } else if ( yNewRow == CURSOR_ROW_WHITE_HANDS ) {
        //  後手（白）の持ち駒ウィンドウ。  //
        xMaxCol = HANDS_NUM_PIECE_TYPES;
    } else if ( (yTmpRow < 0) || (FIELD_NUM_Y_ROWS <= yTmpRow) ) {
        //  範囲外の座標。  //
        return ( ERR_FAILURE );
    } else {
        xMaxCol = FIELD_NUM_X_COLS;
    }

    if ( (xNewCol < 0) || (xMaxCol <= xNewCol) ) {
        //  範囲外の座標。  //
        return ( ERR_FAILURE );
    }

    this->m_yCurRow = yNewRow;
    this->m_xCurCol = xNewCol;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    移動元の座標を設定する。
//

ErrCode
TextUserInterface::setSourcePosition(
        const  RankRow  ySrcRow,
        const  FileCol  xSrcCol)
{
    this->m_ySrcRow = ySrcRow;
    this->m_xSrcCol = xSrcCol;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    移動先の座標を設定する。
//

ErrCode
TextUserInterface::setTargetPosition(
        const  RankRow  yTrgRow,
        const  FileCol  xTrgCol)
{
    this->m_yTrgRow = yTrgRow;
    this->m_xTrgCol = xTrgCol;
    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    端末座標が指定したウィンドウ内にあるか判定する。
//

Boolean
TextUserInterface::checkCoordInWindow(
        WINDOW  *  const    wndTest,
        const  CursorCoord  sY,
        const  CursorCoord  sX,
        CursorCoord      &  wY,
        CursorCoord      &  wX)  const
{
    int     oX,  oY,  oW,  oH;

    getbegyx(wndTest,  oY,  oX);
    getmaxyx(wndTest,  oH,  oW);

    wY  =  sY - oY;
    wX  =  sX - oX;

    if ( (wX < 0) || (oW <= wX) || (wY < 0) || (oH <= wY) ) {
        return ( BOOL_FALSE );
    }
    return ( BOOL_TRUE );
}

}   //  End of namespace  TextUI
FAIRYSHOGI_NAMESPACE_END
