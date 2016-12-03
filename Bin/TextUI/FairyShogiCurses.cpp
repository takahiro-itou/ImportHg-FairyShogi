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
        if ( key == 'q' ) { break; }
        if ( key == ' ' ) { break; }

        switch ( key ) {
        case  KEY_LEFT:   case  'h':    -- cx;  break;
        case  KEY_DOWN:   case  'j':    ++ cy;  break;
        case  KEY_UP:     case  'k':    -- cy;  break;
        case  KEY_RIGHT:  case  'l':    ++ cx;  break;
        case  '1':
        case  '2':
        case  '3':
        case  '4':
        case  '5':
            cx  =  gcTUI.getCursorColFromInternal(key - '1');
            break;
        case  'a':
        case  'b':
        case  'c':
        case  'd':
        case  'e':
            cy  =  gcTUI.getCursorRowFromInternal(key - 'a');
            break;
        }
    }

    // endwin();

    return ( 0 );
}
