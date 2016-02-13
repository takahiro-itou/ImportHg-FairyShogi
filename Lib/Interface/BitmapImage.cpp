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
**      An Implementation of BitmapImage class.
**
**      @file       Interface/BitmapImage.cpp
**/

#include    "FairyShogi/Interface/BitmapImage.h"

#include    <stdio.h>
#include    <windows.h>
#include    <Wingdi.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

#if  !defined( FAIRYSHOGI_WIN32_API )

//========================================================================
//
//    BitmapImage::TBitmapInfoHeader  struct.
//

struct  BitmapImage::TBitmapInfoHeader
{
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;
    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;
};

struct  BitmapImage::TRgbQuad
{
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
};

struct  BitmapImage::TBitmapInfo
{
    BitmapInfoHeader    bmiHeader;
    RgbQuad             bmiColors[1];
};

#endif  //  !defined( FAIRYSHOGI_WIN32_API )

//========================================================================
//
//    BitmapImage  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

BitmapImage::BitmapImage()
    : m_xWidth (0),
      m_yHeight(0),
      m_nDepth (0),
      m_ptrBuf (nullptr),
      m_ptrInfo(nullptr),
      m_ptrBits(nullptr),
#if  defined( FAIRYSHOGI_WIN32_API )
      m_hBitmap(0),
