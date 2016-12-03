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

    int     x = 0, y = 0;
    int     key;

    gcTUI.setupColors();

    for (;;) {
        gcTUI.setCursorPosition(y, x);
        gcTUI.showInformations();
        gcTUI.showCurrentState();
        refresh();

        gcTUI.getCursorPosition(y,  x);
        key = getch();
        if ( key == 'q' ) { break; }
        if ( key == ' ' ) { break; }

        switch ( key ) {
        case  KEY_LEFT:   case  'h':    -- x;   break;
        case  KEY_DOWN:   case  'j':    ++ y;   break;
        case  KEY_UP:     case  'k':    -- y;   break;
        case  KEY_RIGHT:  case  'l':    ++ x;   break;
        case  '1':
        case  '2':
        case  '3':
        case  '4':
        case  '5':
            x   =  key - '1';
            break;
        case  'a':
        case  'b':
        case  'c':
        case  'd':
        case  'e':
            y   =  key - 'a';
            break;
        }
    }

    // endwin();

    return ( 0 );
}
