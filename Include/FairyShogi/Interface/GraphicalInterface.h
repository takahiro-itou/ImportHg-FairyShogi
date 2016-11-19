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
**      An Interface of GraphicalInterface class.
**
**      @file       Interface/GraphicalInterface.h
**/

#if !defined( FAIRYSHOGI_INTERFACE_INCLUDED_GRAPHICAL_INTERFACE_H )
#    define   FAIRYSHOGI_INTERFACE_INCLUDED_GRAPHICAL_INTERFACE_H

#include    "FairyShogi/Interface/ConsoleInterface.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    GraphicalInterface  class.
//
/**
**    グラフィカル版のゲーム管理クラス。
**/

class  GraphicalInterface : public  ConsoleInterface
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
    GraphicalInterface();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~GraphicalInterface();

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
    /**   指定したマウス入力を、指し手データに変換する。
    **
    **  @note   この時点では成り不成りが未定でも良い。
    **      移動先で成れる駒のリストが引数に返される。
    **  @param [in] xOldCol   移動元の座標（横方向）。
    **  @param [in] yOldRow   移動元の座標（縦方向）。
    **  @param [in] xNewCol   移動先の座標（横方向）。
    **  @param [in] yNewRow   移動先の座標（縦方向）。
    **  @param[out] vProms    移動先で成れる駒のリスト。
    **  @param[out] ptrAct    変換した結果を受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setupMoveActionFromMouse(
            const  FileCol      xOldCol,
            const  RankRow      yOldRow,
            const  FileCol      xNewCol,
            const  RankRow      yNewRow,
            PromoteList  *      vProms,
            ActionView   *      ptrAct)  const;

    //----------------------------------------------------------------
    /**   指定したマウス入力を、指し手データに変換する。
    **
    **  @param [in] xPutCol   駒を打つ座標（横方向）。
    **  @param [in] yPutRow   駒を打つ座標（縦方向）。
    **  @param [in] pHand     打つ駒の種類。
    **  @param[out] vProms    移動先で成れる駒のリスト。
    **      駒を打つ場合は、成った状態では打てないが、
    **      変則ルールに対応するために、念のため準備。
    **  @param[out] ptrAct    変換した結果を受け取る変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setupPutActionFromMouse(
            const  FileCol      xPutCol,
            const  RankRow      yPutRow,
            const  PieceIndex   pHand,
            PromoteList  *      vProms,
            ActionView   *      ptrAct)  const;

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

    //----------------------------------------------------------------
    /**   入力した座標を内部処理用に変換する。
    **
    **  @param [in] flgShow   現在の表示フラグ。
    **      この値に基づいて反転や回転の影響を除去する。
    **  @param [in] xInCol    座標（横方向）。ゼロベース。
    **  @param [in] yInRow    座標（縦方向）。ゼロベース。
    **  @param[out] ptrCol    座標（横方向）。
    **  @param[out] ptrRow    座標（縦方向）。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    convertCoordsFromMouse(
            const   ShowCoordFlags  flgShow,
            const   FileCol         xInCol,
            const   RankRow         yInRow,
            FileCol  *  const       ptrCol,
            RankRow  *  const       ptrRow);

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
    typedef     ConsoleInterface        Super;

private:
    typedef     GraphicalInterface      This;
    GraphicalInterface  (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   GraphicalInterfaceTest;
};

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
