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
**      An Interface of BoardState class.
**
**      @file       Game/BoardState.h
**/

#if !defined( FAIRYSHOGI_GAME_INCLUDED_BOARD_STATE_H )
#    define   FAIRYSHOGI_GAME_INCLUDED_BOARD_STATE_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    "FairyShogi/Common/ViewBuffer.h"

#if !defined( FAIRYSHOGI_SYS_INCLUDED_STL_VECTOR )
#    include    <vector>
#    define     FAIRYSHOGI_SYS_INCLUDED_STL_VECTOR
#endif

FAIRYSHOGI_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Common  {
struct  ActionView;
}   //  End of namespace  Common

namespace  Game  {

//========================================================================
//
//    BoardState  class.
//
/**
**    盤面の状態を管理するクラス。
**/

class  BoardState
{

//========================================================================
//
//    Internal Types.
//
public:

    enum  {
        POS_NUM_ROWS    =  5,
        POS_NUM_COLS    =  5,
        FIELD_SIZE      =  POS_NUM_ROWS * POS_NUM_COLS
    };

    enum  {
        FIELD_EMPTY_SQUARE,

        FIELD_BLACK_PAWN,
        FIELD_BLACK_SILVER,
        FIELD_BLACK_GOLD,
        FIELD_BLACK_BISHOP,
        FIELD_BLACK_ROOK,
        FIELD_BLACK_KING,
        FIELD_BLACK_PR_PAWN,
        FIELD_BLACK_PR_SILVER,
        FIELD_BLACK_HORSE,
        FIELD_BLACK_DRAGON,

        FIELD_WHITE_PAWN,
        FIELD_WHITE_SILVER,
        FIELD_WHITE_GOLD,
        FIELD_WHITE_BISHOP,
        FIELD_WHITE_ROOK,
        FIELD_WHITE_KING,
        FIELD_WHITE_PR_PAWN,
        FIELD_WHITE_PR_SILVER,
        FIELD_WHITE_HORSE,
        FIELD_WHITE_DRAGON,

        NUM_FIELD_PIECE_TYPES
    };

    enum  {
        HAND_EMPTY_PIECE,

        HAND_BLACK_PAWN,
        HAND_BLACK_SILVER,
        HAND_BLACK_GOLD,
        HAND_BLACK_BISHOP,
        HAND_BLACK_ROOK,
        HAND_BLACK_KING,

        HAND_WHITE_PAWN,
        HAND_WHITE_SILVER,
        HAND_WHITE_GOLD,
        HAND_WHITE_BISHOP,
        HAND_WHITE_ROOK,
        HAND_WHITE_KING,

        NUM_HAND_TYPES
    };

    /**   盤面データの内部形式の型。    **/
    struct  InternState
    {
        PieceIndex  m_bsField[POS_NUM_ROWS * POS_NUM_COLS];
        THandCount  m_nHands [NUM_HAND_TYPES];
    };

    /**   指し手データの内部形式の型。  **/
    struct  ActionData
    {
        PosCol      xNewCol;
        PosRow      yNewRow;
        PosCol      xOldCol;
        PosRow      yOldRow;
        PieceIndex  fpCatch;        /**<  捕まえた駒。  **/
        PieceIndex  fpMoved;        /**<  移動した駒。  **/
        PieceIndex  fpAfter;        /**<  移動後成り。  **/
        PieceIndex  putHand;        /**<  打った駒。    **/
    };

    typedef     std::vector<ActionData>         ActionList;

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
    BoardState();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~BoardState();

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
    /**   指し手の内部形式を表示用データに変換する。
    **
    **  @param [in] actData   指し手データの内部形式。
    **  @param[out] actView   表示用データを書き込む領域。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    decodeActionData(
            const   ActionData   &  actData,
            Common::ActionView  *   actView);

    //----------------------------------------------------------------
    /**   駒を移動する指し手を内部形式に変換する。
    **
    **  @param [in] xOldCol   移動元の座標（横方向）。
    **  @param [in] yOldRow   移動元の座標（縦方向）。
    **  @param [in] xNewCol   移動先の座標（横方向）。
    **  @param [in] yNewRow   移動先の座標（縦方向）。
    **  @param [in] flgProm   駒の成り、不成り。
    **  @return     指し手の内部形式。
    **/
    const   ActionData
    encodeMoveAction(
            const  PosCol       xOldCol,
            const  PosRow       yOldRow,
            const  PosCol       xNewCol,
            const  PosRow       yNewRow,
            const  PieceIndex   flgProm)  const;

    //----------------------------------------------------------------
    /**   駒を移動する指し手を内部形式に変換する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] xOldCol   移動元の座標（横方向）。
    **  @param [in] yOldRow   移動元の座標（縦方向）。
    **  @param [in] xNewCol   移動先の座標（横方向）。
    **  @param [in] yNewRow   移動先の座標（縦方向）。
    **  @param [in] flgProm   駒の成り、不成り。
    **  @return     指し手の内部形式。
    **/
    static  const   ActionData
    encodeMoveAction(
            const  InternState  &curStat,
            const  PosCol       xOldCol,
            const  PosRow       yOldRow,
            const  PosCol       xNewCol,
            const  PosRow       yNewRow,
            const  PieceIndex   flgProm);

