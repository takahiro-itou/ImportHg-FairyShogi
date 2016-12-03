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

CONSTEXPR_VAR   const  char  *
s_tblHandOwnerNames[]   =  {
    "BLACK",
    "WHITE"
};


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
      m_yCurRow(0),
      m_xCurCol(0)
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
//    現在の盤面を表示する。
//

ErrCode
TextUserInterface::showCurrentState()  const
{
    WINDOW  *  const        wBoard  =  (this->m_wBoard);
    const  GameInterface  &objGame  =  (this->m_giGameCtrl);
    const  GameInterface::ShowCoordFlags
        flgShow = objGame.getShowFlag();

    Common::ViewBuffer  vb;
    ::memset( &vb, 0, sizeof(vb) );
    objGame.writeToViewBuffer(vb);

    //  画面をすべて消去する。  //
    wattrset(wBoard,  COLOR_PAIR(1));
    werase  (wBoard);
    wborder (this->m_wBoard,  0, 0, 0, 0,  0, 0, 0, 0);
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

    std::stringstream   ssSqur;
    for ( int y = 0; y < 5; ++ y ) {
        std::stringstream   ssLine;

        if ( (flgShow) & GameInterface::SCF_ROTATE_BOARD ) {
            ssLine  <<  (5-y);
        } else {
            ssLine  <<  (y+1);
        }

        wattrset(wBoard,  COLOR_PAIR(2));
        wmove   (wBoard,  y * 3 + 3, 1);
        waddstr (wBoard,  " |    |    |    |    |    | ");

        wmove   (wBoard,  y * 3 + 4, 1);
        waddstr (wBoard,  ssLine.str().c_str());
        waddstr (wBoard,  "|    |    |    |    |    |");
        waddstr (wBoard,  ssLine.str().c_str());

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
        ssLine  <<  s_tblHandOwnerNames[i]  <<  "  HANDS:";
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

        touchwin(wHands);
        wrefresh(wHands);
    }

    int         cx,  cy,  sx, sy;
    WINDOW  *   wCurIn;
    computeScreenCursorPosition(&cy,  &cx,  &sy,  &sx,  wCurIn);

    wmove   (wCurIn,  cy,  cx);
    wattrset(wCurIn,  COLOR_PAIR(5));
    waddch  (wCurIn,  '>');

    touchwin(wBoard);
    wrefresh(wBoard);
    wmove   (stdscr,  sy,  sx);

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
//    カーソルを表示する座標を計算する。
//

ErrCode
TextUserInterface::computeScreenCursorPosition(
        int  *  const   pWY,
        int  *  const   pWX,
        int  *  const   pSY,
        int  *  const   pSX,
        WINDOW  *    &  pWnd)  const
{
    WINDOW  *   wCurIn  =  nullptr;
    int         wY,  wX;
    int         oY,  oX;

    if ( (this->m_yCurRow) == -1 ) {
        //  後手（白）の持ち駒ウィンドウ。  //
        wCurIn  =  (this->m_wHands[1]);
        wY      =  2;
        wX      =  (this->m_xCurCol) * 2 + 1;
    } else if ( (this->m_yCurRow) == 5 ) {
        //  先手（黒）の持ち駒ウィンドウ。  //
        wCurIn  =  (this->m_wHands[0]);
        wY      =  2;
        wX      =  (this->m_xCurCol) * 2 + 1;
    } else {
        //  盤面を表示しているウィンドウ。  //
        wCurIn  =  (this->m_wBoard);
        wY      =  (this->m_yCurRow) * 3 + 3;
        wX      =  (this->m_xCurCol) * 5 + 4;
    }

    getbegyx(wCurIn,  oY,  oX);

    (*pWY)  =  wY;
    (*pWX)  =  wX;
    (*pSY)  =  wY + oY;
    (*pSX)  =  wX + oX;
    pWnd    =  wCurIn;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    現在のカーソル位置を取得する。
//

ErrCode
TextUserInterface::getCursorPosition(
        int &   yNewRow,
        int &   xNewCol)  const
{
    yNewRow = (this->m_yCurRow);
    xNewCol = (this->m_xCurCol);
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
    RankRow     yTmpRow = yNewRow;
    FileCol     xTmpCol = xNewCol;

    if ( (yTmpRow < -1) || (5 < yTmpRow) ) {
        //  範囲外の座標。  //
        return ( ERR_FAILURE );
    }

    if ( (yTmpRow == -1) || (yTmpRow == 5) ) {
        //  持ち駒ウィンドウ。  //
    }

    if ( (xTmpCol < 0) || (5 <= xTmpCol) ) {
        //  範囲外の座標。  //
        return ( ERR_FAILURE );
    }

    this->m_yCurRow = yNewRow;
    this->m_xCurCol = xNewCol;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    色を準備する。
//

ErrCode
TextUserInterface::setupColors()
{
    init_pair( 1,  COLOR_WHITE,   COLOR_BLUE);
    init_pair( 2,  COLOR_BLACK,   COLOR_YELLOW);
    init_pair( 3,  COLOR_CYAN,    COLOR_BLACK);
    init_pair( 4,  COLOR_RED,     COLOR_WHITE);
    init_pair( 5,  COLOR_BLACK,   COLOR_RED);
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
    //  最低でも w40 x h30 以上が必要。  //
    int         sxW,  syH;
    getmaxyx(stdscr,  syH,  sxW);
    if ( (sxW < 40) || (syH < 30) ) {
        return ( ERR_FAILURE );
    }

    //  以下の条件でウィンドウを作成する。  //
    //  ボード表示：w30 x h20               //
    //  持ち駒表示：w30 x h 4               //
    //  さらに画面の中央に表示する。        //
    const  int  sxCent  =  (sxW - 30) / 2;
    const  int  syCent  =  (syH - 30) / 2;

    WINDOW  *   wBoard  =  subwin(stdscr,  20,  30,  syCent +  5,  sxCent);
    WINDOW  *   wHandB  =  subwin(stdscr,   4,  30,  syCent + 26,  sxCent);
    WINDOW  *   wHandW  =  subwin(stdscr,   4,  30,  syCent +  0,  sxCent);
    noecho();
    cbreak();
    keypad(stdscr,  TRUE);

    mousemask(BUTTON1_PRESSED | REPORT_MOUSE_POSITION,  NULL);

    this->m_wScreen     =  stdscr;
    this->m_wBoard      =  wBoard;
    this->m_wHands[0]   =  wHandB;
    this->m_wHands[1]   =  wHandW;
    this->m_flgInitScr  =  BOOL_TRUE;

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

}   //  End of namespace  TextUI
FAIRYSHOGI_NAMESPACE_END
