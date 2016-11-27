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
**      アプリケーション本体。
**
**      @file       Bin/FairyShogi.cpp
**/

#include    "FairyShogi/Helper/TerminalScreen.h"
#include    "FairyShogi/TextUI/TextUserInterface.h"

#include    <ncurses.h>

using   namespace   FAIRYSHOGI_NAMESPACE;

int  main(int argc, char * argv[])
{
    TextUI::TextUserInterface   gcTUI;

    int     x = 0, y = 0;
    int     key;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr,  TRUE);

    mousemask(BUTTON1_PRESSED | REPORT_MOUSE_POSITION,  NULL);

    for (;;) {
        move(y, x);
        refresh();

        key = getch();
        if ( key == 'q' ) { break; }
        switch ( key ) {
        case  KEY_LEFT:   case  'h':    -- x;   break;
        case  KEY_DOWN:   case  'j':    ++ y;   break;
        case  KEY_UP:     case  'k':    -- y;   break;
        case  KEY_RIGHT:  case  'l':    ++ x;   break;
        }
    }

    endwin();

    return ( 0 );
}
