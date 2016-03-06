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

#include    "FairyShogi/Interface/GraphicalInterface.h"

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

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**
    **    現在の状態を管理する列挙型。
    **/
    enum  ScreenState
    {
        BSLS_NOTHING,

        /**
        **    成り選択画面の表示を要求。
        **/
        BSLS_SHOW_PROMOTION,
    };

    /**   ユーザーに示す成り駒選択肢の型。  **/
    typedef     std::vector<PieceIndex>     OptionArray;

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
public:

    //----------------------------------------------------------------
    /**   マスの選択をクリアする。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    clearSelection();

    //----------------------------------------------------------------
    /**   ユーザーが選択した成り駒を指定する。
    **
    **  @param [in] idxSel    ユーザーが選んだ選択肢の番号。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setPromotionOption(
            const  PieceIndex   idxSel);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   現在の状態を示すフラグを取得する。
    **
    **  @return     状態フラグを返す。
    **/
    ScreenState
    getCurrentState()  const;

    //----------------------------------------------------------------
    /**   成り駒の選択肢を取得する。
    **
    **  @return     成り駒を選択できる場合の選択肢を返す。
    **/
    const   OptionArray  &
    getPromotionList()  const;

//========================================================================
//
//    For Internal Use Only.
//
private:

    typedef     Common::ActionView                  ActionView;

    typedef     Interface::GraphicalInterface       GameInterface;
    typedef     GameInterface::PromoteList          PromoteList;


    /**   盤上のマスの座標を表す型。    **/
    typedef     int     BoardCoord;

private:

    static  CONSTEXPR_VAR   PieceIndex
    HANDS_BLACK_PAWN    =  Common::HAND_BLACK_PAWN;

    static  CONSTEXPR_VAR   PieceIndex
    HANDS_BLACK_KING    =  Common::HAND_BLACK_KING;

    static  CONSTEXPR_VAR   PieceIndex
    HANDS_WHITE_PAWN    =  Common::HAND_WHITE_PAWN;

    static  CONSTEXPR_VAR   PieceIndex
    HANDS_WHITE_KING    =  Common::HAND_WHITE_KING;

    /**
    **  @todo   ダミー定数。
    **      本来なら、ゲームクラスからもらってくる。
    **/
    static  CONSTEXPR_VAR   int
    POS_NUM_COLS        =  5;

    static  CONSTEXPR_VAR   int
    POS_NUM_ROWS        =  5;

    //  定数。  //
    static  CONSTEXPR_VAR   int
    LEFT_MARGIN         = 64;

    static  CONSTEXPR_VAR   int
    TOP_MARGIN          = 64;

    static  CONSTEXPR_VAR   int
    BOARD_TOP_OFFSET    = 1;

    static  CONSTEXPR_VAR   int
    BOARD_LEFT_OFFSET   = 0;

    static  CONSTEXPR_VAR   int
    SQUARE_WIDTH        = 64;

    static  CONSTEXPR_VAR   int
    SQUARE_HEIGHT       = 64;

    static  CONSTEXPR_VAR   int
    VIEW_NUM_COLS       = (POS_NUM_COLS);

    static  CONSTEXPR_VAR   int
    VIEW_NUM_ROWS       = (POS_NUM_ROWS) + 2;

    /**
    **    駒の移動方法。
    **/
    enum  DragDropMode
    {
        /**
        **    操作を開始していない状態。
        **/
        DDM_NOT_START,

        /**
        **    移動元を選択した状態。
        **/
        DDM_SELECT_SOURCE,

        /**
        **    移動元でマウスボタンを押し、
        **  押したままマウスを移動させ、
        **  移動先でマウスボタンを離す。
        **  すなわち、ドラッグドロップ方式。
        **/
        DDM_DRAG_AND_DROP,

        /**
        **    移動元をクリックし、その後移動先を二回クリックする。
        **/
        DDM_CLICKS
    };

private:

    //----------------------------------------------------------------
    /**   指定したマスに対してプレイを行う。
    **
    **  @param [in] srcX    移動元の水平座標。
    **  @param [in] srcY    移動先の垂直座標。
    **  @param [in] trgX    移動先の水平座標。
    **  @param [in] trgY    移動先の垂直座標。
    **  @param [in] iPrm    成り駒の選択。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    playAction(
            const  BoardCoord   srcX,
            const  BoardCoord   srcY,
            const  BoardCoord   trgX,
            const  BoardCoord   trgY,
            const  PieceIndex   iPrm);

    //----------------------------------------------------------------
    /**   移動先を指定して、移動可能性と成り駒選択肢を検査する。
    **
    **  @param [in] srcX    移動元の水平座標。
    **  @param [in] srcY    移動先の垂直座標。
    **  @param [in] trgX    移動先の水平座標。
    **  @param [in] trgY    移動先の垂直座標。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setActionInput(
            const  BoardCoord   srcX,
            const  BoardCoord   srcY,
            const  BoardCoord   trgX,
            const  BoardCoord   trgY);

    //----------------------------------------------------------------
    /**   移動元と移動先から、指し手データを構築する。
    **
    **  @note   引数の座標はいずれも升目座標のままで良い。
    **      マウスの座標を幅や高さで割った値。
    **      この関数内部で自動的に内部座標に変換する。
    **  @param [in] giCtrl    ゲームコントローラ。
    **  @param [in] srcX      移動元の水平座標。
    **  @param [in] srcY      移動先の垂直座標。
    **  @param [in] trgX      移動先の水平座標。
    **  @param [in] trgY      移動先の垂直座標。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    setupActionView(
            const  GameInterface  & giCtrl,
            const  BoardCoord       srcX,
            const  BoardCoord       srcY,
            const  BoardCoord       trgX,
            const  BoardCoord       trgY,
            PromoteList  *  const   vProms,
            ActionView   *  const   ptrAct);

//========================================================================
//
//    Member Variables.
//
private:

    /**   ゲームコントローラ。  **/
    GameInterface       m_gcGameCtrl;

    /**   現在のステータス。    **/
    ScreenState         m_bsState;

    /**   選択したマスの座標（水平方向）。  **/
    BoardCoord          m_bcSelX;

    /**   選択したマスの座標（垂直方向）。  **/
    BoardCoord          m_bcSelY;

    /**
    **    移動先として選択しているマスの座標（水平方向）。
    **  この値はマウスドラッグ時に、描画用に使う。
    **/
    BoardCoord          m_bcMovX;

    /**
    **    移動先として選択しているマスの座標（垂直方向）。
    **  この値はマウスドラッグ時に、描画用に使う。
    **/
    BoardCoord          m_bcMovY;

    /**
    **    移動元の座標（水平方向）。
    **
    **    成り駒をユーザーが選択している間、
    **  各種座標を保管しておくための変数。
    **/
    BoardCoord          m_bcSrcX;

    /**
    **    移動元の座標（垂直方向）。
    **
    **    成り駒をユーザーが選択している間、
    **  各種座標を保管しておくための変数。
    **/
    BoardCoord          m_bcSrcY;

    /**
    **    移動先の座標（水平方向）。
    **
    **    成り駒をユーザーが選択している間、
    **  各種座標を保管しておくための変数。
    **/
    BoardCoord          m_bcTrgX;

    /**
    **    移動先の座標（垂直方向）。
    **
    **    成り駒をユーザーが選択している間、
    **  各種座標を保管しておくための変数。
    **/
    BoardCoord          m_bcTrgY;

    /**   成り駒の選択肢。      **/
    OptionArray         m_prmOptions;

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
    /**   スーパークラス。  **/
    typedef     ScreenLayer     Super;

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
