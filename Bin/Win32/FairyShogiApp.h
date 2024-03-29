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
**      An Interface of FairyShogiApp class.
**
**      @file       Bin/Win32/FairyShogiApp.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_FAIRY_SHOGI_APP_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_FAIRY_SHOGI_APP_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Win32  {

//  クラスの前方宣言。  //
class   Animation;
class   BitmapResource;

//========================================================================
//
//    FairyShogiApp  class.
//
/**
**    アプリケーションクラス。
**/

class  FairyShogiApp
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
    FairyShogiApp();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~FairyShogiApp();

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
    /**   必要な画像リソースをロードする。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    loadBitmapResources(
            const   HINSTANCE   hInst,
            const   HDC         hDC);

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   アニメーションループのコールバック関数。
    **
    **  @param [in] hWnd
    **  @param      objAnim
    **/
    static  Boolean
    callbackAnimationStep(
            const   HWND    hWnd,
            Animation     & objAnim);

    //----------------------------------------------------------------
    /**   詰みの状態であることを通知する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    showCheckMateStateMessage();

    //----------------------------------------------------------------
    /**   王手の状態であることを通知する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    showCheckStateMessage();

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   アニメーションを管理するインスタンスを取得する。
    **
    **  @return     アニメーションを管理するインスタンス。
    **/
    Animation  &
    getAnimationManager()  const;

    //----------------------------------------------------------------
    /**   現在アニメーションが実行中か確認する。
    **
    **  @retval     BOOL_TRUE   : アニメーションは実行中。
    **  @retval     BOOL_FALSE  : アニメーションは停止中。
    **/
    Boolean
    isAnimationRunning()  const;

    //----------------------------------------------------------------
    /**   盤面の画像リソースを取得する。
    **
    **  @return     画像リソースを管理するインスタンス。
    **/
    const   BitmapResource  &
    getBackBitmap()  const;

    //----------------------------------------------------------------
    /**   ダイスの画像リソースを取得する。
    **
    **  @return     画像リソースを管理するインスタンス。
    **/
    const   BitmapResource  &
    getDiceBitmap()  const;

    //----------------------------------------------------------------
    /**   その他のアイコン画像リソースを取得する。
    **
    **  @return     画像リソースを管理するインスタンス。
    **/
    const   BitmapResource  &
    getIconsBitmap()  const;

    //----------------------------------------------------------------
    /**   駒の画像リソースを取得する。
    **
    **  @return     画像リソースを管理するインスタンス。
    **/
    const   BitmapResource  &
    getPieceBitmap()  const;

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    /**   盤面の画像リソース。  **/
    BitmapResource  *   m_brBack;

    /**   駒の画像リソース。    **/
    BitmapResource  *   m_brPiece;

    /**   ダイス画像リソース。  **/
    BitmapResource  *   m_brDice;

    /**   その他画像リソース。  **/
    BitmapResource  *   m_brIcons;

    /**   アニメーション管理。  **/
    Animation  *        m_manAnim;

//========================================================================
//
//    Other Features.
//
private:
    typedef     FairyShogiApp       This;
    FairyShogiApp       (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   FairyShogiAppTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
