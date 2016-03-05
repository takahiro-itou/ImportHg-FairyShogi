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

//========================================================================
//
//    Public Member Functions (Virtual Functions).
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
            ActionView          &actRet);

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Protected Member Functions.
//
//
protected:
    typedef     Game::BoardState            BoardState;

    typedef     std::vector<ActionView>     ActionViewList;

protected:

    //----------------------------------------------------------------
    /**   現在の局面の合法手を列挙する。
    **
    **  @param [in] curStat   現在の局面。
    **  @param [in] piTurn    現在の手番のプレーヤー番号。
    **  @param [in] vCons     制約条件。
    **  @param[out] actList   合法手のリストを受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    makeLegalActionList(
            const  BoardState   &curStat,
            const  PlayerIndex  piTurn,
            const  TConstraint  vCons,
            ActionViewList      &actList);

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
