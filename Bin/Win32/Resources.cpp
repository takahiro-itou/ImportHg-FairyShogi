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

    return ( hMenu );
}
