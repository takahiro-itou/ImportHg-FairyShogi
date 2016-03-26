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

#define     IDM_FILE                10000
#define     IDM_FILE_EXIT           10001

#define     IDM_MATCH               10100
#define     IDM_MATCH_START         10101

#define     IDM_ID_OPTION           10200

#define     IDM_DICE                10300
#define     IDM_DICE_MANUAL         10301
#define     IDM_DICE_AUTO           10302

#define     IDM_BLACK               10400
#define     IDM_BLACK_MAN           10401
#define     IDM_BLACK_FIRST         10402
#define     IDM_BLACK_LAST          MENU_ID_BLACK_FIRST + 4,

#define     IDM_WHITE               10500
#define     IDM_WHITE_MAN           10501
#define     IDM_WHITE_FIRST         10502
#define     IDM_WHITE_LAST          MENU_ID_WHITE_FIRST + 4

#define     IDM_TURN                10600
#define     IDM_TURN_BLACK          10601
#define     IDM_TURN_WHITE          10602

#endif
