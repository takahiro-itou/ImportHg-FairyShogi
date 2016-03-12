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
**      Helper Macros and Functions.
**
**      @file       Common/HelerMacros.h
**/

#if !defined( FAIRYSHOGI_COMMON_INCLUDED_HELPER_MACROS_H )
#    define   FAIRYSHOGI_COMMON_INCLUDED_HELPER_MACROS_H

#if !defined( FAIRYSHOGI_COMMON_INCLUDED_FAIRY_SHOGI_TYPES_H )
#    include    "FairyShogiTypes.h"
#endif

FAIRYSHOGI_NAMESPACE_BEGIN

//----------------------------------------------------------------
/**
**    未使用の引数に対する警告を取り除くためのマクロ。
**/

#if !defined( UTL_HELP_UNUSED_ARGUMENT )
#    define     UTL_HELP_UNUSED_ARGUMENT(var)   (void)(var)
#endif

//========================================================================
//
//    配列およびポインタ関連の関数。
//

//----------------------------------------------------------------
/**   配列の要素数を取得する。
**
**/

template  <typename  T,  size_t  N>
size_t
getArraySize(const  T (&)[N])
{
    return ( N );
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
