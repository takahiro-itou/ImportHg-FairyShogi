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
**      An Interface of GameController class.
**
**      @file       Interface/GameController.h
**/

#if !defined( FAIRYSHOGI_INTERFACE_INCLUDED_GAME_CONTROLLER_H )
#    define   FAIRYSHOGI_INTERFACE_INCLUDED_GAME_CONTROLLER_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    "FairyShogi/Common/DefaultShogiPieces.h"
#include    "FairyShogi/Common/FairyShogiConst.h"

#include    "FairyShogi/Game/BoardState.h"

#include    <iosfwd>

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
}   //  End of namespace  Common

namespace  Engine  {
class   EngineBase;
}   //  End of namespace  Engine

namespace  Interface  {

//========================================================================
//
//    GameController  class.
//
/**
**    ゲームの進行を管理するクラス。
**/

class  GameController
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     Common::ActionView              ActionView;
    typedef     std::vector<ActionView>         ActionViewList;

    /**   制約条件（ダイスの目）を表す型。  **/
    typedef     int     TConstraint;

    /**   座標の表示関係のフラグ。  **/
    enum  ShowCoordFlagValues
    {
        SCF_NORMAL_SHOW     = 0,    /**<  通常表示（右上を１一）。  **/
        SCF_FLIP_COLUMNS    = 1,    /**<  水平方向の座標を反転。    **/
        SCF_ROTATE_BOARD    = 2,    /**<  盤面をπラジアン回転。    **/
        SCF_ROTATE_FLIP     = 3     /**<  水平反転後、回転も実施。  **/
    };

    typedef     int     ShowCoordFlags;

    typedef     Game::BoardState::ActionData    ActionData;
    typedef     std::vector<ActionData>         ActionDataList;

    typedef     std::vector<PieceIndex>         PromoteList;

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
    GameController();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~GameController();

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
    **  @param[out] actRet    思考した結果を受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    computeBestAction(
            ActionView  &actRet);

    //----------------------------------------------------------------
    /**   現在の局面の合法手を列挙する。
    **
    **  @param [in] fLegals   合法判定フラグ。
    **      このフラグで指定した非合法手も列挙する。
    **      ゼロを指定すると合法手のみ列挙する。
    **  @param [in] vCons     制約条件を指定する。
    **      負の数を指定すると現在の条件を使う。
    **      ゼロを指定すると制約条件無しで扱う。
    **  @param[out] actList   合法手のリストを受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    makeLegalActionList(
            const  ActionFlag   fLegals,
            const  TConstraint  vCons,
            ActionViewList      &actList)  const;

    //----------------------------------------------------------------
    /**   最後に入力した指し手で盤面を戻す。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    playBackward();

    //----------------------------------------------------------------
    /**   指定した指し手で盤面を戻す。
    **
    **  @param [in]     actBwd    指し手データの内部形式。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    playBackward(
            const  ActionView   &actBwd);

    //----------------------------------------------------------------
    /**   指定した指し手で盤面を進める。
    **
    **  @param [in] actFwd    指し手データの表示用形式。
    **  @retval     ERR_SUCCESS           合法手。
    **  @retval     ERR_ILLEGAL_ACTION    非合法。
    **/
    virtual  ErrCode
    playForward(
            const  ActionView   &actFwd);

    //----------------------------------------------------------------
    /**   盤面を初期状態に設定する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    resetGame();

    //----------------------------------------------------------------
    /**   ゲームの状態と勝敗を判定する。
    **
    **  @return     ゲーム状態を返す。
    **/
    virtual  GameStateFlags
    testGameStateResult();

    //----------------------------------------------------------------
    /**   表示用棋譜データの内容をストリームに出力する。
    **
    **  @param [in] actView   棋譜表示用構造体。
    **  @param[out] outStr    出力ストリーム。
    **  @return     出力後のストリームの参照を返す。
    **/
    virtual  std::ostream  &
    writeActionView(
            const  ActionView   &actView,
            std::ostream        &outStr)  const;

    //----------------------------------------------------------------
    /**   棋譜データを表示用に変換する。
    **
    **  @param[out] actList   棋譜表示用構造体の配列。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    writeActionList(
            ActionViewList  &actList)  const;

    //----------------------------------------------------------------
    /**   現在の盤面を表示用バッファにコピーする。
    **
    **  @param[out] bufView   表示用バッファ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    writeToViewBuffer(
            Common::ViewBuffer  &bufView)  const;

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   指し手の表示用形式を比較して、等しいかどうかを返す。
    **
    **  @param [in] avLhs   左辺。
    **  @param [in] avRhs   右辺。
    **  @return     二つの指し手が同じものなら真を返す。
    **/
    static  bool
    isEquals(
            const  ActionView  &avLhs,
            const  ActionView  &avRhs);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   現在の盤面の状態を取得する。
    **
    **  @return     盤面の状態。
    **/
    const   Game::BoardState  &
    getBoardState()  const;

