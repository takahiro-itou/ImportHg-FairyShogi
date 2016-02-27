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
**      An Interface of ConsoleInterface class.
**
**      @file       Interface/ConsoleInterface.h
**/

#if !defined( FAIRYSHOGI_INTERFACE_INCLUDED_CONSOLE_INTERFACE_H )
#    define   FAIRYSHOGI_INTERFACE_INCLUDED_CONSOLE_INTERFACE_H

#include    "FairyShogi/Interface/GameController.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    ConsoleInterface  class.
//
/**
**    コンソール版のゲーム管理クラス。
**/

class  ConsoleInterface : public  GameController
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
    ConsoleInterface();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ConsoleInterface();

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
    typedef     GameController      Super;

public:
    //  テストクラス。  //
    friend  class   ConsoleInterfaceTest;
};

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
