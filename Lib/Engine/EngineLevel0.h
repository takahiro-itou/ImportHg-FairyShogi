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
**      An Interface of EngineLevel0 class.
**
**      @file       Engine/EngineLevel0.h
**/

#if !defined( FAIRYSHOGI_ENGINE_INCLUDED_ENGINE_LEVEL_0_H )
#    define   FAIRYSHOGI_ENGINE_INCLUDED_ENGINE_LEVEL_0_H

#include    "EngineImplements.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Engine  {

//========================================================================
//
//    EngineLevel0  class.
//
/**
**    思考エンジンクラス。
**/

class  EngineLevel0 : public  EngineImplements
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
    EngineLevel0();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~EngineLevel0();

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
            ActionView          &actRet)  OVERRIDE;

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
    /**   スーパークラス。  **/
    typedef     EngineImplements    Super;

private:
    typedef     EngineLevel0        This;
    EngineLevel0        (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   EngineLevel0Test;
};

}   //  End of namespace  Engine
FAIRYSHOGI_NAMESPACE_END

#endif