    //----------------------------------------------------------------
    /**   合法手の制約を取得する。
    **
    **  @return     制約条件を返す。
    **/
    TConstraint
    getConstraint()  const;

    //----------------------------------------------------------------
    /**   合法手の制約を指定する。
    **
    **  @param [in] vCons   制約条件。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setConstraint(
            const  TConstraint  vCons);

    //----------------------------------------------------------------
    /**   現在の手番を持つプレーヤーを取得する。
    **
    **  @return     手番のプレーヤー番号を返す。
    **/
    PlayerIndex
    getCurrentPlayer()  const;

    //----------------------------------------------------------------
    /**   現在の手番を持つプレーヤーを設定する。
    **
    **  @param [in] cPlayer   プレーヤー番号。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setCurrentPlayer(
            const  PlayerIndex  cPlayer);

    //----------------------------------------------------------------
    /**   指定した座標にある駒を取得する。
    **
    **  @param [in] xCol      横方向の座標。
    **  @param [in] yRow      縦方向の座標。
    **  @return     指定した座標の駒番号を返す。
    **/
    Common::EFieldPiece
    getFieldPiece(
            const  PosCol   xCol,
            const  PosRow   yRow)  const;

    //----------------------------------------------------------------
    /**   ゲームの勝敗を取得する。
    **
    **  @return     ゲームの勝敗を返す。
    **/
    GameResultVals
    getGameResult()  const;

    //----------------------------------------------------------------
    /**   現在のゲームの状態を取得する。
    **
    **  @return     ゲーム状態を返す。
    **/
    GameStateFlags
    getGameStateFlags()  const;

    //----------------------------------------------------------------
    /**   現在の盤面の表示フラグを取得する。
    **
    **  @return     盤面表示フラグ。
    **/
    ShowCoordFlags
    getShowFlag()  const;

    //----------------------------------------------------------------
    /**   盤面の表示フラグを設定する。
    **
    **  @param [in] scFlag    盤面表示フラグ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setShowFlag(
            const   ShowCoordFlags  scFlag);

//========================================================================
//
//    For Internal Use Only.
//
private:

    //----------------------------------------------------------------
    /**   入力したダイスの出目を、内部処理用に変換する。
    **
    **  @param [in] flgShow   現在の表示フラグ。
    **      この値に基づいて反転や回転の影響を除去する。
    **  @param [in] vCons   制約条件。
    **  @return     変換した値を返す。
    **/
    static  TConstraint
    convertConstraintCoord(
            const   ShowCoordFlags  flgShow,
            const   TConstraint     vCons);

    //----------------------------------------------------------------
    /**   指し手の内部形式を表示用データに変換する。
    **
    **  @param [in]     flgShow   現在の表示フラグ。
    **      この値に基づいて反転や回転も処理する。
    **  @param [in] actData   指し手データの内部形式。
    **  @param[out] pvAct     表示用データを書き込む領域。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    decodeActionData(
            const   ShowCoordFlags  flgShow,
            const   ActionData   &  actData,
            ActionView  *  const    pvAct);

    //----------------------------------------------------------------
    /**   指し手データの内、表示用座標を設定する。
    **
    **  @param [in]     flgShow   現在の表示フラグ。
    **      この値に基づいて反転や回転も処理する。
    **  @param[out] pvAct     表示用データを書き込む領域。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    setupActionDisplayCoord(
            const   ShowCoordFlags  flgShow,
            ActionView  *  const    pvAct);

//========================================================================
//
//    Member Variables.
//
protected:

    /**
    **    持ち駒を打つ時の番号変換表。
    **  持ち駒番号を、盤上の駒番号に変換する。
    **/
    static  const   Common::EFieldPiece
    s_tblHandConv[Common::NUM_HAND_TYPES];

private:

    /**   思考エンジンクラス。  **/
    typedef     Engine::EngineBase      TEngineBase;

private:

    /**   盤面の状態。  **/
    Game::BoardState    m_gcBoard;

    /**   棋譜データ。  **/
    ActionDataList      m_actList;

    /**   表示フラグ。  **/
    ShowCoordFlags      m_flgShow;

    /**   現在の手番。  **/
    PlayerIndex         m_curTurn;

    /**   現在の出目。  **/
    TConstraint         m_curDice;

    /**   実行の状態。  **/
    GameStateFlags      m_fStatus;

    /**   ゲーム勝敗。  **/
    GameResultVals      m_gResult;

    /**   エンジン。    **/
    TEngineBase  *      m_pEngine;

//========================================================================
//
//    Other Features.
//
private:
    typedef     GameController      This;
    GameController      (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   GameControllerTest;
};

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
