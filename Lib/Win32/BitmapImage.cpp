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
**      @file       Win32/BitmapImage.cpp
**/

#include    "FairyShogi/Win32/BitmapImage.h"

#include    "FairyShogi/Common/HelperMacros.h"

#include    <memory.h>
#include    <stdio.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

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
    : Super(),
      m_ptrInfo(nullptr),
      m_hBitmap(0)
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
        const  BitmapCoord  cxWidth,
        const  BitmapCoord  cyHeight,
        const  BitmapDepth  bDepth)
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

//----------------------------------------------------------------
//    ビットマップイメージを生成する。
//

ErrCode
BitmapImage::createBitmap(
        const  BitmapCoord  cxWidth,
        const  BitmapCoord  cyHeight,
        const  HDC          hDC)
{
    destroyBitmap();

    const  BitmapDepth  bDepth  = 24;

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

//----------------------------------------------------------------
//    ビットマップを描画する。
//

ErrCode
BitmapImage::drawBitmap(
        const  HDC          hDC,
        const  BitmapCoord  dx,
        const  BitmapCoord  dy,
        const  BitmapCoord  w,
        const  BitmapCoord  h,
        const  BitmapCoord  ox,
        const  BitmapCoord  oy)
{
    const  HDC      hMemDC  = ::CreateCompatibleDC(hDC);
    const  HGDIOBJ  hOldBmp = ::SelectObject(hMemDC, this->m_hBitmap);
    ::BitBlt(hDC, dx, dy, w, h, hMemDC, ox, oy, SRCCOPY);
    ::GdiFlush();
    ::SelectObject(hMemDC, hOldBmp);
    ::DeleteDC(hMemDC);

    return ( ERR_SUCCESS );
}

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

    const  ErrCode  retErr  =  readBitmap(ptrBuf, cbFile);
    return ( retErr );
}

//----------------------------------------------------------------
//    ビットマップイメージを読み込む。
//

ErrCode
BitmapImage::readBitmap(
        LpcReadBuf  const   ptrBuf,
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

    const  BitmapCoord  xWidth  = biHead.biWidth;
    const  BitmapCoord  yHeight = biHead.biHeight;
    const  BitmapDepth  bDepth  = biHead.biBitCount;

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

//----------------------------------------------------------------
//    ビットマップイメージをファイルに書き込む。
//

ErrCode
BitmapImage::saveBitmapFile(
        const  std::string  &fileName)  const
{
    FILE  *  fp = fopen(fileName.c_str(),  "wb");
    if ( fp == NULL ) {
        return ( ERR_FILE_OPEN_ERROR );
    }

    BITMAPINFOHEADER    biHead;
    BITMAPFILEHEADER    bfHead;

    const  size_t   cbBits  = (this->m_nLineBytes) * getHeight();

    ::memcpy( &biHead,  &(this->m_ptrInfo->bmiHeader),  sizeof(biHead) );
    bfHead.bfType       =  0x4d42;
    bfHead.bfSize       =  SIZE_OF_BITMAP_FILE_HEADER
            + (biHead.biSize) +  cbBits;
    bfHead.bfReserved1  =  0;
    bfHead.bfReserved2  =  0;
    bfHead.bfOffBits    =  SIZE_OF_BITMAP_FILE_HEADER + (biHead.biSize);

    ::fwrite( &bfHead, 1, sizeof(bfHead), fp );
    ::fwrite( &biHead, 1, sizeof(biHead), fp );
    ::fwrite( this->m_ptrBits, 1, cbBits, fp );
    ::fclose(fp);

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

//----------------------------------------------------------------
//    壱ピクセルに必要なバイト数を計算する。
//

inline  BitmapImage::Offset
BitmapImage::computeBytesPerPixel(
        const  BitmapDepth  bDepth)
{
    return ( static_cast<Offset>((bDepth + 7) / 8) );
}

//----------------------------------------------------------------
//    壱ラインに必要なバイト数を計算する。
//

inline  BitmapImage::Offset
BitmapImage::computeBytesPerLine(
        const  int  cxWidth,
        const  int  bDepth)
{
    return ( ((static_cast<Offset>(cxWidth) * bDepth + 31) / 32) * 4 );
}

//----------------------------------------------------------------
//    ビットマップデータの先頭からのオフセットを計算する。
//

inline  BitmapImage::Offset
BitmapImage::computeOffset(
        const  int  x,
        const  int  y)  const
{
    return ( (( (this->m_yHeight) - y - 1) * (this->m_nLineBytes))
             + ((this->m_nPixelBytes) * x) );
}

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END
