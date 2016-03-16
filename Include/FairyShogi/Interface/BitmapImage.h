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
**      An Interface of BitmapImage class.
**
**      @file       Interface/BitmapImage.h
**/

#if !defined( FAIRYSHOGI_INTERFACE_INCLUDED_BITMAP_IMAGE_H )
#    define   FAIRYSHOGI_INTERFACE_INCLUDED_BITMAP_IMAGE_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    <string>

#if defined( FAIRYSHOGI_WIN32_API )
#    if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#        define     STRICT
#        define     WIN32_LEAN_AND_MEAN
#        include    <windows.h>
#        define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#    endif

#    if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINGDI_H )
#        include    <Wingdi.h>
#        define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINGDI_H
#    endif
#endif

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    BitmapImage  class.
//
/**
**    ビットマップイメージを管理するクラス。
**/

class  BitmapImage
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   ピクセルの輝度値型。  **/
    typedef     uint8_t     PixelValue;

    /**   ピクセルの座標を指定する型。  **/
    typedef     int         BitmapCoord;

    /**   ピクセルの深さを指定する型。  **/
    typedef     int         BitmapDepth;

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    BitmapImage();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~BitmapImage();

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
public:

    //----------------------------------------------------------------
    /**   ビットマップイメージを生成する。
    **
    **  @param [in] cxWidth     幅。
    **  @param [in] cyHeight    高さ。
    **  @param [in] bDepth      深さ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    createBitmap(
            const  BitmapCoord  cxWidth,
            const  BitmapCoord  cyHeight,
            const  BitmapDepth  bDepth);

#if  defined( FAIRYSHOGI_WIN32_API )

    //----------------------------------------------------------------
    /**   ビットマップイメージを生成する。
    **
    **  @param [in] cxWidth     幅。
    **  @param [in] cyHeight    高さ。
    **  @param [in] hDC         デバイスコンテキスト。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    createBitmap(
            const  BitmapCoord  cxWidth,
            const  BitmapCoord  cyHeight,
            const  HDC          hDC);

#endif  //  defined( FAIRYSHOGI_WIN32_API )

    //----------------------------------------------------------------
    /**   ビットマップイメージを破棄する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    destroyBitmap();

#if  defined( FAIRYSHOGI_WIN32_API )

    //----------------------------------------------------------------
    /**   ビットマップを描画する。
    **
    **  @param [in] hDC   描画先のデバイスコンテキスト。
    **  @param [in] dx    描画先の座標。
    **  @param [in] dy    描画先の座標。
    **  @param [in] w     描画する幅。
    **  @param [in] h     描画する高さ。
    **  @param [in] ox    部分的に描画する場合、その左端座標。
    **  @param [in] oy    部分的に描画する場合、その上端座標。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    drawBitmap(
            const  HDC          hDC,
            const  BitmapCoord  dx,
            const  BitmapCoord  dy,
            const  BitmapCoord  w,
            const  BitmapCoord  h,
            const  BitmapCoord  ox  = 0,
            const  BitmapCoord  oy  = 0);

#endif  //  defined( FAIRYSHOGI_WIN32_API )

    //----------------------------------------------------------------
    /**   ビットマップファイルを開いて読み込む。
    **
    **  @param [in] fileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    openBitmapFile(
            const  std::string  &fileName);

    //----------------------------------------------------------------
    /**   ビットマップイメージを読み込む。
    **
    **  @param [in] ptrBuf
    **  @param [in] cbLen
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    readBitmap(
            LpcReadBuf  const   ptrBuf,
            const  FileLen      cbLen);

    //----------------------------------------------------------------
    /**   ビットマップイメージをファイルに書き込む。
    **
    **  @param [in] fileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    saveBitmapFile(
            const  std::string  &fileName)  const;

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   別のビットマップの矩形をコピーする。
    **
    **  @param [in] dx        コピー先の水平座標。
    **  @param [in] dy        コピー先の垂直座標。
    **  @param [in] dw        コピーする幅。
    **  @param [in] dh        コピーする高さ。
    **  @param [in] bmpSrc    コピー元のビットマップ。
    **  @param [in] sx        コピー元の水平座標。
    **  @param [in] sy        コピー元の垂直座標。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    copyRectangle(
            const  BitmapCoord  dx,
            const  BitmapCoord  dy,
            const  BitmapCoord  dw,
            const  BitmapCoord  dh,
            const  BitmapImage  &bmpSrc,
            const  BitmapCoord  sx,
            const  BitmapCoord  sy);

    //----------------------------------------------------------------
    /**   別のビットマップの矩形をコピーする。
    **
    **  @note   コピーしない透過色を指定できる。
    **  @param [in] dx        コピー先の水平座標。
    **  @param [in] dy        コピー先の垂直座標。
    **  @param [in] dw        コピーする幅。
    **  @param [in] dh        コピーする高さ。
    **  @param [in] bmpSrc    コピー元のビットマップ。
    **  @param [in] sx        コピー元の水平座標。
    **  @param [in] sy        コピー元の垂直座標。
    **  @param [in] trColR    透過色（赤）。
    **  @param [in] trColG    透過色（緑）。
    **  @param [in] trColB    透過色（青）。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    copyRectangleWithTransparentColor(
            const  BitmapCoord  dx,
            const  BitmapCoord  dy,
            const  BitmapCoord  dw,
            const  BitmapCoord  dh,
            const  BitmapImage  &bmpSrc,
            const  BitmapCoord  sx,
            const  BitmapCoord  sy,
            const  PixelValue   trColR,
            const  PixelValue   trColG,
            const  PixelValue   trColB);

    //----------------------------------------------------------------
    /**   矩形を描画する。
    **
    **  @param [in] dx      描画先の水平座標。
    **  @param [in] dy      描画先の垂直座標。
    **  @param [in] dw      描画する幅。
    **  @param [in] dh      描画する高さ。
    **  @param [in] colR    描画する色（赤）。
    **  @param [in] colG    描画する色（緑）。
    **  @param [in] colB    描画する色（青）。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    drawRectangle(
            const  BitmapCoord  dx,
            const  BitmapCoord  dy,
            const  BitmapCoord  dw,
            const  BitmapCoord  dh,
            const  PixelValue   colR,
            const  PixelValue   colG,
            const  PixelValue   colB);

    //----------------------------------------------------------------
    /**   半透明の矩形を描画する。
    **
    **  @param [in] dx      描画先の水平座標。
    **  @param [in] dy      描画先の垂直座標。
    **  @param [in] dw      描画する幅。
    **  @param [in] dh      描画する高さ。
    **  @param [in] colR    描画する色（赤）。
    **  @param [in] colG    描画する色（緑）。
    **  @param [in] colB    描画する色（青）。
    **  @param [in] vTr     透過率。0 .. 256 で指定。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    drawTransparentRectangle(
            const  BitmapCoord  dx,
            const  BitmapCoord  dy,
            const  BitmapCoord  dw,
            const  BitmapCoord  dh,
            const  PixelValue   colR,
            const  PixelValue   colG,
            const  PixelValue   colB,
            const  int          vTr);

//========================================================================
//
//    Accessors.
//
public:

    typedef     PixelValue  *           PmPixelArray;
    typedef     const   PixelValue  *   PcPixelArray;

public:

    //----------------------------------------------------------------
    /**   ビットマップの高さを取得する。
    **
    **  @return     ビットマップの高さを返す。
    **/
    BitmapCoord
    getHeight()  const;

    //----------------------------------------------------------------
    /**   ビットマップデータのアドレスを取得する。
    **
    **  @return     ビットマップデータの先頭アドレス。
    **/
    PcPixelArray
    getPixels()  const;

    //----------------------------------------------------------------
    /**   ビットマップデータのアドレスを取得する。
    **
    **  @return     ビットマップデータの先頭アドレス。
    **/
    PmPixelArray
    getPixels();

    //----------------------------------------------------------------
    /**   ビットマップデータのアドレスを取得する。
    **
    **  @param [in] x   水平座標。
    **  @param [in] y   垂直座標。
    **  @return     指定した座標に対応するデータのアドレス。
    **/
    PcPixelArray
    getPixels(
            const  int  x,
            const  int  y)  const;

    //----------------------------------------------------------------
    /**   ビットマップデータのアドレスを取得する。
    **
    **  @param [in] x   水平座標。
    **  @param [in] y   垂直座標。
    **  @return     指定した座標に対応するデータのアドレス。
    **/
    PmPixelArray
    getPixels(
            const  int  x,
            const  int  y);

    //----------------------------------------------------------------
    /**   ビットマップの幅を取得する。
    **
    **  @return     ビットマップの幅を返す。
    **/
    BitmapCoord
    getWidth()  const;

