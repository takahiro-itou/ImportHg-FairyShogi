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
**      @file       Win32/BitmapImage.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_BITMAP_IMAGE_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_BITMAP_IMAGE_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    "FairyShogi/Interface/PixelMatrix.h"

#include    <string>

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINGDI_H )
#    include    <Wingdi.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINGDI_H
#endif

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    BitmapImage  class.
//
/**
**    ビットマップイメージを管理するクラス。
**/

class  BitmapImage : public  Interface::PixelMatrix
{

//========================================================================
//
//    Internal Type Definitions.
//

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

//========================================================================
//
//    Accessors.
//

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

    typedef     BITMAPINFO          TBitmapInfo;
    typedef     BITMAPINFOHEADER    TBitmapInfoHeader;
    typedef     RGBQUAD             TRgbQuad;

    typedef     TBitmapInfo  *      LpBitmapInfo;
    typedef     void  *             PmBitsBuffer;

private:

    LpBitmapInfo    m_ptrInfo;

    HBITMAP         m_hBitmap;

//========================================================================
//
//    Other Features.
//
private:
    /**   スーパークラス。  **/
    typedef     Interface::PixelMatrix      Super;

private:
    typedef     BitmapImage     This;
    BitmapImage         (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   BitmapImageTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
