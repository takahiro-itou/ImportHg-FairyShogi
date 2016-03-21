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
**      An Implementation of EngineBase class.
**
**      @file       Engine/EngineBase.cpp
**/

#include    "FairyShogi/Engine/EngineBase.h"

#include    "EngineLevel0.h"
#include    "EngineLevel1.h"
#include    "EngineLevel2.h"
#include    "EngineLevel3.h"

#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/HelperMacros.h"
#include    "FairyShogi/Game/BoardState.h"

#include    <iostream>
#include    <sstream>
#include    <stdexcept>
#include    <stdlib.h>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Engine  {

//========================================================================
//
//    EngineBase  class.
//

//========================================================================
//
//    Factory.
//

//----------------------------------------------------------------
//    思考エンジンのインスタンスを生成する。
//

EngineBase  *
EngineBase::createEngine(
        const  std::string  &engName)
{
    EngineBase  *   ptrEng  =  (nullptr);

    if ( (engName == "default") || (engName == "level3") ) {
        ptrEng  =  new  EngineLevel3;
    } else if ( engName == "level2" ) {
        ptrEng  =  new  EngineLevel2;
    } else if ( engName == "level1" ) {
        ptrEng  =  new  EngineLevel1;
    } else if ( engName == "level0" ) {
        ptrEng  =  new  EngineLevel0;
    } else {
        std::stringstream   ss;
        ss  <<  "Invalid Engine Name ["
            <<  engName
            <<  ']';
        std::cerr  << ss.str()  <<  std::endl;
        throw  std::runtime_error(ss.str());
    }

    return ( ptrEng );
}

//----------------------------------------------------------------
//    思考エンジンのインスタンスを破棄する。
//

ErrCode
EngineBase::destroyEngine(
        EngineBase  *  &ptrEng)
{
    if ( ptrEng != (nullptr) ) {
        delete  ptrEng;
    }

    ptrEng  = (nullptr);
    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

EngineBase::EngineBase()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

EngineBase::~EngineBase()
{
}

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
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Engine
FAIRYSHOGI_NAMESPACE_END
