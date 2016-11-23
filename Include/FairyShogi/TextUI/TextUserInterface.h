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
**      An Interface of TextUserInterface class.
**
**      @file       TextUI/TextUserInterface.h
**/

#if !defined( FAIRYSHOGI_TEXTUI_INCLUDED_TEXT_USER_INTERFACE_H )
#    define   FAIRYSHOGI_TEXTUI_INCLUDED_TEXT_USER_INTERFACE_H

#include    "FairyShogi/Common/MersenneTwister.h"
#include    "FairyShogi/Interface/GraphicalInterface.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  TextUI  {

//========================================================================
//
//    TextUserInterface  class.
//
/**
**    テキストユーザーインターフェイスクラス。
**/

class  TextUserInterface
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
    TextUserInterface();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~TextUserInterface();

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
//    For Internal Use Only.
//
private:

    typedef     Interface::GraphicalInterface       GameInterface;

    typedef     Common::MersenneTwister             RandomGenerator;

    typedef     RandomGenerator::TResultInt         RandResult;

    static  CONSTEXPR_VAR   RandResult
    RANDOM_MAX_VALUE    = RandomGenerator::MaxValue<28>::VALUE;

//========================================================================
//
//    Member Variables.
//
private:

    /**   ゲームコントローラ。  **/
    GameInterface       m_giGameCtrl;

    /**   乱数のジェネレータ。  **/
    RandomGenerator     m_rndGen;

//========================================================================
//
//    Other Features.
//
private:
    typedef     TextUserInterface   This;
    TextUserInterface   (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   TextUserInterfaceTest;
};

}   //  End of namespace  TextUI
FAIRYSHOGI_NAMESPACE_END

#endif
