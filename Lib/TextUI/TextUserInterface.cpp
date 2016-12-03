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
#include    <ncurses.h>
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
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr,  TRUE);

    mousemask(BUTTON1_PRESSED | REPORT_MOUSE_POSITION,  NULL);

    this->m_giGameCtrl.resetGame();
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

TextUserInterface::~TextUserInterface()
{
    endwin();
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
    CONSTEXPR_VAR   const  char  *  s_tblHandOwnerNames[2]  =  {
        "BLACK:",
        "WHITE:"
    };

    const   GameInterface  &objGame =  (this->m_giGameCtrl);
    const   GameInterface::ShowCoordFlags
        flgShow = objGame.getShowFlag();

    Common::ViewBuffer  vb;
    ::memset( &vb, 0, sizeof(vb) );
    objGame.writeToViewBuffer(vb);

    //  盤面を表示する。    //
    ::move(0, 0);
    if ( (flgShow == GameInterface::SCF_FLIP_COLUMNS)
            || (flgShow == GameInterface::SCF_ROTATE_BOARD) )
    {
        ::addstr("| 1| 2| 3| 4| 5|");
    } else {
        ::addstr("| 5| 4| 3| 2| 1|");
    }

    ::move(1, 0);
    ::addstr("----------------");
    for ( int y = 0; y < 5; ++ y ) {
        std::stringstream   ssLine;
        for ( int x = 0; x < 5; ++ x ) {
            const  PieceIndex   dp  = vb.fpBoard[y][x];
            ssLine  <<  "|"  <<  s_tblPieceName[dp];
        }
        if ( (flgShow) & GameInterface::SCF_ROTATE_BOARD ) {
            ssLine  <<  "|"  <<  (5-y);
        } else {
            ssLine  <<  "|"  <<  (y+1);
        }
        ::move(y * 2 + 2, 0);
        ::addstr(ssLine.str().c_str());
        ::move(y * 2 + 3, 0);
        ::addstr("----------------");
    }

    //  持ち駒を表示する。  //
    for ( PlayerIndex i = 0; i < vb.numPlayers; ++ i ) {
        std::stringstream   ssLine;
        ssLine  <<  s_tblHandOwnerNames[i];
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
        ::move(i + 14, 0);
        ::addstr(ssLine.str().c_str());
    }
    ::refresh();

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

}   //  End of namespace  TextUI
FAIRYSHOGI_NAMESPACE_END
