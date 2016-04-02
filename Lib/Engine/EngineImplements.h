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

#include    "FairyShogi/Common/FairyShogiConst.h"
#include    "FairyShogi/Game/BoardState.h"

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
protected:
    typedef     Game::BoardState                BoardState;

    typedef     std::vector<ActionView>         ActionViewList;

    typedef     BoardState::InternState         InternState;
    typedef     BoardState::ActionData          ActionData;
    typedef     BoardState::ActionList          ActionList;
    typedef     ActionList::const_iterator      ActIter;
    typedef     BoardState::TBitBoard           TBitBoard;

    typedef     ActionViewList::const_iterator  ActViewIter;
    typedef     int                             ActionCount;

    /**   ダイスの目をインデックスとする整数値配列型。  **/
    typedef     ActionCount     TCountArray [Common::DICE_MAX_VALUE];

    enum  {
        /**
        **    任意の手を指すことができるダイスの目。
        **
        **    内部データでは、ゼロベースのため、壱ずれる。
        **/
        ENGINE_IDICE_ANY_MOVE   =  Common::DICE_ANY_MOVE - 1
    };

protected:

    //----------------------------------------------------------------
    /**   相手の玉をチェックメイトできる手を検索する。
    **
    **  @param [in] curStat   現在の局面。
    **  @param [in] piTurn    現在の手番のプレーヤー番号。
    **  @param [in] actList   現在の局面の合法手リスト。
    **  @param[out] nCounts   チェックメイトできる手の総数。
    **      ダイスの出目ごとに集計される。
    **  @return     チェックメイト可能な、ダイスの目の数。
    **/
    static  ActionCount
    findCheckMateActions(
            const  InternState  &curStat,
            const  PlayerIndex  piTurn,
            const  ActionList   &actList,
            TCountArray         nCounts);

    //----------------------------------------------------------------
    /**   相手の玉をチェックメイトできる手を検索する。
    **
    **  @param [in] curStat   現在の局面。
    **  @param [in] piTurn    現在の手番のプレーヤー番号。
    **  @param [in] actList   現在の局面の合法手リスト。
    **  @param[out] itrRet    詰みになる手を指す反復子。
    **      なお、複数存在する場合は、最初のものを返す。
    **      どの手も詰みにならない場合は、未定義となる。
    **  @retval     BOOL_TRUE     詰みを発見。
    **  @retval     BOOL_FALSE    詰みは無かった。
    **/
    static  Boolean
    findCheckMateAction(
            const  InternState      &curStat,
            const  PlayerIndex      piTurn,
            const  ActionViewList   &actList,
            ActViewIter  *          itrRet);

    //----------------------------------------------------------------
    /**   現在の局面がチェックメイトかどうかを判定する。
    **
    **  @param [in] curStat   現在の局面。
    **  @param [in] piTurn    現在の手番のプレーヤー番号。
    **  @retval     BOOL_TRUE     チェックメイト。
    **  @retval     BOOL_FALSE    それ以外。
    **/
    static  Boolean
    isCheckMateState(
            const  InternState  &curStat,
            const  PlayerIndex  piTurn);

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
            const  InternState  &curStat,
            const  PlayerIndex  piTurn,
            const  TConstraint  vCons,
            ActionList          &actList);

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
