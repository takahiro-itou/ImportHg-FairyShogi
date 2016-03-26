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
**      @file       Bin/Win32/Resources.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_RESOURCES_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_RESOURCES_H

//========================================================================
//
//    メニューリソース。
//

//----------------------------------------------------------------
/**
**    リソース ID の定義。
**/

enum  MainMenuResource
{
    MENU_ID_FILE            =  10000,
    MENU_ID_FILE_EXIT       =  10001,

    MENU_ID_OPTION          =  10100,

    MENU_ID_DICE            =  10200,
    MENU_ID_DICE_MANUAL     =  10201,
    MENU_ID_DICE_AUTO       =  10202,

    MENU_ID_BLACK           =  10300,
    MENU_ID_BLACK_MAN       =  10301,
    MENU_ID_BLACK_FIRST     =  10302,
    MENU_ID_BLACK_LAST      =  MENU_ID_BLACK_FIRST + 4,

    MENU_ID_WHITE           =  10400,
    MENU_ID_WHITE_MAN       =  10401,
    MENU_ID_WHITE_FIRST     =  10402,
    MENU_ID_WHITE_LAST      =  MENU_ID_WHITE_FIRST + 4,

    MENU_ID_TURN            =  10500,
    MENU_ID_TURN_BLACK      =  10501,
    MENU_ID_TURN_WHITE      =  10502,
};

#endif
