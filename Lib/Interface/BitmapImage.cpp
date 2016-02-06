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

//========================================================================
//
//    BitmapImage::BitmapInfoHeader  struct.
//

struct  BitmapImage::BitmapInfoHeader
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

struct  BitmapImage::RgbQuad
{
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
};

struct  BitmapImage::BitmapInfo
{
    BitmapInfoHeader    bmiHeader;
    RgbQuad             bmiColors[1];
};

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

    size_t  cbBits  = (this->m_nLineBytes) * cyHeight;
    size_t  cbHead  = sizeof(BitmapInfoHeader);
    if ( bDepth == 8 ) {
        cbHead  += sizeof(RgbQuad) * 256;
    }

    LpBuffer        ptrBuf  = new  uint8_t [cbHead + cbBits];
    LpBitmapInfo    ptrInfo = pointer_cast<LpBitmapInfo>(ptrBuf);
    LpBitArray      ptrBits = (ptrBuf) + cbHead;
    this->m_ptrBuf  = (ptrBuf);

    ptrInfo->bmiHeader.biSize           = sizeof(BITMAPINFOHEADER);
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
//    ビットマップファイルを開いて読み込む。
//

ErrCode
BitmapImage::openBitmapFile(
        const  std::string  &fileName)
{
    FILE  *  fp = fopen(fileName.c_str(), "rb");
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
            sizeof(BitmapInfoHeader) == SIZE_OF_BITMAP_INFO_HEADER,
            "Invalid Structure Size (BitmapInfoHeader)" );

    const   WORD    fhMagic = *(pointer_cast<const  WORD  *>(ptrBuf));
    if ( fhMagic != 0x4d42 ) {
        return ( ERR_FAILURE );
    }

    LpBuffer  const    ptrByte  = new  uint8_t [cbLen + 2];
    LpBuffer  const    ptrBody  = (ptrByte + 2);

    ::memcpy( ptrByte, ptrBuf, cbLen );

    this->m_ptrInfo = pointer_cast<LpBitmapInfo>(
                            (ptrBody) + SIZE_OF_BITMAP_FILE_HEADER);

    const  BitmapInfoHeader  &  biHead  = (this->m_ptrInfo->bmiHeader);

    if ( (biHead.biSize < SIZE_OF_BITMAP_INFO_HEADER) )
    {
        return ( ERR_FAILURE );
    }

    const  int  xWidth  = biHead.biWidth;
    const  int  yHeight = biHead.biHeight;
    const  int  bDepth  = biHead.biBitCount;

    Offset  ofsBits = SIZE_OF_BITMAP_FILE_HEADER + (biHead.biSize);
    if ( bDepth == 8 ) {
        ofsBits += sizeof(RgbQuad) * 256;
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

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
