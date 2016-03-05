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
**      Type and Const Definitions.
**
**      @file       Common/DefaultShogiPieces.h
**/

#if !defined( FAIRYSHOGI_COMMON_INCLUDED_DEFAULT_SHOGI_PIECES_H )
#    define   FAIRYSHOGI_COMMON_INCLUDED_DEFAULT_SHOGI_PIECES_H

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Common  {


//----------------------------------------------------------------
/**
**    標準的な（盤上の）駒番号。
**
**    ただし、この値は表示用なので、
**  内部処理でどのような値を用いてもよい。
**  最終的に、表示用構造体に詰め直す時に、
**  適当な変換を実行すれば十分である。
**/

enum  EFieldPiece
{
    /**   空白のマス。  **/
    FIELD_EMPTY_SQUARE,

    //----------------------------------------
    //
    //    先手の駒。
    //

    /**   先手の歩兵。  **/
    FIELD_BLACK_PAWN,

    /**   先手の香車。  **/
    FIELD_BLACK_LANCE,

    /**   先手の桂馬。  **/
    FIELD_BLACK_KNIGHT,

    /**   先手の銀将。  **/
    FIELD_BLACK_SILVER,

    /**   先手の金将。  **/
    FIELD_BLACK_GOLD,

    /**   先手の角行。  **/
    FIELD_BLACK_BISHOP,

    /**   先手の飛車。  **/
    FIELD_BLACK_ROOK,

    /**   先手の玉将。  **/
    FIELD_BLACK_KING,

    /**   先手のと金。  **/
    FIELD_BLACK_PR_PAWN,

    /**   先手の成香。  **/
    FIELD_BLACK_PR_LANCE,

    /**   先手の成桂。  **/
    FIELD_BLACK_PR_KNIGHT,

    /**   先手の成銀。  **/
    FIELD_BLACK_PR_SILVER,

    /**   先手の龍馬。  **/
    FIELD_BLACK_PR_BISHOP,

    /**   先手の龍王。  **/
    FIELD_BLACK_PR_ROOK,

    //----------------------------------------
    //
    //    後手の駒。
    //

    /**   後手の歩兵。  **/
    FIELD_WHITE_PAWN,

    /**   後手の香車。  **/
    FIELD_WHITE_LANCE,

    /**   後手の桂馬。  **/
    FIELD_WHITE_KNIGHT,

    /**   後手の銀将。  **/
    FIELD_WHITE_SILVER,

    /**   後手の金将。  **/
    FIELD_WHITE_GOLD,

    /**   後手の角行。  **/
    FIELD_WHITE_BISHOP,

    /**   後手の飛車。  **/
    FIELD_WHITE_ROOK,

    /**   後手の玉将。  **/
    FIELD_WHITE_KING,

    /**   後手のと金。  **/
    FIELD_WHITE_PR_PAWN,

    /**   後手の成香。  **/
    FIELD_WHITE_PR_LANCE,

    /**   後手の成桂。  **/
    FIELD_WHITE_PR_KNIGHT,

    /**   後手の成銀。  **/
    FIELD_WHITE_PR_SILVER,

    /**   後手の龍馬。  **/
    FIELD_WHITE_PR_BISHOP,

    /**   後手の龍王。  **/
    FIELD_WHITE_PR_ROOK,

    //----------------------------------------
    //
    //    その他の定数。
    //

    /**   駒の種類の総数。  **/
    NUM_FIELD_PIECE_TYPES
};

//----------------------------------------------------------------
/**
**    標準的な（持ち駒の）駒番号。
**
**    ただし、この値は表示用なので、
**  内部処理でどのような値を用いてもよい。
**  最終的に、表示用構造体に詰め直す時に、
**  適当な変換を実行すれば十分である。
**/

enum  EHandPiece
{
    HAND_EMPTY_PIECE,

    /**   先手の歩兵。  **/
    HAND_BLACK_PAWN,

    /**   先手の香車。  **/
    HAND_BLACK_LANCE,

    /**   先手の桂馬。  **/
    HAND_BLACK_KNIGHT,

    /**   先手の銀将。  **/
    HAND_BLACK_SILVER,

    /**   先手の金将。  **/
    HAND_BLACK_GOLD,

    /**   先手の角行。  **/
    HAND_BLACK_BISHOP,

    /**   先手の飛車。  **/
    HAND_BLACK_ROOK,

    /**   先手の玉将。  **/
    HAND_BLACK_KING,

    /**   後手の歩兵。  **/
    HAND_WHITE_PAWN,

    /**   後手の香車。  **/
    HAND_WHITE_LANCE,

    /**   後手の桂馬。  **/
    HAND_WHITE_KNIGHT,

    /**   後手の銀将。  **/
    HAND_WHITE_SILVER,

    /**   後手の金将。  **/
    HAND_WHITE_GOLD,

    /**   後手の角行。  **/
    HAND_WHITE_BISHOP,

    /**   後手の飛車。  **/
    HAND_WHITE_ROOK,

    /**   後手の玉将。  **/
    HAND_WHITE_KING,

    //----------------------------------------
    //
    //    その他の定数。
    //

    /**   駒の種類の総数。  **/
    NUM_HAND_TYPES
};

}   //  End of namespace  Common
FAIRYSHOGI_NAMESPACE_END

#endif
