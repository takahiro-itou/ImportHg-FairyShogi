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
**      An Implementation of BitmapResource class.
**
**      @file       Win32/BitmapResource.cpp
**/

#include    "FairyShogi/Win32/BitmapResource.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    BitmapResource  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

BitmapResource::BitmapResource()
    : Super()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BitmapResource::~BitmapResource()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//----------------------------------------------------------------
//    ビットマップリソースを読み込む。
//

ErrCode
BitmapResource::loadBitmapResource(
        const   HINSTANCE   hInst,
        const   HDC         hDC,
        const   LPCTSTR     bmpName)
{
    const  HBITMAP  hBitmap = ::LoadBitmap(hInst,  bmpName);
    if ( hBitmap == NULL ) {
        return ( ERR_FAILURE );
    }

    const  HDC      hMemDC  = ::CreateCompatibleDC(hDC);
    const  HGDIOBJ  hOldBmp = ::SelectObject(hMemDC, hBitmap);

    copyBitmap(hMemDC, 0, 0, getWidth(), getHeight(), 0, 0);

    ::SelectObject(hMemDC, hOldBmp);
    ::DeleteDC(hMemDC);
    ::DeleteObject(hBitmap);

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
