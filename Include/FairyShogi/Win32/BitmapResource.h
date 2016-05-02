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
**      An Interface of BitmapResource class.
**
**      @file       Win32/BitmapResource.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_BITMAP_RESOURCE_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_BITMAP_RESOURCE_H

#include    "BitmapImage.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//========================================================================
//
//    BitmapResource  class.
//
/**
**    ビットマップリソースを管理するクラス。
**/

class  BitmapResource : public  BitmapImage
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
    BitmapResource();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~BitmapResource();

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
    /**   ビットマップリソースを読み込む。
    **
    **  @param [in] hInst     インスタンスハンドル。
    **  @param [in] hDC       デバイスコンテキスト。
    **  @param [in] bmpName   ビットマップリソース名。
    **/
    virtual  ErrCode
    loadBitmapResource(
            const   HINSTANCE   hInst,
            const   HDC         hDC,
            const   LPCTSTR     bmpName);

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

//========================================================================
//
//    Member Variables.
//

//========================================================================
//
//    Other Features.
//
private:
    /**   スーパークラス。  **/
    typedef     BitmapImage         Super;

private:
    typedef     BitmapResource      This;
    BitmapResource      (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   BitmapResourceTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
