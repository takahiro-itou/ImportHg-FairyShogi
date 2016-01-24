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

#include    "FairyShogi/Interface/ViewBuffer.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  GAME  {

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
//    Public Member Functions.
//
public:

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
            const  PosRow       yPosRow,
            const  PieceIndex   pHand)  const;

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
            INTERFACE::ViewBuffer  &bufView)  const;

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

public:
    //  テストクラス。  //
    friend  class   BoardStateTest;
};

}   //  End of namespace  GAME
FAIRYSHOGI_NAMESPACE_END

#endif
