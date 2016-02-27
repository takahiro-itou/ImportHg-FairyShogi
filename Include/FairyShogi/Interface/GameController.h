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
            ActionDataList  &actList)  const;

    //----------------------------------------------------------------
    /**   現在の局面の合法手を列挙する。
    **
    **  @param [in] fLegals   合法判定フラグ。
    **      このフラグで指定した非合法手も列挙する。
    **      ゼロを指定すると合法手のみ列挙する。
    **  @param [in] vCons     制約条件を指定する。
    **      負の数を指定すると現在の条件を使う。
    **  @param[out] actList   合法手のリストを受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    makeLegalActionList(
            const   ActionFlag  fLegals,
            const   int         vCons,
            ActionViewList      &actList)  const;

    //----------------------------------------------------------------
    /**   指定した入力文字列を、指し手データに変換する。
    **
    **  @param [in] strPlay   指し手入力文字列。
    **  @param[out] ptrAct    変換した結果を受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    parseActionText(
            const  std::string  &strPlay,
            ActionView  *       ptrAct)  const;

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
    /**   合法手の制約を取得する。
    **
    **  @return     制約条件を返す。
    **/
    virtual  int
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
            ActionView  &actRet);

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
    /**   入力した座標を内部処理用に変換する。
    **
    **  @param [in]     flgShow   現在の表示フラグ。
    **      この値に基づいて反転や回転の影響を除去する。
    **  @param [in,out] ptrCol    座標（横方向）。
    **  @param [in,out] ptrRow    座標（縦方向）。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    convertCoordsFromConsole(
            const   ShowCoordFlags  flgShow,
            PosCol  *   const       ptrCol,
            PosRow  *   const       ptrRow);

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

//========================================================================
//
//    Member Variables.
//
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
