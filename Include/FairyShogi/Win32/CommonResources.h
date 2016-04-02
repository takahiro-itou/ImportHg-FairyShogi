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
**      Common Resource Definitions.
**
**      @file       Win32/CommonResources.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_COMMON_RESOURCES_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_COMMON_RESOURCES_H

#if !defined( IDC_STATIC )
#    define     IDC_STATIC      -1
#endif

//========================================================================
//
//    メニューリソース。
//

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
