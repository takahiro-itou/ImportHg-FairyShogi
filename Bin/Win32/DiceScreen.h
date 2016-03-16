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
**      An Interface of DiceScreen class.
**
**      @file       Bin/Win32/DiceScreen.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_DICE_SCREEN_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_DICE_SCREEN_H

#include    "ChoiceScreen.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    DiceScreen  class.
//
/**
**    ダイス画面を管理するクラス。
**/

class  DiceScreen : public  ChoiceScreen
{

public:

    enum  {
        /**
        **    乱数を使う場合に指定する番号。
        **/
        DICE_USE_RANDOM     =  12,

        /**
        **    乱数のシードを設定する場合に指定する番号。
        **/
        DICE_SET_SEED       =  13,

        /**
        **    元に戻すボタンの番号。
        **/
        DICE_BACK_COMMAND   =  14
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
    DiceScreen();

    //----------------------------------------------------------------
    /**   インスタンスを指定したサイズで初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] wcLeft      左端座標。
    **  @param [in] wcTop       上端座標。
    **  @param [in] wcWidth     幅。
    **  @param [in] wcHeight    高さ。
    **/
    DiceScreen(
            const  WindowCoord  wcLeft,
            const  WindowCoord  wcTop,
            const  WindowCoord  wcWidth,
            const  WindowCoord  wcHeight);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~DiceScreen();

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
    /**   必要な画像データを準備する。
    **
    **  @param [in] imgDice   ダイスの画像。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setupBitmapImages(
            const  std::string  &imgDice);

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
    /**   ユーザーが選択したインデックスを取得する。
    **
    **  @return     ユーザーの選択した番号を返す。
    **/
    ChoiceIndex
    getUserSelect()  const;

    //----------------------------------------------------------------
    /**   ユーザーに示す選択肢を設定する。
    **
    **  @param [in] ciTurn    現在のプレーヤー。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setSelectionList(
            const  PlayerIndex  piTurn);

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
    typedef     ChoiceScreen    Super;

private:
    typedef     DiceScreen      This;
    DiceScreen          (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   DiceScreenTest;
};

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
