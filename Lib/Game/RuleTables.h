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
**      An Interface of RuleTables class.
**
**      @file       Game/RuleTables.h
**/

#if !defined( FAIRYSHOGI_GAME_INCLUDED_RULE_TABLES_H )
#    define   FAIRYSHOGI_GAME_INCLUDED_RULE_TABLES_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Game  {

//========================================================================
//
//    RuleTables  class.
//
/**
**    ルールを表現するのに必要なテーブルを管理する。
**/

class  RuleTables
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
    RuleTables();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~RuleTables();

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
public:

    //----------------------------------------------------------------
    /**   ルールテーブルを構築する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    setupRuleTables();

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//
private:

    typedef     int         TDirsTable[9];
    typedef     uint32_t    TMoveTable[25];
    typedef     uint32_t    TPinsTable[25][25];

private:

    //----------------------------------------------------------------
    /**   ルールテーブルを展開する。
    **
    **  @param [in] tblWalk   移動可能な方向のテーブル。
    **  @param [in] tblJump   移動可能な方向のテーブル。
    **  @param[out] tblMove   展開した移動テーブル。
    **  @param[out] tblPins   展開したピンテーブル。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    expandDirTable(
            const  TDirsTable  &tblWalk,
            const  TDirsTable  &tblJump,
            TMoveTable         &tblMove,
            TPinsTable         &tblPins);

//========================================================================
//
//    Member Variables.
//
private:

    static  uint32_t    s_tblMoveTo[25][20];

    static  uint32_t    s_tblMoveFrom[25][20];

//========================================================================
//
//    Other Features.
//
private:
    typedef     RuleTables      This;
    RuleTables          (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   RuleTablesTest;
};

}   //  End of namespace  Game
FAIRYSHOGI_NAMESPACE_END

#endif
