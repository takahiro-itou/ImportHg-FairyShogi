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
**      リソース定義。
**
**      @file       Bin/Win32/Resources.cpp
**/

#include    "Resources.h"

HMENU
insertMenuItem(
        const  char  *  szTitle,
        const  UINT     wID,
        const  HMENU    hSub,
        const  UINT     uPos,
        const  BOOL     fByPos,
        HMENU           hMenu)
{
    MENUITEMINFO    mii;

    mii.cbSize      =  sizeof(MENUITEMINFO);
    mii.fMask       =  MIIM_FTYPE | MIIM_ID | MIIM_SUBMENU | MIIM_STRING;
    mii.fType       =  MFT_STRING;
    mii.fState      =  MFS_ENABLED;
    mii.wID         =  wID;
    mii.hSubMenu    =  hSub;
    mii.dwTypeData  =  const_cast<LPTSTR>(szTitle);

    ::InsertMenuItem(hMenu, uPos, fByPos, &mii);

    return ( hMenu );
}

//----------------------------------------------------------------
//    メインウィンドウのメニューを作成する。
//

HMENU
createMainMenu()
{
    HMENU   hMenuFile   =  ::CreatePopupMenu();
    HMENU   hMenuOpts   =  ::CreatePopupMenu();
    HMENU   hMenuDice   =  ::CreatePopupMenu();
    HMENU   hMenuBlack  =  ::CreatePopupMenu();
    HMENU   hMenuWhite  =  ::CreatePopupMenu();
    HMENU   hMenuTurn   =  ::CreatePopupMenu();

    HMENU   hMenu       =  ::CreateMenu();

    insertMenuItem(
            "&File",    MENU_ID_FILE,   hMenuFile,  0, FALSE, hMenu);
    insertMenuItem(
            "&Option",  MENU_ID_OPTION, hMenuOpts,  0, FALSE, hMenu);
    insertMenuItem(
            "&Dice",    MENU_ID_DICE,   hMenuDice,  0, FALSE, hMenu);
    insertMenuItem(
            "&Black",   MENU_ID_BLACK,  hMenuBlack, 0, FALSE, hMenu);
    insertMenuItem(
            "&White",   MENU_ID_WHITE,  hMenuWhite, 0, FALSE, hMenu);
    insertMenuItem(
            "&Turn",    MENU_ID_TURN,   hMenuTurn,  0, FALSE, hMenu);

    insertMenuItem(
            "E&xit",    MENU_ID_FILE_EXIT,
            NULL,  0,   FALSE,  hMenuFile);

    insertMenuItem(
            "&Manual",  MENU_ID_DICE_MANUAL,
            NULL,  0,   FALSE,  hMenuDice);
    insertMenuItem(
            "&Auto",    MENU_ID_DICE_AUTO,
            NULL,  0,   FALSE,  hMenuDice);

    insertMenuItem(
            "&Man",     MENU_ID_BLACK_MAN,
            NULL,  0,   FALSE,  hMenuBlack);
    insertMenuItem(
            "Level &0", MENU_ID_BLACK_FIRST + 0,
            NULL,  0,   FALSE,  hMenuBlack);
    insertMenuItem(
            "Level &1", MENU_ID_BLACK_FIRST + 1,
            NULL,  0,   FALSE,  hMenuBlack);
    insertMenuItem(
            "Level &2", MENU_ID_BLACK_FIRST + 2,
            NULL,  0,   FALSE,  hMenuBlack);
    insertMenuItem(
            "Level &3", MENU_ID_BLACK_FIRST + 3,
            NULL,  0,   FALSE,  hMenuBlack);

    insertMenuItem(
            "&Man",     MENU_ID_WHITE_MAN,
            NULL,  0,   FALSE,  hMenuWhite);
    insertMenuItem(
            "Level &0", MENU_ID_WHITE_FIRST + 0,
            NULL,  0,   FALSE,  hMenuWhite);
    insertMenuItem(
            "Level &1", MENU_ID_WHITE_FIRST + 1,
            NULL,  0,   FALSE,  hMenuWhite);
    insertMenuItem(
            "Level &2", MENU_ID_WHITE_FIRST + 2,
            NULL,  0,   FALSE,  hMenuWhite);
    insertMenuItem(
            "Level &3", MENU_ID_WHITE_FIRST + 3,
            NULL,  0,   FALSE,  hMenuWhite);

    insertMenuItem(
            "&Black",   MENU_ID_TURN_BLACK,
            NULL,  0,   FALSE,  hMenuTurn);
    insertMenuItem(
            "&White",   MENU_ID_TURN_WHITE,
            NULL,  0,   FALSE,  hMenuTurn);

    return ( hMenu );
}
