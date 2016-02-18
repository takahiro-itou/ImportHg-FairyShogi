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
**      An Interface of EngineProcess class.
**
**      @file       Bin/Win32/EngineProcess.h
**/

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_ENGINE_PROCESS_H )
#    define   FAIRYSHOGI_WIN32_INCLUDED_ENGINE_PROCESS_H

#include    "FairyShogi/Common/FairyShogiTypes.h"

#if !defined( FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     FAIRYSHOGI_WIN32_INCLUDED_SYS_WINDOWS_H
#endif

#include    <string>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    EngineProcess  class.
//
/**
**    思考エンジンのプロセスを管理する。
**/

class  EngineProcess
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
    EngineProcess();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~EngineProcess();

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
    /**   標準エラー用のパイプを作成する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    createStandardErrorPipe();

    //----------------------------------------------------------------
    /**   標準入力用のパイプを作成する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    createStandardInputPipe();

    //----------------------------------------------------------------
    /**   標準出力用のパイプを作成する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    createStandardOutputPipe();

    //----------------------------------------------------------------
    /**   子プロセスを生成する。
    **
    **  @param [in] strCmd   起動するプログラムの名前と引数。
    **  @return     起動された子プロセスのハンドル。
    **/
    virtual  HANDLE
    createProcess(
            const  std::string  &strCmd);

    //----------------------------------------------------------------
    /**   標準出力に書き込まれたデータのサイズを取得する。
    **
    **  @return     パイプのバッファ上にあるデータのサイズ。
    **      パイプのバッファが空の場合は、直ちにゼロを返す。
    **/
    virtual  FileLen
    peekConsoleOutput()  const;

    //----------------------------------------------------------------
    /**   標準出力に書き込まれたデータを取得する。
    **
    **  @param[out] ptrBuf    データを受け取るバッファ。
    **  @param [in] cbSize    バッファのサイズ。
    **  @return     バッファにコピーされたバイト数を返す。
    **/
    virtual  FileLen
    readConsoleOutput(
            LpWriteBuf  const   ptrBuf,
            const   FileLen     cbSize)  const;

    //----------------------------------------------------------------
    /**   標準出力に何かデータが書き込まれるのを待機する。
    **
    **  @note       データが書き込まれると、
    **      引数で指定された内容でメッセージを送信する。
    **  @param [in] hWnd      メッセージを受け取るウィンドウ。
    **  @param [in] uiMsg     メッセージコード。
    **  @param [in] wParam    メッセージのパラメータ。
    **  @param [in] lParam    メッセージのパラメータ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    waitConsoleOutput(
            HWND    hWnd,
            UINT    uiMsg,
            WPARAM  wParam,
            LPARAM  lParam);

    //----------------------------------------------------------------
    /**   標準入力用のパイプにデータを送信する。
    **
    **  @param [in] ptrBuf    送信するデータ。
    **  @param [in] cbSize    データのサイズ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    writeConsoleInput(
            const   LpcReadBuf  ptrBuf,
            const   FileLen     cbSize)  const;

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
    /**   パイプハンドルをペアで閉じる。
    **
    **  @param [in,out] hParent   親プロセス側のハンドル。
    **  @param [in,out] hChild    子プロセス側のハンドル。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    closePipeHandles(
            HANDLE   &  hParent,
            HANDLE   &  hChild);

    //----------------------------------------------------------------
    /**   子プロセスが読み込みを行うパイプを準備する。
    **
    **  @param [out]    hParentWrite    ハンドルを受け取る変数。
    **      パイプに親側から書き込む為のハンドルが書き込まれる。
    **  @return     パイプの（子が使う側の）ハンドルを返す。
    **/
    static  HANDLE
    createReadPipe(
            HANDLE   *  hParentWrite);

    //----------------------------------------------------------------
    /**   子プロセスが書き込みを行うパイプを準備する。
    **
    **  @param [out]    hParentRead     ハンドルを受け取る変数。
    **      パイプに親側から読み込む為のハンドルが書き込まれる。
    **  @return     パイプの（子が使う側の）ハンドルを返す。
    **/
    static  HANDLE
    createWritePipe(
            HANDLE   *  hParentRead);

//========================================================================
//
//    Member Variables.
//
private:
    typedef     PROCESS_INFORMATION     ProcInfo;

private:

    HANDLE      m_hStdInWrite;
    HANDLE      m_hStdOutRead;
    HANDLE      m_hStdErrRead;

    HANDLE      m_hConsoleIn;
    HANDLE      m_hConsoleOut;
    HANDLE      m_hConsoleErr;

    ProcInfo    m_infProc;

//========================================================================
//
//    Other Features.
//
private:
    typedef     EngineProcess       This;
    EngineProcess       (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   EngineProcessTest;
};

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END

#endif