//========================================================================
//
//    For Internal Use Only.
//
private:
    typedef     size_t              Offset;

private:

    //----------------------------------------------------------------
    /**   壱ピクセルに必要なバイト数を計算する。
    **
    **  @param [in] bDepth    深さ。
    **  @return     壱ピクセルに必要なバイト数。
    **/
    static  inline  Offset
    computeBytesPerPixel(
            const  BitmapDepth  bDepth);

    //----------------------------------------------------------------
    /**   壱ラインに必要なバイト数を計算する。
    **
    **  @param [in] cxWidth   幅。
    **  @param [in] bDepth    深さ。
    **  @return     壱ラインに必要なバイト数。
    **/
    static  inline  Offset
    computeBytesPerLine(
            const  BitmapCoord  cxWidth,
            const  BitmapDepth  bDepth);

    //----------------------------------------------------------------
    /**   ビットマップデータの先頭からのオフセットを計算する。
    **
    **  @param [in] x   水平座標。
    **  @param [in] y   垂直座標。
    **  @return     指定した座標に対応するデータのオフセット。
    **/
    inline  Offset
    computeOffset(
            const  BitmapCoord  x,
            const  BitmapCoord  y)  const;

    //----------------------------------------------------------------
    //
    //    定数。
    //
    enum  {
        /**
        **    ビットマップファイルヘッダのサイズ。
        **/
        SIZE_OF_BITMAP_FILE_HEADER  = 14,

        /**
        **    ビットマップファイルヘッダのサイズ（パディングを含む場合）。
        **/

        /**
        **    ビットマップ情報ヘッダのサイズ。
        **/
        SIZE_OF_BITMAP_INFO_HEADER  = 40
    };

