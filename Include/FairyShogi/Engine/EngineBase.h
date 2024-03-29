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
**      An Interface of EngineBase class.
**
**      @file       Engine/EngineBase.h
**/

#if !defined( FAIRYSHOGI_ENGINE_INCLUDED_ENGINE_BASE_H )
#    define   FAIRYSHOGI_ENGINE_INCLUDED_ENGINE_BASE_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#if !defined( FAIRYSHOGI_SYS_INCLUDED_STL_STRING )
#    include    <string>
#    define     FAIRYSHOGI_SYS_INCLUDED_STL_STRING
#endif

#if !defined( FAIRYSHOGI_SYS_INCLUDED_STL_VECTOR )
#    include    <vector>
#    define     FAIRYSHOGI_SYS_INCLUDED_STL_VECTOR
#endif

FAIRYSHOGI_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Common  {
struct  ActionView;
struct  ViewBuffer;
}   //  End of namespace  Common

namespace  Game  {
class   BoardState;
}   //  End of namespace  Game

namespace  Engine  {

//========================================================================
//
//    EngineBase  class.
//
/**
**    思考エンジンの基底クラス。
**/

class  EngineBase
{

//========================================================================
//
//    Factory.
//
public:

    //----------------------------------------------------------------
    /**   思考エンジンのインスタンスを生成する。
    **
    **  @param [in] engName   生成するエンジン名。
    **  @return     生成したインスタンス（指すポインタ）。
    **/
    static  EngineBase  *
    createEngine(
            const  std::string  &engName);

    //----------------------------------------------------------------
    /**   思考エンジンのインスタンスを破棄する。
    **
    **  @param [in,out] ptrEng    思考エンジンのインスタンス
    **      （指すポインタ変数の参照）。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **  @note       ポインタが NULL の場合は何もしない。
    **/
    static  ErrCode
    destroyEngine(
            EngineBase  *  &ptrEng);

//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     Common::ActionView          ActionView;
    typedef     Common::ViewBuffer          ViewBuffer;

    /**   制約条件（ダイスの目）を表す型。  **/
    typedef     int     TConstraint;

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
    EngineBase();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~EngineBase();

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
public:

    //----------------------------------------------------------------
    /**   コンピュータの思考を開始する。
    **
    **  @param [in] vbCur     現在の局面。
    **  @param [in] piTurn    現在の手番のプレーヤー番号。
    **  @param [in] vCons     制約条件。
    **  @param[out] actRet    思考した結果を受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    computeBestAction(
            const  ViewBuffer   &vbCur,
            const  PlayerIndex  piTurn,
            const  TConstraint  vCons,
            ActionView          &actRet)  = 0;

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
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
    typedef     EngineBase      This;
    EngineBase          (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   EngineBaseTest;
};

}   //  End of namespace  Engine
FAIRYSHOGI_NAMESPACE_END

#endif
