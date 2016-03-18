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
        BOARD_SIZE      =  POS_NUM_ROWS * POS_NUM_COLS
    };

    enum  {
        BOARD_EMPTY_SQUARE,

        BOARD_BLACK_PAWN,
        BOARD_BLACK_SILVER,
        BOARD_BLACK_GOLD,
        BOARD_BLACK_BISHOP,
        BOARD_BLACK_ROOK,
        BOARD_BLACK_KING,
        BOARD_BLACK_PR_PAWN,
        BOARD_BLACK_PR_SILVER,
        BOARD_BLACK_PR_BISHOP,
        BOARD_BLACK_PR_ROOK,

        BOARD_WHITE_PAWN,
        BOARD_WHITE_SILVER,
        BOARD_WHITE_GOLD,
        BOARD_WHITE_BISHOP,
        BOARD_WHITE_ROOK,
        BOARD_WHITE_KING,
        BOARD_WHITE_PR_PAWN,
        BOARD_WHITE_PR_SILVER,
        BOARD_WHITE_PR_BISHOP,
        BOARD_WHITE_PR_ROOK,

        NUM_PIECE_TYPES
    };

    enum  {
        IHAND_EMPTY_PIECE,

        IHAND_BLACK_PAWN,
        IHAND_BLACK_SILVER,
        IHAND_BLACK_GOLD,
        IHAND_BLACK_BISHOP,
        IHAND_BLACK_ROOK,
        IHAND_BLACK_KING,

        IHAND_WHITE_PAWN,
        IHAND_WHITE_SILVER,
        IHAND_WHITE_GOLD,
        IHAND_WHITE_BISHOP,
        IHAND_WHITE_ROOK,
        IHAND_WHITE_KING,

        NUM_IHAND_TYPES
    };

    /**   盤面データの内部形式の型。    **/
    struct  InternState
    {
        PieceIndex  m_bsField[POS_NUM_ROWS * POS_NUM_COLS];
        THandCount  m_hcHands[NUM_IHAND_TYPES];
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
        PieceIndex  hpiDrop;        /**<  打った駒。    **/
        ActionFlag  fLegals;        /**<  合法手判定。  **/
    };

    typedef     std::vector<ActionData>         ActionList;
    typedef     std::vector<FieldIndex>         TBitBoard;

    typedef     Common::ActionView              ActionView;

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
    /**   指定した局面のクローンを作成する。
    **
    **  @param [in] objSrc    クローン元のインスタンス。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    cloneFrom(
            const  BoardState  &objSrc);

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
            ActionView  *  const    actView);

    //----------------------------------------------------------------
    /**   指定した座標にある駒を取得する。
    **
    **  @param [in] xCol      横方向の座標。
    **  @param [in] yRow      縦方向の座標。
    **  @return     指定した座標の駒番号を返す。
    **/
    Common::EFieldPiece
    decodeFieldPiece(
            const  PosCol   xCol,
            const  PosRow   yRow)  const;

    //----------------------------------------------------------------
    /**   指し手の表示用形式を内部形式に変換する。
    **
    **  @param [in] actView   指し手データの表示用形式。
    **  @param[out] actData   内部形式のデータを書き込む領域。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    encodeActionData(
            const   ActionView   &  actView,
            ActionData  *  const    actData);

    //----------------------------------------------------------------
    /**   表示用バッファから内部形式に変換する。
    **
    **  @param [in] bufView   表示用バッファ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    encodeFromViewBuffer(
            const  Common::ViewBuffer  &bufView);

    //----------------------------------------------------------------
    /**   表示用バッファから内部形式に変換する。
    **
    **  @param [in] bufView   表示用バッファ。
    **  @param[out] curStat   内部形式を書き込む変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    encodeFromViewBuffer(
            const  Common::ViewBuffer  &bufView,
            InternState                &curStat);

    //----------------------------------------------------------------
    /**   現在の局面がチェックメイトかどうかを判定する。
    **
    **  @param [in] dPlayer   判定を行うプレーヤー。
    **  @retval     BOOL_TRUE   : チェックメイト。
    **  @retval     BOOL_FALSE  : それ以外。
    **/
    Boolean
    isCheckMateState(
            const  PlayerIndex  dPlayer)  const;

    //----------------------------------------------------------------
    /**   現在の局面がチェックメイトかどうかを判定する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] dPlayer   判定を行うプレーヤー。
    **  @retval     BOOL_TRUE   : チェックメイト。
    **  @retval     BOOL_FALSE  : それ以外。
    **/
    static  Boolean
    isCheckMateState(
            const  InternState  &curStat,
            const  PlayerIndex  dPlayer);

    //----------------------------------------------------------------
    /**   王手が掛かっているかどうかを判定する。
    **
    **  @param [in] dPlayer   判定を行うプレーヤー。
    **  @param[out] bbFrom    王手を掛けている攻撃側の駒の場所。
    **  @return     王手を掛けている攻撃側の駒の枚数を返す。
    **/
    size_t
    isCheckState(
            const  PlayerIndex  dPlayer,
            TBitBoard           &bbFrom)  const;

    //----------------------------------------------------------------
    /**   王手が掛かっているかどうかを判定する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] dPlayer   判定を行うプレーヤー。
    **  @param[out] bbFrom    王手を掛けている攻撃側の駒の場所。
    **  @return     王手を掛けている攻撃側の駒の枚数を返す。
    **/
    static  size_t
    isCheckState(
            const  InternState  &curStat,
            const  PlayerIndex  dPlayer,
            TBitBoard           &bbFrom);

    //----------------------------------------------------------------
    /**   合法手を列挙する。
    **
    **  @param [in] cPlayer   現在の手番のプレーヤーの番号。
    **  @param [in] fLegals   合法判定フラグ。
    **      このフラグで指定した非合法手も列挙する。
    **      ゼロを指定すると合法手のみ列挙する。
    **  @param[out] actList   合法手のリストを受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    makeLegalActionList(
            const  PlayerIndex  cPlayer,
            const  ActionFlag   fLegals,
            ActionList          &actList)  const;

    //----------------------------------------------------------------
    /**   合法手を列挙する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] cPlayer   現在の手番のプレーヤーの番号。
    **  @param [in] fLegals   合法判定フラグ。
    **      このフラグで指定した非合法手も列挙する。
    **      ゼロを指定すると合法手のみ列挙する。
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
            const  ActionFlag   fLegals,
            ActionList          &actList);

    //----------------------------------------------------------------
    /**   指定した指し手で盤面を戻す。
    **
    **  @param [in] actBwd    指し手データの内部形式。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    playBackward(
            const  ActionData   &actBwd);

    //----------------------------------------------------------------
    /**   指定した指し手で盤面を戻す。
    **
    **  @param [in]     actBwd    指し手データの内部形式。
    **  @param [in,out] curStat   現在の盤面データ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    playBackward(
            const  ActionData   &actBwd,
            InternState         &curStat);

    //----------------------------------------------------------------
    /**   指定した指し手で盤面を進める。
    **
    **  @param [in] actFwd    指し手データの内部形式。
    **  @retval     ERR_SUCCESS           合法手。
    **  @retval     ERR_ILLEGAL_ACTION    非合法。
    **/
    ErrCode
    playForward(
            const  ActionData   &actFwd);

    //----------------------------------------------------------------
    /**   指定した指し手で盤面を進める。
    **
    **  @param [in]     actFwd    指し手データの内部形式。
    **  @param [in,out] curStat   現在の盤面データ。
    **  @retval     ERR_SUCCESS           合法手。
    **  @retval     ERR_ILLEGAL_ACTION    非合法。
    **/
    static  ErrCode
    playForward(
            const  ActionData   &actFwd,
            InternState         &curStat);

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
    /**   現在の盤面データの内部形式のクローンを作成する。
    **
    **  @param[out] stClone   クローンデータを受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    cloneInternState(
            InternState  *  stClone)  const;

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
