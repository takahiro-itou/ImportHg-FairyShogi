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
**      An Interface of EngineImplements class.
**
**      @file       Engine/EngineImplements.h
**/

#if !defined( FAIRYSHOGI_ENGINE_INCLUDED_ENGINE_IMPLEMENTS_H )
#    define   FAIRYSHOGI_ENGINE_INCLUDED_ENGINE_IMPLEMENTS_H

#include    "FairyShogi/Engine/EngineBase.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Engine  {

//========================================================================
//
//    EngineImplements  class.
//
/**
**    思考エンジンの実装クラス。
**/

class  EngineImplements : public  EngineBase
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
    EngineImplements();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~EngineImplements();

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
    /**   スーパークラス。  **/
    typedef     EngineBase          Super;

private:
    typedef     EngineImplements    This;
    EngineImplements    (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   EngineImplementsTest;
};

}   //  End of namespace  Engine
FAIRYSHOGI_NAMESPACE_END

#endif
