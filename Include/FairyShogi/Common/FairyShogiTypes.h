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
**      Type Definitions.
**
**      @file       Common/FairyShogiTypes.h
**/

#if !defined( FAIRYSHOGI_COMMON_INCLUDED_FAIRY_SHOGI_TYPES_H )
#    define   FAIRYSHOGI_COMMON_INCLUDED_FAIRY_SHOGI_TYPES_H

#include    "FairyShogiSettings.h"

#include    <stddef.h>
#include    <stdint.h>

FAIRYSHOGI_NAMESPACE_BEGIN

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    エラーコード。
**/

enum  ErrCode
{
    /**   正常終了。    **/
    ERR_SUCCESS             = 0,

    /**   異常終了。エラーの理由は不明または報告なし。  **/
    ERR_FAILURE             = 1,

    /**   ファイルオープンエラー。  **/
    ERR_FILE_OPEN_ERROR     = 2,

    /**   合法では無い指し手入力。  **/
    ERR_ILLEGAL_ACTION      = 3
};

//----------------------------------------------------------------
/**
**    横方向の座標を表す型。
**/

typedef     int     PosCol;

//----------------------------------------------------------------
/**
**    縦方向の座標を表す型。
**/

typedef     int     PosRow;

//----------------------------------------------------------------
/**
**    盤面の座標を表す型。
**/

typedef     int     FieldIndex;

//----------------------------------------------------------------
/**
**    プレーヤーの番号を表す型。
**/

typedef     int     PlayerIndex;

//----------------------------------------------------------------
/**
**    駒の種類を表す型。
**/

typedef     int     PieceIndex;

//----------------------------------------------------------------
/**
**    持ち駒の枚数を表す型。
**/

typedef     int     THandCount;

//----------------------------------------------------------------

typedef     const   void  *     LpReadBuf;

typedef     void  *             LpWriteBuf;

typedef     size_t              FileLen;

//----------------------------------------------------------------
/**   ポインタを別の型のポインタに変換する。
**
**  @tparam     T     変換する先の型。ポインタ型に限る。
**  @param [in] ptr   ポインタ
**  @return     指定した型に変換したポインタを返す。
**/

template  <typename  T>
T  pointer_cast(
        void  *  ptr)
{
    return ( static_cast<T>(ptr) );
}

//----------------------------------------------------------------
/**   ポインタを別の型のポインタに変換する。
**
**  @tparam     T     変換する先の型。ポインタ型に限る。
**  @param [in] ptr   ポインタ
**  @return     指定した型に変換したポインタを返す。
**/

template  <typename  T>
T  pointer_cast(
        const  void  *  ptr)
{
    return ( static_cast<T>(ptr) );
}

FAIRYSHOGI_NAMESPACE_END

#endif