//========================================================================
//
//    Member Variables.
//
private:

#if defined( FAIRYSHOGI_WIN32_API )
    typedef     BITMAPINFO          TBitmapInfo;
    typedef     BITMAPINFOHEADER    TBitmapInfoHeader;
    typedef     RGBQUAD             TRgbQuad;
#else
    struct      TBitmapInfo;
    struct      TBitmapInfoHeader;
    struct      TRgbQuad;

    typedef     uint8_t             BYTE;
    typedef     int32_t             LONG;
    typedef     uint16_t            WORD;
    typedef     uint32_t            DWORD;
#endif

    typedef     uint8_t  *          LpBuffer;
    typedef     TBitmapInfo  *      LpBitmapInfo;
    typedef     void  *             PmBitsBuffer;

private:

    BitmapCoord     m_xWidth;
    BitmapCoord     m_yHeight;
    BitmapDepth     m_nDepth;

    LpBuffer        m_ptrBuf;
    LpBitmapInfo    m_ptrInfo;
    PmPixelArray    m_ptrBits;

#if  defined( FAIRYSHOGI_WIN32_API )
    HBITMAP         m_hBitmap;
#endif  //  defined( FAIRYSHOGI_WIN32_API )

    /**   壱ピクセルあたりのバイト数。  **/
    Offset          m_nPixelBytes;

    /**   壱ラインあたりのバイト数。    **/
    Offset          m_nLineBytes;

//========================================================================
//
//    Other Features.
//
private:
    typedef     BitmapImage     This;
    BitmapImage         (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   BitmapImageTest;
};

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