#endif
      m_nPixelBytes(0),
      m_nLineBytes (0)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BitmapImage::~BitmapImage()
{
    destroyBitmap();
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
BitmapImage::createBitmap(
        const  int  cxWidth,
        const  int  cyHeight,
        const  int  bDepth)
{
    destroyBitmap();

    this->m_xWidth  = cxWidth;
    this->m_yHeight = cyHeight;
    this->m_nDepth  = bDepth;

    this->m_nPixelBytes = computeBytesPerPixel(bDepth);
    this->m_nLineBytes  = computeBytesPerLine (cxWidth, bDepth);

    size_t  cbHead  = sizeof(TBitmapInfoHeader);
    if ( bDepth == 8 ) {
        cbHead  += sizeof(TRgbQuad) * 256;
    }

    const  size_t   cbBits  = (this->m_nLineBytes) * cyHeight;
    LpBuffer        ptrBuf  = new  uint8_t [cbHead + cbBits];
    LpBitmapInfo    ptrInfo = pointer_cast<LpBitmapInfo>(ptrBuf);
    PmPixelArray    ptrBits = (ptrBuf) + cbHead;
    this->m_ptrBuf  = (ptrBuf);

    ptrInfo->bmiHeader.biSize           = sizeof(TBitmapInfoHeader);
    ptrInfo->bmiHeader.biWidth          = cxWidth;
    ptrInfo->bmiHeader.biHeight         = cyHeight;
    ptrInfo->bmiHeader.biBitCount       = bDepth;
    ptrInfo->bmiHeader.biPlanes         = 1;
    ptrInfo->bmiHeader.biXPelsPerMeter  = 0;
    ptrInfo->bmiHeader.biYPelsPerMeter  = 0;
    ptrInfo->bmiHeader.biClrUsed        = 0;
    ptrInfo->bmiHeader.biClrImportant   = 0;
    ptrInfo->bmiHeader.biCompression    = BI_RGB;
    ptrInfo->bmiHeader.biSizeImage      = cbBits;

    this->m_ptrInfo = (ptrInfo);
    this->m_ptrBits = (ptrBits);

    return ( ERR_SUCCESS );
}

#if  defined( FAIRYSHOGI_WIN32_API )

//----------------------------------------------------------------
//    ビットマップイメージを生成する。
//

ErrCode
BitmapImage::createBitmap(
        const  int  cxWidth,
        const  int  cyHeight,
        const  HDC  hDC)
{
    destroyBitmap();

    const  int  bDepth  = 24;

    this->m_xWidth  = cxWidth;
    this->m_yHeight = cyHeight;
    this->m_nDepth  = bDepth;

    this->m_nPixelBytes = computeBytesPerPixel(bDepth);
    this->m_nLineBytes  = computeBytesPerLine (cxWidth, bDepth);

    size_t  cbHead  = sizeof(TBitmapInfoHeader);
    if ( bDepth == 8 ) {
        cbHead  += sizeof(TRgbQuad) * 256;
    }

    const  size_t   cbBits  = (this->m_nLineBytes) * cyHeight;
    LpBuffer        ptrBuf  = new  uint8_t [cbHead];
    LpBitmapInfo    ptrInfo = pointer_cast<LpBitmapInfo>(ptrBuf);
    this->m_ptrBuf  = (ptrBuf);

    ptrInfo->bmiHeader.biSize           = sizeof(TBitmapInfoHeader);
    ptrInfo->bmiHeader.biWidth          = cxWidth;
    ptrInfo->bmiHeader.biHeight         = cyHeight;
    ptrInfo->bmiHeader.biBitCount       = bDepth;
    ptrInfo->bmiHeader.biPlanes         = 1;
    ptrInfo->bmiHeader.biXPelsPerMeter  = 0;
    ptrInfo->bmiHeader.biYPelsPerMeter  = 0;
    ptrInfo->bmiHeader.biClrUsed        = 0;
    ptrInfo->bmiHeader.biClrImportant   = 0;
    ptrInfo->bmiHeader.biCompression    = BI_RGB;
    ptrInfo->bmiHeader.biSizeImage      = cbBits;

    PmBitsBuffer    ptrBits = (NULL);
    this->m_hBitmap = ::CreateDIBSection(
                            hDC, ptrInfo, DIB_RGB_COLORS,
                            &(ptrBits), NULL, 0);
    if ( this->m_hBitmap == 0 ) {
        return ( ERR_FAILURE );
    }

    this->m_ptrBits = static_cast<PmPixelArray>(ptrBits);

    return ( ERR_SUCCESS );
}

#endif  //  defined( FAIRYSHOGI_WIN32_API )


//----------------------------------------------------------------
//    ビットマップイメージを破棄する。
//

ErrCode
BitmapImage::destroyBitmap()
{
    this->m_ptrInfo = (nullptr);
    this->m_ptrBits = (nullptr);

    delete  []  (this->m_ptrBuf);
    this->m_ptrBuf  = (nullptr);

    return ( ERR_SUCCESS );
}

#if defined( FAIRYSHOGI_WIN32_API )

//----------------------------------------------------------------
//    ビットマップを描画する。
//

ErrCode
BitmapImage::drawBitmap(
        const  HDC  hDC,
        const  int  dx,
        const  int  dy,
        const  int  w,
        const  int  h,
        const  int  ox,
        const  int  oy)
{
    const  HDC      hMemDC  = ::CreateCompatibleDC(hDC);
    const  HGDIOBJ  hOldBmp = ::SelectObject(hMemDC, this->m_hBitmap);
    ::BitBlt(hDC, dx, dy, w, h, hMemDC, ox, oy, SRCCOPY);
    ::GdiFlush();
    ::SelectObject(hMemDC, hOldBmp);
    ::DeleteDC(hMemDC);

    return ( ERR_SUCCESS );
}

#endif  //  defined( FAIRYSHOGI_WIN32_API )

//----------------------------------------------------------------
//    ビットマップファイルを開いて読み込む。
//

ErrCode
BitmapImage::openBitmapFile(
        const  std::string  &fileName)
{
    FILE  *  fp = fopen(fileName.c_str(), "rb");
    if ( fp == NULL ) {
        return ( ERR_FILE_OPEN_ERROR );
    }

    fseek(fp, 0, SEEK_END);
    const  FileLen  cbFile  = ftell(fp);
    LpBuffer    ptrBuf  = new  uint8_t [cbFile];

    fseek(fp, 0, SEEK_SET);
    fread(ptrBuf, 1, cbFile, fp);

    fclose(fp);

    return ( readBitmap(ptrBuf, cbFile) );
}

//----------------------------------------------------------------
//    ビットマップイメージを読み込む。
//

ErrCode
BitmapImage::readBitmap(
        LpReadBuf   const   ptrBuf,
        const  FileLen      cbLen)
{
    static_assert(
            sizeof(TBitmapInfoHeader) == SIZE_OF_BITMAP_INFO_HEADER,
            "Invalid Structure Size (BitmapInfoHeader)" );

    const   WORD    fhMagic = *(pointer_cast<const  WORD  *>(ptrBuf));
    if ( fhMagic != 0x4d42 ) {
        return ( ERR_FAILURE );
    }

    LpBuffer  const    ptrByte  = new  uint8_t [cbLen + 2];
    LpBuffer  const    ptrBody  = (ptrByte + 2);

    ::memcpy( ptrBody, ptrBuf, cbLen );

    this->m_ptrInfo = pointer_cast<LpBitmapInfo>(
                            (ptrBody) + SIZE_OF_BITMAP_FILE_HEADER);

    const  TBitmapInfoHeader  & biHead  = (this->m_ptrInfo->bmiHeader);

    if ( (biHead.biSize < SIZE_OF_BITMAP_INFO_HEADER) )
    {
        return ( ERR_FAILURE );
    }

    const  int  xWidth  = biHead.biWidth;
    const  int  yHeight = biHead.biHeight;
    const  int  bDepth  = biHead.biBitCount;

    Offset  ofsBits = SIZE_OF_BITMAP_FILE_HEADER + (biHead.biSize);
    if ( bDepth == 8 ) {
        ofsBits += sizeof(TRgbQuad) * 256;
    }

    this->m_xWidth  = xWidth;
    this->m_yHeight = yHeight;
    this->m_nDepth  = bDepth;

    this->m_nPixelBytes = computeBytesPerPixel(bDepth);
    this->m_nLineBytes  = computeBytesPerLine (xWidth, bDepth);

    this->m_ptrBuf  = ptrByte;
    this->m_ptrBits = (ptrBody) + ofsBits;

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
BitmapImage::copyRectangle(
        const  int          dx,
        const  int          dy,
        const  int          dw,
        const  int          dh,
        const  BitmapImage  &bmpSrc,
        const  int          sx,
        const  int          sy)
{
    for ( int y = 0; y < dh; ++ y ) {
        PcPixelArray    ptrSrc  = bmpSrc.getPixels(sx, sy + y);
        PmPixelArray    ptrDst  = this->getPixels(dx, dy + y);
        for ( int x = 0; x < dw; ++ x ) {
            *(ptrDst++) = *(ptrSrc++);      //  B
            *(ptrDst++) = *(ptrSrc++);      //  G
            *(ptrDst++) = *(ptrSrc++);      //  R
        }
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    半透明の矩形を描画する。
//

ErrCode
BitmapImage::drawTransparentRectangle(
        const  int          dx,
        const  int          dy,
        const  int          dw,
        const  int          dh,
        const  PixelValue   colR,
        const  PixelValue   colG,
        const  PixelValue   colB,
        const  int          vTr)
{
    const  int  dx2 = std::min((this->m_xWidth),  dx + dw);
    const  int  dy2 = std::min((this->m_yHeight), dy + dh);

    for ( int y = dy; y < dy2; ++ y ) {
        PmPixelArray    ptrDst  = this->getPixels(dx, y);
        for ( int x = dx; x < dx2; ++ x ) {
            const  int  cB  = *(ptrDst);
            *(ptrDst++) = ( (colB * (1 - vTr)) + (cB * vTr) ) >> 8;

            const  int  cG  = *(ptrDst);
            *(ptrDst++) = ( (colG * (1 - vTr)) + (cG * vTr) ) >> 8;

            const  int  cR  = *(ptrDst);
            *(ptrDst++) = ( (colR * (1 - vTr)) + (cR * vTr) ) >> 8;
        }
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    壱ピクセルに必要なバイト数を計算する。
//

inline  size_t
BitmapImage::computeBytesPerPixel(
        const  int  bDepth)
{
    return ( static_cast<Offset>((bDepth + 7) / 8) );
}

//----------------------------------------------------------------
//    壱ラインに必要なバイト数を計算する。
//

inline  size_t
BitmapImage::computeBytesPerLine(
        const  int  cxWidth,
        const  int  bDepth)
{
    return ( ((static_cast<Offset>(cxWidth) * bDepth + 31) / 32) * 4 );
}

//----------------------------------------------------------------
//    ビットマップデータの先頭からのオフセットを計算する。
//

inline  const   BitmapImage::Offset
BitmapImage::computeOffset(
        const  int  x,
        const  int  y)  const
{
    return ( (( (this->m_yHeight) - y - 1) * (this->m_nLineBytes))
             + ((this->m_nPixelBytes) * x) );
}

//----------------------------------------------------------------
//    ビットマップデータのアドレスを取得する。
//

inline  BitmapImage::PcPixelArray
BitmapImage::getPixels()  const
{
    return ( this->m_ptrBits );
}

//----------------------------------------------------------------
//    ビットマップデータのアドレスを取得する。
//

inline  BitmapImage::PmPixelArray
BitmapImage::getPixels()
{
    return ( this->m_ptrBits );
}

//----------------------------------------------------------------
//    ビットマップデータのアドレスを取得する。
//

inline  BitmapImage::PcPixelArray
BitmapImage::getPixels(
        const  int  x,
        const  int  y)  const
{
    return ( (this->m_ptrBits) + computeOffset(x, y) );
}


//----------------------------------------------------------------
//    ビットマップデータのアドレスを取得する。
//

inline  BitmapImage::PmPixelArray
BitmapImage::getPixels(
        const  int  x,
        const  int  y)
{
    return ( (this->m_ptrBits) + computeOffset(x, y) );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
