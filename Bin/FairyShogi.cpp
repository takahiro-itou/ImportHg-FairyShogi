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
#include    "FairyShogi/Common/ViewBuffer.h"
#include    "FairyShogi/Interface/GameController.h"

#include    <iostream>
#include    <limits>
#include    <stdlib.h>
#include    <cstring>
#include    <vector>

using   namespace   FAIRYSHOGI_NAMESPACE;

Interface::GameController   g_gcGameCtrl;

CONSTEXPR_VAR   const   char  *
g_tblPieceName[]    = {
    "  ",
    " P",  " S",  " G",  " B",  " R",  " K",
    "+P",  "+S",  "+B",  "+R",
    " p",  " s",  " g",  " b",  " r",  " k",
    "+p",  "+s",  "+b",  "+r"
};

CONSTEXPR_VAR   const   char  *
g_tblPieceName2[]   = {
    "W",
    "P",  "S",  "G",  "B",  "R",  "K",
    "+P", "+S", "+B", "+R",
    "p",  "s",  "g",  "b",  "r",  "k",
    "+p", "+s", "+b", "+r"
};

CONSTEXPR_VAR   const   char  *
g_tblSfenName[]     = {
    "1",
    "P",   "S",   "G",   "B",   "R",   "K",
    "+P",  "+S",  "+B",  "+R",
    "p",   "s",   "g",   "b",   "r",   "k",
    "+p",  "+s",  "+b",  "+r"
};

CONSTEXPR_VAR   const   char  *
g_tblHandName[]     = {
    "WALL",
    "P", "S", "G", "B", "R", "K",
    "p", "s", "g", "b", "r", "k"
};

CONSTEXPR_VAR   const   int
g_tblPromotion[]    = {
    0,
    Game::BoardState::FIELD_BLACK_PR_PAWN,
    Game::BoardState::FIELD_BLACK_PR_SILVER,
    Game::BoardState::FIELD_BLACK_GOLD,
    Game::BoardState::FIELD_BLACK_HORSE,
    Game::BoardState::FIELD_BLACK_DRAGON,
    Game::BoardState::FIELD_BLACK_KING,
    Game::BoardState::FIELD_BLACK_PR_PAWN,
    Game::BoardState::FIELD_BLACK_PR_SILVER,
    Game::BoardState::FIELD_BLACK_HORSE,
    Game::BoardState::FIELD_BLACK_DRAGON,

    Game::BoardState::FIELD_WHITE_PR_PAWN,
    Game::BoardState::FIELD_WHITE_PR_SILVER,
    Game::BoardState::FIELD_WHITE_GOLD,
    Game::BoardState::FIELD_WHITE_HORSE,
    Game::BoardState::FIELD_WHITE_DRAGON,
    Game::BoardState::FIELD_WHITE_KING,
    Game::BoardState::FIELD_WHITE_PR_PAWN,
    Game::BoardState::FIELD_WHITE_PR_SILVER,
    Game::BoardState::FIELD_WHITE_HORSE,
    Game::BoardState::FIELD_WHITE_DRAGON,
};

const
int
parseText(
        const   std::string         &strText,
        const   char  *             vSeps,
        const   int                 nMaxSep,
        std::vector< std::string >  &vTokens)
{
    const  size_t  lenText  = strText.length();
    std::vector<char>   chBuf(lenText + 1);
    char  *     ptrBuf  = &(chBuf[0]);

    ::memcpy( ptrBuf, strText.c_str(), lenText );
    chBuf[lenText]  = '\0';

    char  *     ptrTkn  = (nullptr);
    ////char  *     ptrSave = (nullptr);

    ////ptrTkn  = strtok_r(ptrBuf,  vSeps,  &ptrSave);
    ptrTkn  = strtok(ptrBuf,  vSeps);
    if ( ptrTkn == (nullptr) ) {
        return ( 0 );
    }
    vTokens.push_back(ptrTkn);

    for ( int i = 1; i < nMaxSep; ++ i ) {
        ////ptrTkn  = strtok_r(nullptr,  vSeps,  &ptrSave);
        ptrTkn  = strtok(nullptr,  vSeps);
        if ( ptrTkn == (nullptr) ) {
            break;
        }
        vTokens.push_back(ptrTkn);
    }

    ////ptrTkn  = strtok_r(nullptr,  "\n",  &ptrSave);
    ptrTkn  = strtok(nullptr,  "\n");
    if ( ptrTkn != (nullptr) ) {
        vTokens.push_back(ptrTkn);
    }

    return ( vTokens.size() );
}

