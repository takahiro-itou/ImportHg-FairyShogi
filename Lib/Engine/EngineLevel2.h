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
**      An Interface of EngineLevel2 class.
**
**      @file       Engine/EngineLevel2.h
**/

#if !defined( FAIRYSHOGI_ENGINE_INCLUDED_ENGINE_LEVEL_2_H )
#    define   FAIRYSHOGI_ENGINE_INCLUDED_ENGINE_LEVEL_2_H

#include    "EngineImplements.h"

#include    "FairyShogi/Common/MersenneTwister.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Engine  {

//========================================================================
//
//    EngineLevel2  class.
//
/**
**    思考エンジンクラス。
**/

class  EngineLevel2 : public  EngineImplements
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
    EngineLevel2();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~EngineLevel2();

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
            ActionView          &actRet)  override;

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
private:

    typedef     Common::MersenneTwister         RandomGenerator;
    typedef     RandomGenerator::TResultInt     RandResult;

    enum  {
        RANDOM_MAX_VALUE    =  RandomGenerator::MaxValue<28>::VALUE
    };

private:

    RandomGenerator     m_rndGen;

//========================================================================
//
//    Other Features.
//
private:
    /**   スーパークラス。  **/
    typedef     EngineImplements    Super;

private:
    typedef     EngineLevel2        This;
    EngineLevel2        (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   EngineLevel2Test;
};

}   //  End of namespace  Engine
FAIRYSHOGI_NAMESPACE_END

#endif
