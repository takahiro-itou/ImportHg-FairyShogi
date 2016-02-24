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

#include    "FairyShogi/Game/BoardState.h"

#include    <iosfwd>
#include    <string>

#if !defined( FAIRYSHOGI_SYS_INCLUDED_STL_VECTOR )
#    include    <vector>
#    define     FAIRYSHOGI_SYS_INCLUDED_STL_VECTOR
#endif

FAIRYSHOGI_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Common  {
struct  ActionView;
}   //  End of namespace  Common

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
public:
    typedef     Game::BoardState::ActionData    ActionData;
    typedef     std::vector<ActionData>         ActionList;

    typedef     Common::ActionView              ActionView;
    typedef     std::vector<ActionView>         ActionViewList;

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
    /**   現在の局面の合法手を列挙する。
    **
    **  @param[out] actList   合法手のリストを受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    makeLegalActionList(
            ActionList  &actList)  const;

    //----------------------------------------------------------------
    /**   駒を移動する指し手を入力して盤面を進める。
    **
    **  @param [in] xOldCol   移動元の座標（横方向）。
    **  @param [in] yOldRow   移動元の座標（縦方向）。
    **  @param [in] xNewCol   移動先の座標（横方向）。
    **  @param [in] yNewRow   移動先の座標（縦方向）。
    **  @param [in] flgProm   駒の成り、不成り。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    playMoveAction(
            const  PosCol       xOldCol,
            const  PosRow       yOldRow,
            const  PosCol       xNewCol,
            const  PosRow       yNewRow,
            const  PieceIndex   flgProm);

    //----------------------------------------------------------------
    /**   持ち駒を打つ指し手を入力して盤面を進める。
    **
    **  @param [in] xPutCol   駒を打つ座標（横方向）。
    **  @param [in] yPutRow   駒を打つ座標（縦方向）。
    **  @param [in] pHand     打つ駒の種類。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    playPutAction(
            const  PosCol       xPutCol,
            const  PosRow       yPutRow,
            const  PieceIndex   pHand);

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
    /**   合法手の制約を指定する。
    **
    **  @param [in] vCons   制約条件。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setConstraint(
            const  int  vCons);

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
    startThinking(
            ActionData  &actRet);

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
            std::ostream        &outStr);

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
    ErrCode
    writeToViewBuffer(
            Common::ViewBuffer  &bufView)  const;

//========================================================================
//
//    Public Member Functions.
//

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

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    /**   盤面の状態。  **/
    Game::BoardState    m_gcBoard;

    /**   棋譜データ。  **/
    ActionList          m_actList;

    /**   現在の手番。  **/
    PlayerIndex         m_curTurn;

    /**   現在の出目。  **/
    int                 m_curDice;

//========================================================================
//
//    Other Features.
//
private:

public:
    //  テストクラス。  //
    friend  class   GameControllerTest;
};

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
