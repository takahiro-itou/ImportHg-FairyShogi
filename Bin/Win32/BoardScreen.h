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
**      An Interface of BoardScreen class.
**
**      @file       Bin/Win32/BoardScreen.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_BOARD_SCREEN_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_BOARD_SCREEN_H

#include    "ScreenLayer.h"

#include    "FairyShogi/Interface/GameController.h"

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

#include    <fstream>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    BoardScreen  class.
//
/**
**    画面表示のレイヤーの内、メイン画面を管理するクラス。
**/

class  BoardScreen : public  ScreenLayer
{
private:

    /**   スーパークラス。  **/
    typedef     ScreenLayer     Super;

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
    BoardScreen();

    //----------------------------------------------------------------
    /**   インスタンスを指定したサイズで初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] wcLeft      左端座標。
    **  @param [in] wcTop       上端座標。
    **  @param [in] wcWidth     幅。
    **  @param [in] wcHeight    高さ。
    **/
    BoardScreen(
            const  WindowCoord  wcLeft,
            const  WindowCoord  wcTop,
            const  WindowCoord  wcWidth,
            const  WindowCoord  wcHeight);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~BoardScreen();

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//
public:

    //----------------------------------------------------------------
    /**   指定したビットマップイメージ上に内容を描画する。
    **
    **  @param [in,out] bmpTrg    描画対象のイメージ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    drawScreenLayer(
            BitmapImage  *  bmpTrg)  const  override;

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
    /**   マウスの左ボタンを押した時のイベントハンドラ。
    **
    **  @param [in] fwKeys
    **  @param [in] xPos
    **  @param [in] yPos
    **  @return     イベントハンドラの処理結果。
    **/
    virtual  EventResult
    onLButtonDown(
            const   DWORD   fwKeys,
            const   UINT    xPos,
            const   UINT    yPos);

    //----------------------------------------------------------------
    /**   マウスの左ボタンを離した時のイベントハンドラ。
    **
    **  @param [in] fwKeys
    **  @param [in] xPos
    **  @param [in] yPos
    **  @return     イベントハンドラの処理結果。
    **/
    virtual  EventResult
    onLButtonUp(
            const   DWORD   fwKeys,
            const   UINT    xPos,
            const   UINT    yPos);

    //----------------------------------------------------------------
    /**   マウスを移動させた時のイベントハンドラ。
    **
    **  @param [in] fwKeys
    **  @param [in] xPos
    **  @param [in] yPos
    **  @return     イベントハンドラの処理結果。
    **/
    virtual  EventResult
    onMouseMove(
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos);

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
    /**   必要な画像データを準備する。
    **
    **  @param [in] imgBack     盤の画像。
    **  @param [in] imgPiece    駒の画像。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setupBitmapImages(
            const  std::string  &imgBack,
            const  std::string  &imgPiece);

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

    static  constexpr   int
    HANDS_BLACK_PAWN    = Game::BoardState::HAND_BLACK_PAWN;

    static  constexpr   int
    HANDS_BLACK_KING    = Game::BoardState::HAND_BLACK_KING;

    static  constexpr   int
    HANDS_WHITE_PAWN    = Game::BoardState::HAND_WHITE_PAWN;

    static  constexpr   int
    HANDS_WHITE_KING    = Game::BoardState::HAND_WHITE_KING;

    /**
    **  @todo   ダミー定数。
    **      本来なら、ゲームクラスからもらってくる。
    **/
    static  constexpr   int     POS_NUM_COLS        =  5;
    static  constexpr   int     POS_NUM_ROWS        =  5;

    //  定数。  //
    static  constexpr   int     LEFT_MARGIN         = 64;
    static  constexpr   int     TOP_MARGIN          = 64;

    static  constexpr   int     BOARD_TOP_OFFSET    = 1;
    static  constexpr   int     BOARD_LEFT_OFFSET   = 0;

    static  constexpr   int     SQUARE_WIDTH        = 64;
    static  constexpr   int     SQUARE_HEIGHT       = 64;

    static  constexpr   int     VIEW_NUM_COLS       = (POS_NUM_COLS);
    static  constexpr   int     VIEW_NUM_ROWS       = (POS_NUM_ROWS) + 2;

    /**
    **    駒の移動方法。
    **/
    enum  DragDropMode
    {
        /**
        **    移動元をクリックし、その後移動先を二回クリックする。
        **/
        DDM_CLICKS,

        /**
        **    移動元でマウスボタンを押し、
        **  押したままマウスを移動させ、
        **  移動先でマウスボタンを離す。
        **  すなわち、ドラッグドロップ方式。
        **/
        DDM_DRAG_AND_DROP
    };

//========================================================================
//
//    Member Variables.
//
private:

    /**   ゲームコントローラ。  **/
    GameController      m_gcGameCtrl;

    /**   選択したマスの座標（水平方向）。  **/
    int                 m_scSelX;

    /**   選択したマスの座標（垂直方向）。  **/
    int                 m_scSelY;

    /**   移動先のマスの座標（水平方向）。  **/
    int                 m_scMovX;

    /**   移動先のマスの座標（垂直方向）。  **/
    int                 m_scMovY;

    /**   盤の画像イメージ。    **/
    BitmapImage  *      m_biBack;

    /**   駒の画像イメージ。    **/
    BitmapImage  *      m_biPiece;

    /**   @todo     暫定処理。後で消す。    **/
    std::ofstream       m_ofsKifu;

    /**   駒の移動方法の選択。  **/
    DragDropMode        m_ddMode;

//========================================================================
//
//    Other Features.
//
private:
    typedef     BoardScreen     This;
    BoardScreen         (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   BoardScreenTest;
};

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
