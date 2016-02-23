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

#include    "FairyShogi/Game/BoardState.h"

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
public:

    /**
    **    ビットボード用の型。
    **/
    typedef     uint32_t        BitBoardVal;

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
public:

    //----------------------------------------------------------------
    /**   ピンマスクを取得する。
    **
    **  @param [in] piMove    移動させる駒の種類。
    **  @param [in] fiTrg     移動先。
    **  @param [in] fiSrc     移動元。
    **/
    static  BitBoardVal
    getPinMask(
            const  PieceIndex   piMove,
            const  FieldIndex   fiTrg,
            const  FieldIndex   fiSrc);

//========================================================================
//
//    For Internal Use Only.
//
private:

    enum  {
        POS_NUM_ROWS    =  BoardState::POS_NUM_ROWS,
        POS_NUM_COLS    =  BoardState::POS_NUM_COLS,
        FIELD_SIZE      =  POS_NUM_ROWS * POS_NUM_COLS,
        NUM_PIECE_TYPES =  BoardState::NUM_FIELD_PIECE_TYPES,
        NUM_HAND_TYPES  =  BoardState::NUM_HAND_TYPES,
        MAX_DIRECTIONS  =  9
    };

    typedef     int             TDirsTable[MAX_DIRECTIONS];
    typedef     BitBoardVal     TMoveTable[FIELD_SIZE];
    typedef     BitBoardVal     TPinsTable[FIELD_SIZE][FIELD_SIZE];

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
public:

    static  BitBoardVal
    s_tblMoveTo[FIELD_SIZE][NUM_PIECE_TYPES];

    static  BitBoardVal
    s_tblMoveFrom[FIELD_SIZE][NUM_PIECE_TYPES];

    static  BitBoardVal
    s_tblPin[NUM_PIECE_TYPES][FIELD_SIZE][FIELD_SIZE];

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
