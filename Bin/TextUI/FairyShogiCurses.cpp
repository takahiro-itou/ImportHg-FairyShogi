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

#include    <iostream>
#include    <ncurses.h>

using   namespace   FAIRYSHOGI_NAMESPACE;

int  main(int argc, char * argv[])
{
    TextUI::TextUserInterface   gcTUI;

    if ( gcTUI.setupScreen() != ERR_SUCCESS )
    {
        gcTUI.cleanupScreen();
        std::cerr   <<  "FATAL ERROR : Screen Initialize Failure."
                    <<  std::endl;
        return ( 1 );
    }

    int     cx  =  0;
    int     cy  = 0;
    int     key;

    gcTUI.setupColors();

    for (;;) {
        gcTUI.setCursorPosition(cy,  cx);
        gcTUI.showInformations();
        gcTUI.showCurrentState();
        refresh();

        gcTUI.getCursorPosition(cy,  cx);
        key = getch();

        attrset(COLOR_PAIR(0));
        mvprintw(40, 0, "# DEBUG : KEY = %x",  key);

        if ( key == 'q' ) { break; }

        if ( (key == '\n') || (key == KEY_ENTER) ) {
            continue;
        }

        switch ( key ) {
        case  KEY_LEFT:   case  'h':    -- cx;  break;
        case  KEY_DOWN:   case  'j':    ++ cy;  break;
        case  KEY_UP:     case  'k':    -- cy;  break;
        case  KEY_RIGHT:  case  'l':    ++ cx;  break;
        }

        if ( ('1' <= key) && (key <= '5') ) {
            cx  =  gcTUI.getCursorColFromInternal(key - '1');
            continue;
        }
        if ( ('a' <= key) && (key <= 'e') ) {
            cy  =  gcTUI.getCursorRowFromInternal(key - 'a');
            continue;
        }
        if ( ('A' <= key) && (key <= 'E') ) {
            cy  =  gcTUI.getCursorRowFromInternal(key - 'A');
            continue;
        }
    }

    // endwin();

    return ( 0 );
}
