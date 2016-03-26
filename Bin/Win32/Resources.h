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

#if !defined( IDC_STATIC )
#    define     IDC_STATIC      -1
#endif

//========================================================================
//
//    メニューリソース。
//

//----------------------------------------------------------------
//
//    メインメニュー。
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

//========================================================================
//
//    ダイアログリソース。
//

//----------------------------------------------------------------
//
//    対局ダイアログ。
//

#define     IDD_MATCH_DIALOG                20000

#define     IDD_GROUP_BLACK_PLAYER          20001
#define     IDD_STATIC_BLACK_PLAYER         20002
#define     IDD_COMBO_BLACK_PLAYER          20003
#define     IDD_STATIC_BLACK_DICE           20004
#define     IDD_RADIO_BLACK_DICE_AUTO       20005
#define     IDD_RADIO_BLACK_DICE_MANUAL     20006
#define     IDD_STATIC_BLACK_THINK          20007
#define     IDD_RADIO_BLACK_THINK_AUTO      20008
#define     IDD_RADIO_BLACK_THINK_MANUAL    20009

#define     IDD_GROUP_WHITE_PLAYER          20010
#define     IDD_STATIC_WHITE_PLAYER         20011
#define     IDD_COMBO_WHITE_PLAYER          20012
#define     IDD_STATIC_WHITE_DICE           20013
#define     IDD_RADIO_WHITE_DICE_AUTO       20014
#define     IDD_RADIO_WHITE_DICE_MANUAL     20015
#define     IDD_STATIC_WHITE_THINK          20016
#define     IDD_RADIO_WHITE_THINK_AUTO      20017
#define     IDD_RADIO_WHITE_THINK_MANUAL    20018

#endif
