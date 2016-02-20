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
**      An Implementation of Test Case 'RuleTables'.
**
**      @file       Game/Tests/RuleTablesTest.cpp
**/

#include    "TestDriver.h"

#include    "RuleTables.h"

FAIRYSHOGI_NAMESPACE_BEGIN
namespace  Game  {

//========================================================================
//
//    RuleTablesTest  class.
//
/**
**    クラス RuleTables の単体テスト。
**/

class  RuleTablesTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(RuleTablesTest);
    CPPUNIT_TEST(testExpandDirTable);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     OVERRIDE    { }
    virtual  void   tearDown()  OVERRIDE    { }

private:
    void  testExpandDirTable();
};

CPPUNIT_TEST_SUITE_REGISTRATION( RuleTablesTest );

//========================================================================
//
//    Tests.
//

void  RuleTablesTest::testExpandDirTable()
{
}

}   //  End of namespace  Game
FAIRYSHOGI_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}

