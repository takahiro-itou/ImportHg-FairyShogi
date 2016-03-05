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
**      アプリケーション本体。
**
**      @file       Bin/FairyShogi.cpp
**/

#include    "CommandInterpreter.h"

#include    "FairyShogi/Common/FairyShogiTypes.h"
#include    "FairyShogi/Common/ActionView.h"
#include    "FairyShogi/Common/ViewBuffer.h"
#include    "FairyShogi/Interface/ConsoleInterface.h"

#include    <iostream>
#include    <limits>
#include    <cstdlib>
#include    <cstring>
#include    <fstream>
#include    <time.h>
#include    <vector>

using   namespace   FAIRYSHOGI_NAMESPACE;

Interface::CommandInterpreter   g_ciGameCtrl;

int  main(int argc, char * argv[])
{
    std::cerr   <<  "Fairy Shogi Version 0.0"
                <<  std::endl;

    std::string     strBuf;
    ErrCode         retErr;

    std::istream   & inStr  = (std::cin);

    for ( ;; ) {
        if ( ! inStr ) {
            break;
        }
        std::cerr   <<  ">";
        std::getline(inStr, strBuf);

        if ( strBuf.empty() ) {
            continue;
        }
        if ( strBuf[0] == '#' ) {
            //  コメント行は無視する。  //
            continue;
        }
        if ( strBuf == "quit" ) {
            //  終了コマンドを処理。    //
            break;
        }

        retErr  =  g_ciGameCtrl.interpretConsoleInput(strBuf,  std::cout);
        if ( retErr != ERR_SUCCESS ) {
            std::cerr   <<  "\nCommand Failed"  <<  std::endl;
        }

    }

    return ( 0 );
}
