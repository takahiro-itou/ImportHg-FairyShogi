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
**      An Interface of Animation class.
**
**      @file       Win32/Animation.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_ANIMATION_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_ANIMATION_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

FAIRYSHOGI_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Interface  {
class   PixelMatrix;
}   //  End of namespace  Interface

namespace  Win32  {

//========================================================================
//
//    Animation  class.
//
/**
**    アニメーションを管理するクラス。
**/

class  Animation
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
    Animation();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~Animation();

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
    /**   アニメーションの壱ステップを描画する。
    **
    **  @param[out] imgDest   描画先のイメージ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    drawAnimation(
            Interface::PixelMatrix  &imgDest);

    //----------------------------------------------------------------
    /**   アニメーションを行うためのループを実行する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    enterAnimationLoop();

    //----------------------------------------------------------------
    /**   アニメーションを次のステップに進める。
    **
    **  @retval     BOOL_TRUE   : アニメーションの続きがある。
    **  @retval     BOOL_FALSE  : アニメーションが終了した。
    **/
    virtual  Boolean
    stepAnimation();

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   アニメーションの状態を取得する。
    **
    **  @retval     BOOL_TRUE   : アニメーションを実行中。
    **  @retval     BOOL_FALSE  : アニメーションは停止中。
    **/
    Boolean
    getAnimationFlag()  const;

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
    typedef     Animation       This;
    Animation           (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   AnimationTest;
};

}   //  End of namespace  Win32
FAIRYSHOGI_NAMESPACE_END

#endif
