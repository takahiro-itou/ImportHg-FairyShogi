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

FAIRYSHOGI_NAMESPACE_END

#endif