int
setPosition(
        const  std::string         &strData,
        Interface::GameController  &itfGame)
{
    std::vector<std::string>    vTokens;

    vTokens.clear();
    vTokens.reserve(4);

    parseText(
            strData, " \t", 3, // std::numeric_limits<int>::max(),
            vTokens);
    if ( vTokens[0] == "startpos" ) {
        itfGame.resetGame();
        return ( 0 );
    }

    std::cerr   <<  "Invalid Position Format["  <<  strData  <<  "]"
                <<  std::endl;
    return ( 0 );
}

int
displaySfen(
        const  Interface::GameController  & itfGame,
        std::ostream                      & outStr)
{
    Common::ViewBuffer  vb;
    ::memset( &vb, 0, sizeof(vb) );
    itfGame.writeToViewBuffer(vb);

    //  盤面を表示する。    //
    for ( int y = 0; y < 5; ++ y ) {
        if ( y > 0 ) {
            outStr  <<  "/";
        }
        for ( int x = 0; x < 5; ++ x ) {
            const  int          pi  = (y * 5) + x;
            const  PieceIndex   dp  = vb.piBoard[pi];
            outStr  <<  g_tblSfenName[dp];
        }

    }

    /**     @todo   暫定処理。後で直す。    **/
    outStr  <<  " b ";

    //  持ち駒を表示する。  //
    int     flg = 0;
    for ( int c = 1; c < 12; ++ c ) {
        const  THandCount   numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }
        flg = 1;
        if ( numHand > 1 ) {
            outStr  <<  (numHand);
        }
        outStr  <<  g_tblHandName[c];
    }
    if ( flg == 0 ) {
        outStr  <<  "-";
    }

    outStr  <<  " 1\n";
    return ( 0 );

}

int
displayBoard(
        const  Interface::GameController  & itfGame,
        std::ostream                      & outStr)
{
    Common::ViewBuffer  vb;
    ::memset( &vb, 0, sizeof(vb) );
    itfGame.writeToViewBuffer(vb);

    //  盤面を表示する。    //
    outStr  <<  "| 5| 4| 3| 2| 1|\n";
    outStr  <<  "----------------\n";
    for ( int y = 0; y < 5; ++ y ) {
        for ( int x = 0; x < 5; ++ x ) {
            const  int          pi  = (y * 5) + x;
            const  PieceIndex   dp  = vb.piBoard[pi];
            outStr  <<  "|"  <<  g_tblPieceName[dp];
        }
        outStr  <<  "|"  <<  (y+1)  <<  "\n";
        outStr  <<  "----------------\n";
    }

    //  持ち駒を表示する。  //
    for ( int c = 1; c < 12; ++ c ) {
        if ( c == 1 ) {
            outStr  <<  "\nBLACK:";
        } else if ( c == 7 ) {
            outStr  <<  "\nWHITE:";
        }

        const  THandCount   numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }
        outStr  <<  g_tblHandName[c]
                <<  numHand
                <<  ", ";
    }

    outStr  <<  std::endl;
    return ( 0 );
}

int
playForward(
        const  std::string         &strPlay,
        Interface::GameController  &itfGame)
{
    int     nx, ny, ox, oy;
    int     pr  = 0;

    nx  =  strPlay[2] - '0';
    ny  =  strPlay[3] - '0';

    if ( (nx < 1) || (5 < nx) || (ny < 1) || (5 < ny) ) {
        std::cerr   <<  "Out of Range (Target)"
                    <<  std::endl;
        return ( 0 );
    }
    nx  = 5 - nx;
    --  ny;

    if ( strPlay[1] == '*' ) {
        //  持ち駒を打つ。  //
        int  h  = -1;
        for ( int ht = 0; ht < 13; ++ ht ) {
            if ( g_tblHandName[ht][0] == strPlay[0] ) {
                h   = ht;
                break;
            }
        }
        if ( h == -1 ) {
            std::cerr   <<  "Invalid Piece Name"    <<  strPlay
                        <<  std::endl;
            return ( 0 );
        }
        itfGame.playPutAction(nx, ny, h);

    } else {
        ox  =  strPlay[0] - '0';
        oy  =  strPlay[1] - '0';
        if ( (ox < 1) || (5 < ox) || (oy < 1) || (5 < oy) ) {
            std::cerr   <<  "Out of Range (Source)"
                        <<  std::endl;
            return ( 0 );
        }
        ox  =  5 - ox;
        --  oy;
        const  int  trg = itfGame.getBoardState().getFieldPiece(ox, oy);
        if ( (strPlay.length() >= 5) && (strPlay[4] == '+') ) {
            pr  = g_tblPromotion[trg];
        } else {
            pr  = trg;
        }
#if 0
        std::cerr   <<  "  NX = "   <<  nx
                    <<  ", NY = "   <<  ny
                    <<  ", OX = "   <<  ox
                    <<  ", OY = "   <<  oy
                    <<  ", PR = "   <<  pr
                    <<  std::endl;
#endif
        itfGame.playMoveAction(ox, oy, nx, ny, pr);
    }

    return ( 0 );
}

