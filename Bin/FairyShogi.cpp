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

#include    "FairyShogi/Common/FairyShogiTypes.h"

#include    <iostream>

using   namespace   FAIRYSHOGI_NAMESPACE;

int  main(int argc, char * argv[])
{
    std::cerr   <<  "Fairy Shogi Version 0.0"
                <<  std::endl;

    std::string     strBuf;
    std::istream   & inStr  = (std::cin);

    std::getline(inStr, strBuf);
    std::cerr   <<  strBuf  <<  std::endl;

    std::cout   <<  "ECHO :"
                <<  strBuf  <<  std::endl;

    return ( 0 );
}
