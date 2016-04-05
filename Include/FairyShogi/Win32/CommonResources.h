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

#define     IDD_GROUP_BLACK_PLAYER            101
#define     IDD_RADIO_BLACK_MAN               102
#define     IDD_RADIO_BLACK_COM               103
#define     IDD_COMBO_BLACK_MAN               104
#define     IDD_COMBO_BLACK_COM               105
#define     IDD_RADIO_BLACK_DICE_AUTO         106
#define     IDD_RADIO_BLACK_DICE_MANUAL       107
#define     IDD_COMBO_BLACK_DICE_CTRL         108
#define     IDD_RADIO_BLACK_THINK_AUTO        109
#define     IDD_RADIO_BLACK_THINK_MANUAL      110

#define     IDD_GROUP_WHITE_PLAYER            111
#define     IDD_RADIO_WHITE_MAN               112
#define     IDD_RADIO_WHITE_COM               113
#define     IDD_COMBO_WHITE_MAN               114
#define     IDD_COMBO_WHITE_COM               115
#define     IDD_RADIO_WHITE_DICE_AUTO         116
#define     IDD_RADIO_WHITE_DICE_MANUAL       117
#define     IDD_COMBO_WHITE_DICE_CTRL         118
#define     IDD_RADIO_WHITE_THINK_AUTO        119
#define     IDD_RADIO_WHITE_THINK_MANUAL      120

#define     IDD_RADIO_START_INITIAL           121
#define     IDD_RADIO_START_CURRENT           122
#define     IDD_RADIO_START_TEXTSFEN          123
#define     IDD_RADIO_START_TEXTCSA           124
#define     IDD_EDIT_START_TEXT               125
#define     IDD_RADIO_SEED_TIME               126
#define     IDD_RADIO_SEED_MANUAL             127
#define     IDD_EDIT_RANDOM_SEED              128
#define     IDD_CHECK_AUTO_SAVE               129
#define     IDD_EDIT_FILE_NAME                130
#define     IDD_BUTTON_REF_FILE               131

#endif