int
executeDiceCommand(
        const  std::string  &strArgs)
{
    return ( 0 );
}

int
executeListCommand(
        const  Interface::GameController  & itfGame,
        std::ostream                      & outStr)
{
    typedef     Interface::GameController::ActionList   ActionList;
    typedef     ActionList::const_iterator              ActIter;

    ActionList  vActs;
    itfGame.makeLegalActionList(vActs);

    const  ActIter  itrEnd  = vActs.end();
    int             cntDisp = 0;
    for ( ActIter itr = vActs.begin(); itr != itrEnd; ++ itr )
    {
        if ( itr->putHand == Game::BoardState::HAND_EMPTY_PIECE ) {
            outStr  <<  (itr->xOldCol + 1)  <<  (itr->yOldRow + 1)
                    <<  (itr->xNewCol + 1)  <<  (itr->yNewRow + 1)
                    <<  (g_tblPieceName2[itr->fpMoved]);
            if ( (itr->fpAfter) != (itr->fpMoved) ) {
                outStr  <<  '+';
            } else {
                outStr  <<  ' ';
            }
        } else {
            outStr  <<  (g_tblHandName[itr->putHand])
                    <<  '*'
                    <<  (itr->xNewCol + 1)  <<  (itr->yNewRow + 1)
                    <<  ' ';
        }
        outStr  <<  ", ";
        ++  cntDisp;
        if ( cntDisp >= 8 ) {
            outStr  <<  std::endl;
            cntDisp -=  8;
        }
    }

    outStr  <<  (vActs.size())  <<  "  Legal Actions."  <<  std::endl;
    return ( 0 );
}

int
parseConsoleInput(
        const  std::string  &strLine)
{
    std::vector<std::string>    vTokens;

    vTokens.clear();
    vTokens.reserve(2);

    parseText(
            strLine,  " \t",  1,  vTokens);

    if ( vTokens[0] == "go" ) {
    } else if ( vTokens[0] == "dice" ) {
        if ( vTokens.size() == 1 ) {
            std::cerr   <<  "Require Arguments."    <<  std::endl;
            return ( 0 );
        }
        return ( executeDiceCommand(vTokens[1]) );
    } else if ( vTokens[0] == "position" ) {
        if ( vTokens.size() == 1 ) {
            std::cerr   <<  "Require Arguments."    <<  std::endl;
            return ( 0 );
        }
        return  ( setPosition(vTokens[1], g_gcGameCtrl) );

    } else if ( vTokens[0] == "fwd" ) {
        return ( playForward(vTokens[1], g_gcGameCtrl) );
    } else if ( vTokens[0] == "sfen" ) {
        return ( displaySfen(g_gcGameCtrl, std::cout) );
    } else if ( vTokens[0] == "show" ) {
        return ( displayBoard(g_gcGameCtrl, std::cout) );
    } else if ( vTokens[0] == "list" ) {
        return ( executeListCommand(g_gcGameCtrl, std::cout) );
    }

    std::cerr   <<  "Invalid Command."  << std::endl;
    return ( 0 );
}

int  main(int argc, char * argv[])
{
    std::cerr   <<  "Fairy Shogi Version 0.0"
                <<  std::endl;

    std::string     strBuf;
    std::istream   & inStr  = (std::cin);

    g_gcGameCtrl.resetGame();

    for ( ;; ) {
        if ( ! inStr ) {
            break;
        }
        std::cerr   <<  ">";
        std::getline(inStr, strBuf);
        if ( strBuf == "exit" ) {
            break;
        }

        const  int  retVal  = parseConsoleInput(strBuf);
        if ( retVal != 0 ) {
            std::cerr   <<  "Command Failed."   <<  std::endl;
            //exit ( retVal );
        }
    }

    return ( 0 );
}
