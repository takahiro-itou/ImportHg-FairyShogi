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
**      An Implementation of EngineProcess class.
**
**      @file       Bin/Win32/EngineProcess.cpp
**/

#include    "EngineProcess.h"

#include    <vector>

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Interface  {

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

EngineProcess::EngineProcess()
    : m_hStdInWrite(NULL),
      m_hStdOutRead(NULL),
      m_hStdErrRead(NULL),
      m_hConsoleIn (NULL),
      m_hConsoleOut(NULL),
      m_hConsoleErr(NULL),
      m_infProc()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

EngineProcess::~EngineProcess()
{
}

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

//----------------------------------------------------------------
//    標準エラー用のパイプを作成する。
//

ErrCode
EngineProcess::createStandardErrorPipe()
{
    HANDLE  hChildWrite,  hParentRead;

    hChildWrite = createWritePipe(&hParentRead);
    if ( hChildWrite == (NULL) ) {
        return ( ERR_FAILURE );
    }

    this->m_hConsoleErr = hChildWrite;
    this->m_hStdErrRead = hParentRead;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    標準入力用のパイプを作成する。
//

ErrCode
EngineProcess::createStandardInputPipe()
{
    HANDLE  hChildRead,  hParentWrite;

    hChildRead  = createReadPipe(&hParentWrite);
    if ( hChildRead == (NULL) ) {
        return ( ERR_FAILURE );
    }

    this->m_hConsoleIn  = hChildRead;
    this->m_hStdInWrite = hParentWrite;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    標準出力用のパイプを作成する。
//

ErrCode
EngineProcess::createStandardOutputPipe()
{
    HANDLE  hChildWrite,  hParentRead;

    hChildWrite = createWritePipe(&hParentRead);
    if ( hChildWrite == (NULL) ) {
        return ( ERR_FAILURE );
    }

    this->m_hConsoleOut = hChildWrite;
    this->m_hStdOutRead = hParentRead;

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    子プロセスを生成する。
//

HANDLE
EngineProcess::createProcess(
        const  std::string  &strCmd)
{
    const   size_t      lenCmd  = strCmd.length();
    std::vector<char>   bufCmd(lenCmd + 1);
    ::memcpy( &(bufCmd[0]), strCmd.c_str(), lenCmd );
    bufCmd[lenCmd]  = '\0';

    STARTUPINFO     si;
    ::memset( &si, 0, sizeof(si) );
    si.cb           = sizeof(si);
    si.hStdInput    = getStdHandle(this->m_hConsoleIn,  STD_INPUT_HANDLE);
    si.hStdOutput   = getStdHandle(this->m_hConsoleOut, STD_OUTPUT_HANDLE);
    si.hStdError    = getStdHandle(this->m_hConsoleErr, STD_ERROR_HANDLE);

    if ( ! ::CreateProcess(
                    NULL,   &(bufCmd[0]),
                    NULL,   NULL,
                    TRUE,
                    CREATE_NEW_PROCESS_GROUP,
                    NULL,   NULL,
                    &si,    &(this->m_infProc)) )
    {
        return ( NULL );
    }

    return ( (this->m_infProc.hProcess) );
}

//----------------------------------------------------------------
//    標準出力に書き込まれたデータのサイズを取得する。
//

FileLen
EngineProcess::peekConsoleOutput()  const
{
    DWORD   dwAvailSize = 0;
    if ( ! ::PeekNamedPipe(
                    (this->m_hStdOutRead), NULL, 0, NULL,
                    &dwAvailSize, NULL) )
    {
        return ( 0 );
    }
    return ( dwAvailSize );
}

//----------------------------------------------------------------
//    標準出力に書き込まれたデータを取得する。
//

FileLen
EngineProcess::readConsoleOutput(
        LpWriteBuf  const   ptrBuf,
        const   FileLen     cbSize)  const
{
    DWORD   dwRead  = 0;
    ::ReadFile(this->m_hStdOutRead, ptrBuf, cbSize, &dwRead, NULL);
    if ( dwRead < cbSize ) {
        *(static_cast<char *>(ptrBuf) + dwRead) = '\0';
    }
    return ( dwRead );
}

//----------------------------------------------------------------
//    標準出力に何かデータが書き込まれるのを待機する。
//

ErrCode
EngineProcess::waitConsoleOutput(
        HWND    hWnd,
        UINT    uiMsg,
        WPARAM  wParam,
        LPARAM  lParam)
{
    for (;;) {
        if ( peekConsoleOutput() > 0 ) {
            break;
        }
        ::Sleep(1000);
    }

    ::PostMessage(hWnd, uiMsg, wParam, lParam);
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    標準入力用のパイプにデータを送信する。
//

ErrCode
EngineProcess::writeConsoleInput(
        const   LpcReadBuf  ptrBuf,
        const   FileLen     cbSize)  const
{
    return ( ERR_FAILURE );
}

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

//----------------------------------------------------------------
//    パイプハンドルをペアで閉じる。
//

ErrCode
EngineProcess::closePipeHandles(
        HANDLE   &  hParent,
        HANDLE   &  hChild)
{
    if ( (hParent != NULL) && (hParent != INVALID_HANDLE_VALUE) )
    {
        ::CloseHandle(hParent);
    }
    hParent = (NULL);

    if ( (hChild != NULL) && (hChild != INVALID_HANDLE_VALUE) )
    {
        ::CloseHandle(hChild);
    }
    hChild  = (NULL);

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    子プロセスが読み込みを行うパイプを準備する。
//

HANDLE
EngineProcess::createReadPipe(
        HANDLE   *  hParentWrite)
{
    HANDLE  hTempPipe,  hReadPipe,  hWritePipe;

    //  パイプを作成する。  //
    const  HANDLE   hInstance   = ::GetCurrentProcess();
    if ( ! ::CreatePipe(&hTempPipe, &hWritePipe, NULL, 0) ) {
        return ( NULL );
    }

    //  作成したパイプの内、読み込み側を複製。  //
    //  子プロセスへの継承可能な権限を与える。  //
    if ( ! ::DuplicateHandle(
                    hInstance,  hTempPipe,
                    hInstance,  &hReadPipe,
                    0,  TRUE,   DUPLICATE_SAME_ACCESS) )
    {
        closePipeHandles(hWritePipe, hTempPipe);
        return ( NULL );
    }

    //  複製元のハンドルは使わないので閉じる。  //
    if ( ! ::CloseHandle(hTempPipe) ) {
        return ( NULL );
    }

    *(hParentWrite) = hWritePipe;
    return ( hReadPipe );
}

//----------------------------------------------------------------
//    子プロセスが書き込みを行うパイプを準備する。
//

HANDLE
EngineProcess::createWritePipe(
        HANDLE   *  hParentRead)
{
    HANDLE  hTempPipe,  hReadPipe,  hWritePipe;

    //  パイプを作成する。  //
    const  HANDLE   hInstance   = ::GetCurrentProcess();
    if ( ! ::CreatePipe(&hReadPipe, &hTempPipe, NULL, 0) ) {
        return ( NULL );
    }

    //  作成したパイプの内、読み込み側を複製。  //
    //  子プロセスへの継承可能な権限を与える。  //
    if ( ! ::DuplicateHandle(
                    hInstance,  hTempPipe,
                    hInstance,  &hWritePipe,
                    0,  TRUE,   DUPLICATE_SAME_ACCESS) )
    {
        closePipeHandles(hReadPipe, hTempPipe);
        return ( NULL );
    }

    //  複製元のハンドルは使わないので閉じる。  //
    if ( ! ::CloseHandle(hTempPipe) ) {
        return ( NULL );
    }

    *(hParentRead)  = hReadPipe;
    return ( hWritePipe );
}

//----------------------------------------------------------------
//    コンソール入出力用のハンドルを取得する。
//

HANDLE
EngineProcess::getStdHandle(
        const  HANDLE   hConsIO,
        const  DWORD    nStdIO)
{
    if ( (hConsIO != NULL) && (hConsIO != INVALID_HANDLE_VALUE) ) {
        return ( hConsIO );
    }
    return ( ::GetStdHandle(nStdIO) );
}

}   //  End of namespace  Interface
FAIRYSHOGI_NAMESPACE_END
