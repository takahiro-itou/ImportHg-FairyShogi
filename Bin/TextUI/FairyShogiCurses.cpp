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

    MEVENT  mEvent;
    int     cx  =  0;
    int     cy  =  0;
    int     key;

    gcTUI.setupColors();

    for (;;) {
        gcTUI.showInformations();
        gcTUI.showCurrentState();
        refresh();

        gcTUI.getCursorPosition(cy,  cx);
        key = getch();

        if ( key == 'q' ) { break; }

        if ( (key == '\n') || (key == KEY_ENTER) || (key == ' ') ) {
            gcTUI.setSourcePosition(cy,  cx);
            continue;
        }

        if ( key == KEY_MOUSE ) {
            if ( getmouse(&mEvent) != OK ) {
                continue;
            }
            WINDOW  *   wndTmp  =  nullptr;
            if ( gcTUI.computeCursorPosition(
                            mEvent.y,  mEvent.x,  wndTmp,  cy,  cx)
                    != ERR_SUCCESS )
            {
                continue;
            }
            gcTUI.setCursorPosition(cy,  cx);
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
        }
        if ( ('a' <= key) && (key <= 'e') ) {
            cy  =  gcTUI.getCursorRowFromInternal(key - 'a');
        }
        if ( ('A' <= key) && (key <= 'E') ) {
            cy  =  gcTUI.getCursorRowFromInternal(key - 'A');
        }
        gcTUI.setCursorPosition(cy,  cx);

    }

    // endwin();

    return ( 0 );
}
