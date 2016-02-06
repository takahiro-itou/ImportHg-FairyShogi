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
            const  int  cxWidth,
            const  int  cyHeight,
            const  int  bDepth);

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
            LpReadBuf   const   ptrBuf,
            const  FileLen      cbLen);

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

    //----------------------------------------------------------------
    /**   壱ピクセルに必要なバイト数を計算する。
    **
    **  @param [in] bDepth    深さ。
    **  @return     壱ピクセルに必要なバイト数。
    **/
    static  inline  size_t
    computeBytesPerPixel(
            const  int  bDepth);

    //----------------------------------------------------------------
    /**   壱ラインに必要なバイト数を計算する。
    **
    **  @param [in] cxWidth   幅。
    **  @param [in] bDepth    深さ。
    **  @return     壱ラインに必要なバイト数。
    **/
    static  inline  size_t
    computeBytesPerLine(
            const  int  cxWidth,
            const  int  bDepth);


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


    struct      BitmapInfo;

    typedef     uint8_t  *          LpBuffer;
    typedef     BitmapInfo  *       LpBitmapInfo;
    typedef     void  *             LpBitArray;

    typedef     size_t              Offset;

private:

    int             m_xWidth;
    int             m_yHeight;
    int             m_nDepth;

    LpBuffer        m_ptrBuf;
    LpBitmapInfo    m_ptrInfo;
    LpBitArray      m_ptrBits;


    /**   壱ピクセルあたりのバイト数。  **/
    Offset          m_nPixelBytes;

    /**   壱ラインあたりのバイト数。    **/
    Offset          m_nLineBytes;

//========================================================================
//
//    Other Features.
//
private:

    struct      BitmapInfoHeader;
    struct      RgbQuad;

    typedef     uint8_t         BYTE;
    typedef     int32_t         LONG;
    typedef     uint16_t        WORD;
    typedef     uint32_t        DWORD;

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