    //----------------------------------------------------------------
    /**   持ち駒を打つ指し手を内部形式に変換する。
    **
    **  @param [in] xPutCol   駒を打つ座標（横方向）。
    **  @param [in] yPutRow   駒を打つ座標（縦方向）。
    **  @param [in] pHand     打つ駒の種類。
    **  @return     指し手の内部形式。
    **/
    const   ActionData
    encodePutAction(
            const  PosCol       xPutCol,
            const  PosRow       yPutRow,
            const  PieceIndex   pHand)  const;

    //----------------------------------------------------------------
    /**   持ち駒を打つ指し手を内部形式に変換する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] xPutCol   駒を打つ座標（横方向）。
    **  @param [in] yPutRow   駒を打つ座標（縦方向）。
    **  @param [in] pHand     打つ駒の種類。
    **  @return     指し手の内部形式。
    **/
    static  const   ActionData
    encodePutAction(
            const  InternState  &curStat,
            const  PosCol       xPutCol,
            const  PosRow       yPutRow,
            const  PieceIndex   pHand);

    //----------------------------------------------------------------
    /**   合法手を列挙する。
    **
    **  @param [in] cPlayer   現在の手番のプレーヤーの番号。
    **  @param[out] actList   合法手のリストを受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    makeLegalActionList(
            const  PlayerIndex  cPlayer,
            ActionList          &actList)  const;

    //----------------------------------------------------------------
    /**   合法手を列挙する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] cPlayer   現在の手番のプレーヤーの番号。
    **  @param[out] actList   合法手のリストを受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    makeLegalActionList(
            const  InternState  &curStat,
            const  PlayerIndex  cPlayer,
            ActionList          &actList);

    //----------------------------------------------------------------
    /**   指定した指し手で盤面を進める。
    **
    **  @param [in] actFws    指し手データの内部形式。
    **  @retval     ERR_SUCCESS           合法手。
    **  @retval     ERR_ILLEGAL_ACTION    非合法。
    **/
    ErrCode
    playForward(
            const  ActionData   &actFwd);

    //----------------------------------------------------------------
    /**   盤面を初期状態に設定する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    resetGameBoard();

    //----------------------------------------------------------------
    /**   盤面を初期状態に設定する。
    **
    **  @param[out] pCurStat    盤面データを書き込む領域。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    resetGameBoard(
            InternState  *  pCurStat);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   現在の盤面を取得して、表示用バッファにコピーする。
    **
    **  @param[out] bufView   表示用バッファ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    copyToViewBuffer(
            Common::ViewBuffer  &bufView)  const;

    //----------------------------------------------------------------
    /**   現在の盤面を取得して、表示用バッファにコピーする。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param[out] bufView   表示用バッファ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    copyToViewBuffer(
            const  InternState  &curStat,
            Common::ViewBuffer  &bufView);

    //----------------------------------------------------------------
    /**   指定した座標にある駒を取得する。
    **
    **  @param [in] xCol      横方向の座標。
    **  @param [in] yRow      縦方向の座標。
    **  @return     指定した座標の駒番号を返す。
    **/
    PieceIndex
    getFieldPiece(
            const  PosCol   xCol,
            const  PosRow   yRow)  const;

    //----------------------------------------------------------------
    /**   指定した座標にある駒を取得する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] xCol      横方向の座標。
    **  @param [in] yRow      縦方向の座標。
    **  @return     指定した座標の駒番号を返す。
    **/
    static  PieceIndex
    getFieldPiece(
            const  InternState  &curStat,
            const  PosCol       xCol,
            const  PosRow       yRow);

//========================================================================
//
//    For Internal Use Only.
//
private:
    typedef     std::vector<FieldIndex>     TBitBoard;

private:

    static  ErrCode
    getAttackFromList(
            const  InternState  &curStat,
            const  FieldIndex   posTrg,
            const  PlayerIndex  offPlayer,
            TBitBoard           &bbFrom);

    //----------------------------------------------------------------
    /**   盤面の座標をインデックスに変換する。
    **
    **  @param [in] xCol    横方向の座標。
    **  @param [in] yRow    縦方向の座標。
    **  @return     座標に対応するインデックスを返す。
    **/
    static  inline  FieldIndex
    getMatrixPos(
            const   PosCol  xCol,
            const   PosRow  yRow);

//========================================================================
//
//    Member Variables.
//
private:

    /**   現在の盤面。  **/
    InternState     m_icState;

//========================================================================
//
//    Other Features.
//
private:

public:
    //  テストクラス。  //
    friend  class   BoardStateTest;
};

}   //  End of namespace  Game
FAIRYSHOGI_NAMESPACE_END

#endif
