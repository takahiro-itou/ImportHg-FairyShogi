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
**      プロジェクトの設定。
**
**      @file       Common/FairyShogiSettings.h
**/

#if !defined( FAIRYSHOGI_COMMON_INCLUDED_FAIRY_SHOGI_SETTINGS_H )
#    define   FAIRYSHOGI_COMMON_INCLUDED_FAIRY_SHOGI_SETTINGS_H

//  スクリプトによる設定値が書き込まれたヘッダを読み込む。  //
#include    "FairyShogi/.Config/ConfiguredFairyShogi.h"

FAIRYSHOGI_NAMESPACE_BEGIN

//========================================================================
//
//    FSSYSLIMIT  enum.
//
/**
**    ゲームシステムの制限事項をまとめた定数用列挙型。
**/

enum  FSSYSLIMIT
{
    /**
    **    プログラムが扱える最大の盤面サイズ（横方向）。
    **/
    MAX_FIELD_COLS  = 16,

    /**
    **    プログラムが扱える最大の盤面サイズ（縦方向）。
    **/
    MAX_FIELD_ROWS  = 16,

    /**
    **    プログラムが扱える最大の盤面サイズ。
    **/
    MAX_FIELD_SIZE  = MAX_FIELD_COLS * MAX_FIELD_ROWS,

    /**
    **    プログラムが扱える最大のプレーヤー数。
    **/
    MAX_NUM_PLAYERS = 16,

    /**
    **    定義可能な盤上駒の種類の最大値。
    **/
    MAX_PIECE_TYPES = 256,

    /**
    **    定義可能な持ち駒の種類の最大値。
    **/
    MAX_HAND_TYPES  = 256
};

FAIRYSHOGI_NAMESPACE_END

#endif
