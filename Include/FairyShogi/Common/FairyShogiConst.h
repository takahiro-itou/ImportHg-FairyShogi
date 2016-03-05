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
**      Const Definitions.
**
**      @file       Common/FairyShogiConst.h
**/

#if !defined( FAIRYSHOGI_COMMON_INCLUDED_FAIRY_SHOGI_CONST_H )
#    define   FAIRYSHOGI_COMMON_INCLUDED_FAIRY_SHOGI_CONST_H

#include    "FairyShogiSettings.h"

FAIRYSHOGI_NAMESPACE_BEGIN

//----------------------------------------------------------------
/**
**    ゲームの状態を管理する列挙型。
**/

enum  GameStateFlags
{
    /**   ゲーム終了。  **/
    GAME_IS_OVER        =  0,

    /**   対局実行中。  **/
    GAME_IS_RUNNING     =  1
};

//----------------------------------------------------------------
/**
**    ゲームの勝敗を管理する列挙型。
**/

enum  GameResultVals
{
    /**
    **    引き分け。ゲームが終了していない場合も含む。
    **/
    GAME_RESULT_DRAW            =  0x00,

    /**   先手の勝ち。  **/
    GAME_BLACK_WON              =  0x02,

    /**   後手の勝ち。  **/
    GAME_WHITE_WON              =  0x04,

    /**   通常のチェックメイトによる勝利。  **/
    GAME_ENDED_CHECKMATE        =  0x10,

    /**   ステイルメイトによる逆転勝利。    **/
    GAME_ENDED_STALEMATE        =  0x20,

    /**   相手の投了による勝利。            **/
    GAME_ENDED_RESIGN           =  0x40,

    /**   相手の反則による勝利。            **/
    GAME_ENDED_VIOLATE          =  0x80,

    /**
    **    チェックメイトにより先手の勝利。
    **/
    GAME_BLACK_WON_CHECKMATE    =  GAME_BLACK_WON | GAME_ENDED_CHECKMATE,

    /**
    **    ステイルメイトにより先手の勝利。
    **/
    GAME_BLACK_WON_STALEMATE    =  GAME_BLACK_WON | GAME_ENDED_STALEMATE,

    /**
    **    後手の投了により先手の勝利。
    **/
    GAME_BLACK_WON_W_RESIGN     =  GAME_BLACK_WON | GAME_ENDED_RESIGN,

    /**
    **    後手の反則により先手の勝利。
    **/
    GAME_BLACK_WON_W_VIOLATE    =   GAME_BLACK_WON | GAME_ENDED_VIOLATE,

    /**
    **    チェックメイトにより後手の勝利。
    **/
    GAME_WHITE_WON_CHECKMATE    =  GAME_WHITE_WON | GAME_ENDED_CHECKMATE,

    /**
    **    ステイルメイトにより後手の勝利。
    **/
    GAME_WHITE_WON_STALEMATE    =  GAME_WHITE_WON | GAME_ENDED_STALEMATE,

    /**
    **    先手の投了により後手の勝利。
    **/
    GAME_WHITE_WON_B_RESIGN     =  GAME_WHITE_WON | GAME_ENDED_RESIGN,

    /**
    **    先手の反則により後手の勝利。
    **/
    GAME_WHITE_WON_B_VIOLATE    =  GAME_WHITE_WON | GAME_ENDED_VIOLATE
};

namespace  Common  {

//----------------------------------------------------------------
/**
**    手番を管理すする列挙型。
**/

enum
{
    PLAYER_BLACK        =  0,       /**<  先手番。  */
    PLAYER_WHITE        =  1,       /**<  後手番。  **/

    /**
    **    手番を交代するための定数。
    **
    **    手番を管理している値に、この定数の排他的論理輪を取る。
    **/
    PLAYER_OPPOSITE     =  1
};

}   //  End of namespace  Common
FAIRYSHOGI_NAMESPACE_END

#endif
