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
**      An Implementation of PixelMatrix class.
**
**      @file       Interface/PixelMatrix.cpp
**/

#include    "FairyShogi/Interface/PixelMatrix.h"

#include    "FairyShogi/Common/HelperMacros.h"

#include    <algorithm>
#include    <memory.h>
#include    <stdio.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    PixelMatrix  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

PixelMatrix::PixelMatrix()
    : m_xWidth (0),
      m_yHeight(0),
      m_nDepth (0),
      m_ptrBuf (nullptr),
      m_ptrBits(nullptr),
      m_nPixelBytes(0),
      m_nLineBytes (0)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

PixelMatrix::~PixelMatrix()
{
    destroyPixelMatrix();
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
//    ビットマップイメージを生成する。
//

ErrCode
PixelMatrix::createPixelMatrix(
        const  BitmapCoord  cxWidth,
        const  BitmapCoord  cyHeight,
        const  BitmapDepth  bDepth)
{
    destroyPixelMatrix();
    setupParameters(cxWidth, cyHeight, bDepth);

    LpBuffer        ptrBuf  = allocateBuffer(BOOL_TRUE,  0);
    PmPixelArray    ptrBits = (ptrBuf);

    this->m_ptrBuf  = (ptrBuf);
    this->m_ptrBits = (ptrBits);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ビットマップイメージを生成する。
//

ErrCode
PixelMatrix::createPixelMatrix(
        const  BitmapCoord  cxWidth,
        const  BitmapCoord  cyHeight,
        const  BitmapDepth  bDepth,
        PmPixelArray        ptrBits)
{
    destroyPixelMatrix();
    setupParameters(cxWidth, cyHeight, bDepth);

    this->m_ptrBuf  = (nullptr);
    this->m_ptrBits = (ptrBits);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    ビットマップイメージを破棄する。
//

ErrCode
PixelMatrix::destroyPixelMatrix()
{
    this->m_ptrBits = (nullptr);

    delete  []  (this->m_ptrBuf);
    this->m_ptrBuf  = (nullptr);

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    別のビットマップの矩形をコピーする。
//

ErrCode
PixelMatrix::copyRectangle(
        const  BitmapCoord  dx,
        const  BitmapCoord  dy,
        const  BitmapCoord  dw,
        const  BitmapCoord  dh,
        const  PixelMatrix  &bmpSrc,
        const  BitmapCoord  sx,
        const  BitmapCoord  sy)
{
    for ( BitmapCoord y = 0; y < dh; ++ y ) {
        PcPixelArray    ptrSrc  = bmpSrc.getPixels(sx, sy + y);
        PmPixelArray    ptrDst  = this->getPixels(dx, dy + y);
        for ( BitmapCoord x = 0; x < dw; ++ x ) {
            *(ptrDst++) = *(ptrSrc++);      //  B
            *(ptrDst++) = *(ptrSrc++);      //  G
            *(ptrDst++) = *(ptrSrc++);      //  R
        }
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    別のビットマップの矩形をコピーする。
//

ErrCode
PixelMatrix::copyRectangleWithTransparentColor(
        const  BitmapCoord  dx,
        const  BitmapCoord  dy,
        const  BitmapCoord  dw,
        const  BitmapCoord  dh,
        const  PixelMatrix  &bmpSrc,
        const  BitmapCoord  sx,
        const  BitmapCoord  sy,
        const  PixelValue   trColR,
        const  PixelValue   trColG,
        const  PixelValue   trColB)
{
    for ( BitmapCoord y = 0; y < dh; ++ y ) {
        PcPixelArray    ptrSrc  = bmpSrc.getPixels(sx, sy + y);
        PmPixelArray    ptrDst  = this->getPixels(dx, dy + y);
        for ( BitmapCoord x = 0; x < dw; ++ x ) {
            const  PixelValue  pvB  = *(ptrSrc++);
            const  PixelValue  pvG  = *(ptrSrc++);
            const  PixelValue  pvR  = *(ptrSrc++);

            if ( (pvR == trColR) && (pvG == trColG) && (pvB == trColB) ) {
                ptrDst  += 3;
                continue;
            }

            *(ptrDst++) = pvB;
            *(ptrDst++) = pvG;
            *(ptrDst++) = pvR;
        }
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    矩形を描画する。
//

ErrCode
PixelMatrix::drawRectangle(
        const  BitmapCoord  dx,
        const  BitmapCoord  dy,
        const  BitmapCoord  dw,
        const  BitmapCoord  dh,
        const  PixelValue   colR,
        const  PixelValue   colG,
        const  PixelValue   colB)
{
    const  BitmapCoord  dx2 = std::min((this->m_xWidth),  dx + dw);
    const  BitmapCoord  dy2 = std::min((this->m_yHeight), dy + dh);

    for ( BitmapCoord y = dy; y < dy2; ++ y ) {
        PmPixelArray    ptrDst  = this->getPixels(dx, y);
        for ( BitmapCoord x = dx; x < dx2; ++ x ) {
            *(ptrDst++) = colB;
            *(ptrDst++) = colG;
            *(ptrDst++) = colR;
        }
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    半透明の矩形を描画する。
//

ErrCode
PixelMatrix::drawTransparentRectangle(
        const  BitmapCoord  dx,
        const  BitmapCoord  dy,
        const  BitmapCoord  dw,
        const  BitmapCoord  dh,
        const  PixelValue   colR,
        const  PixelValue   colG,
        const  PixelValue   colB,
        const  int          vTr)
{
    const  BitmapCoord  dx2 = std::min((this->m_xWidth),  dx + dw);
    const  BitmapCoord  dy2 = std::min((this->m_yHeight), dy + dh);

    for ( BitmapCoord y = dy; y < dy2; ++ y ) {
        PmPixelArray    ptrDst  = this->getPixels(dx, y);
        for ( BitmapCoord x = dx; x < dx2; ++ x ) {
            const  int  cB  = *(ptrDst);
            *(ptrDst++) = ( (colB * (256 - vTr)) + (cB * vTr) ) >> 8;

            const  int  cG  = *(ptrDst);
            *(ptrDst++) = ( (colG * (256 - vTr)) + (cG * vTr) ) >> 8;

            const  int  cR  = *(ptrDst);
            *(ptrDst++) = ( (colR * (256 - vTr)) + (cR * vTr) ) >> 8;
        }
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    ビットマップの高さを取得する。
//

PixelMatrix::BitmapCoord
PixelMatrix::getHeight()  const
{
    return ( this->m_yHeight );
}

//----------------------------------------------------------------
//    ビットマップデータのアドレスを取得する。
//

PixelMatrix::PcPixelArray
PixelMatrix::getPixels()  const
{
    return ( this->m_ptrBits );
}

//----------------------------------------------------------------
//    ビットマップデータのアドレスを取得する。
//

PixelMatrix::PmPixelArray
PixelMatrix::getPixels()
{
    return ( this->m_ptrBits );
}

//----------------------------------------------------------------
//    ビットマップデータのアドレスを取得する。
//

PixelMatrix::PcPixelArray
PixelMatrix::getPixels(
        const  int  x,
        const  int  y)  const
{
    return ( (this->m_ptrBits) + computeOffset(x, y) );
}

//----------------------------------------------------------------
//    ビットマップデータのアドレスを取得する。
//

PixelMatrix::PmPixelArray
PixelMatrix::getPixels(
        const  int  x,
        const  int  y)
{
    return ( (this->m_ptrBits) + computeOffset(x, y) );
}

//----------------------------------------------------------------
//    ビットマップの幅を取得する。
//

PixelMatrix::BitmapCoord
PixelMatrix::getWidth()  const
{
    return ( this->m_xWidth );
}

//========================================================================
//
//    Protected Member Functions.
//

//----------------------------------------------------------------
//    メモリを確保する。
//

PixelMatrix::LpBuffer
PixelMatrix::allocateBuffer(
        const  Boolean  bPixels,
        const  Offset   cbHead)
{
    Offset  cbSize  =  cbHead;
    if ( bPixels ) {
        cbSize  +=  ((this->m_nLineBytes) * (this->m_yHeight));
    }

    LpBuffer    ptrBuf  = new  FSG_UInt8 [cbSize];

    this->m_ptrBuf  = (ptrBuf);
    return ( ptrBuf );
}

//----------------------------------------------------------------
//    ビットマップデータのアドレスを設定する。
//

Boolean
PixelMatrix::setPixels(
        PmPixelArray    ptrBits)
{
    this->m_ptrBits = (ptrBits);

    return ( BOOL_TRUE );
}

//----------------------------------------------------------------
//    ビットマップのパラメータを設定する。
//

ErrCode
PixelMatrix::setupParameters(
        const  BitmapCoord  cxWidth,
        const  BitmapCoord  cyHeight,
        const  BitmapDepth  bDepth)
{
    this->m_xWidth  = cxWidth;
    this->m_yHeight = cyHeight;
    this->m_nDepth  = bDepth;

    this->m_nPixelBytes = computeBytesPerPixel(bDepth);
    this->m_nLineBytes  = computeBytesPerLine (cxWidth, bDepth);

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    壱ピクセルに必要なバイト数を計算する。
//

inline  PixelMatrix::Offset
PixelMatrix::computeBytesPerPixel(
        const  BitmapDepth  bDepth)
{
    return ( static_cast<Offset>((bDepth + 7) / 8) );
}

//----------------------------------------------------------------
//    壱ラインに必要なバイト数を計算する。
//

inline  PixelMatrix::Offset
PixelMatrix::computeBytesPerLine(
        const  int  cxWidth,
        const  int  bDepth)
{
    return ( ((static_cast<Offset>(cxWidth) * bDepth + 31) / 32) * 4 );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
