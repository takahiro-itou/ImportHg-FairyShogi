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
**      An Interface of PixelMatrix class.
**
**      @file       Interface/PixelMatrix.h
**/

#if !defined( FAIRYSHOGI_INTERFACE_INCLUDED_PIXEL_MATRIX_H )
#    define   FAIRYSHOGI_INTERFACE_INCLUDED_PIXEL_MATRIX_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    PixelMatrix  class.
//
/**
**    ビットマップイメージを管理するクラス。
**/

class  PixelMatrix
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   ピクセルの輝度値型。  **/
    typedef     uint8_t                 PixelValue;

    /**   ピクセルの座標を指定する型。  **/
    typedef     int                     BitmapCoord;

    /**   ピクセルの深さを指定する型。  **/
    typedef     int                     BitmapDepth;

    /**   輝度値の配列型。      **/
    typedef     PixelValue  *           PmPixelArray;

    /**   輝度値の配列型。      **/
    typedef     const   PixelValue  *   PcPixelArray;

    /**   バッファの型。        **/
    typedef     uint8_t  *              LpBuffer;

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
    PixelMatrix();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~PixelMatrix();

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
    createPixelMatrix(
            const  BitmapCoord  cxWidth,
            const  BitmapCoord  cyHeight,
            const  BitmapDepth  bDepth);

    //----------------------------------------------------------------
    /**   ビットマップイメージを生成する。
    **
    **  @param [in] cxWidth     幅。
    **  @param [in] cyHeight    高さ。
    **  @param [in] bDepth      深さ。
    **  @param      ptrBits     輝度値の配列。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    createPixelMatrix(
            const  BitmapCoord  cxWidth,
            const  BitmapCoord  cyHeight,
            const  BitmapDepth  bDepth,
            PmPixelArray        ptrBits);

    //----------------------------------------------------------------
    /**   ビットマップイメージを破棄する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    destroyPixelMatrix();

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
            const  PixelMatrix  &bmpSrc,
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
            const  PixelMatrix  &bmpSrc,
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
//    Protected Member Functions.
//
protected:

    typedef     size_t              Offset;

protected:

    //----------------------------------------------------------------
    /**   メモリを確保する。
    **
    **  @param [in] bPixels   ピクセル配列を確保する。
    **      -   真の場合は、設定済みのパラメータに基づいて、
    **          必要な容量が自動で計算され確保される。
    **      -   偽の場合は、ヘッダサイズだけが確保される。
    **  @param [in] cbHead    ヘッダとして追加するサイズ。
    **  @return     確保した領域を指すポインタ。
    **      関数が失敗した場合は NULL を返す。
    **  @note       確保されたメモリは自動的に破棄される。
    **/
    LpBuffer
    allocateBuffer(
            const  Boolean  bPixels,
            const  Offset   cbHead);

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
    /**   ビットマップのパラメータを設定する。
    **
    **  @param [in] cxWidth     幅。
    **  @param [in] cyHeight    高さ。
    **  @param [in] bDepth      深さ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setupParameters(
            const  BitmapCoord  cxWidth,
            const  BitmapCoord  cyHeight,
            const  BitmapDepth  bDepth);

//========================================================================
//
//    For Internal Use Only.
//
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
protected:

    typedef     void  *             PmBitsBuffer;

private:
protected:

    BitmapCoord     m_xWidth;
    BitmapCoord     m_yHeight;
    BitmapDepth     m_nDepth;

    LpBuffer        m_ptrBuf;
    PmPixelArray    m_ptrBits;

    /**   壱ピクセルあたりのバイト数。  **/
    Offset          m_nPixelBytes;

    /**   壱ラインあたりのバイト数。    **/
    Offset          m_nLineBytes;

//========================================================================
//
//    Other Features.
//
private:
    typedef     PixelMatrix     This;
    PixelMatrix         (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   PixelMatrixTest;
};

//========================================================================
//
//    Implementation of Inline Functions.
//

//----------------------------------------------------------------
//    ビットマップデータの先頭からのオフセットを計算する。
//

inline  PixelMatrix::Offset
PixelMatrix::computeOffset(
        const  int  x,
        const  int  y)  const
{
    return ( (( (this->m_yHeight) - y - 1) * (this->m_nLineBytes))
             + ((this->m_nPixelBytes) * x) );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
