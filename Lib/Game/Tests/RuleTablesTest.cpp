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
    CPPUNIT_TEST(testExpandDirTable01);
    CPPUNIT_TEST(testExpandDirTable02);
    CPPUNIT_TEST(testExpandDirTable03);
    CPPUNIT_TEST(testExpandDirTable04);
    CPPUNIT_TEST(testExpandDirTable05);
    CPPUNIT_TEST(testExpandDirTable06);
    CPPUNIT_TEST(testExpandDirTable07);
    CPPUNIT_TEST(testExpandDirTable08);
    CPPUNIT_TEST(testExpandDirTable09);
    CPPUNIT_TEST(testExpandDirTable10);
    CPPUNIT_TEST(testExpandDirTable11);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     OVERRIDE    { }
    virtual  void   tearDown()  OVERRIDE    { }

private:
    void  testExpandDirTable01();
    void  testExpandDirTable02();
    void  testExpandDirTable03();
    void  testExpandDirTable04();
    void  testExpandDirTable05();
    void  testExpandDirTable06();
    void  testExpandDirTable07();
    void  testExpandDirTable08();
    void  testExpandDirTable09();
    void  testExpandDirTable10();
    void  testExpandDirTable11();

    static  int
    checkExpandResult(
            const  uint32_t  (& tblExp)[25],
            const  uint32_t  (& tblAct)[25]);

};

CPPUNIT_TEST_SUITE_REGISTRATION( RuleTablesTest );

//========================================================================
//
//    Tests.
//

//  テスト用テーブル。  //
namespace  {

const  int  g_tblDir00[9]   = {  0,  0,  0,  0,  0,  0,  0,  0,  0 };

const  int  g_tblDir01[9]   = { -1,  0,  0,  0,  0,  0,  0,  0,  0 };
const  int  g_tblDir02[9]   = { +1,  0,  0,  0,  0,  0,  0,  0,  0 };

const  int  g_tblDir03[9]   = { +8, +6, -1, -6, -8,  0,  0,  0,  0 };
const  int  g_tblDir04[9]   = { +8, +6, +1, -6, -8,  0,  0,  0,  0 };

const  int  g_tblDir05[9]   = { +7, +6, +1, -1, -7, -8,  0,  0,  0 };
const  int  g_tblDir06[9]   = { +8, +7, +1, -1, -6, -7,  0,  0,  0 };

const  int  g_tblDir07[9]   = { +8, +7, +6, +1, -1, -6, -7, -8,  0 };

const  int  g_tblDir08[9]   = { +8, +6, -6, -8,  0,  0,  0,  0,  0 };
const  int  g_tblDir09[9]   = { +7, +1, -1, -7,  0,  0,  0,  0,  0 };


const  uint32_t     g_tblPos01[25]  = {
    0x00000000, 0x00000001, 0x00000002, 0x00000004, 0x00000008,
    0x00000000, 0x00000020, 0x00000040, 0x00000080, 0x00000100,
    0x00000000, 0x00000400, 0x00000800, 0x00001000, 0x00002000,
    0x00000000, 0x00008000, 0x00010000, 0x00020000, 0x00040000,
    0x00000000, 0x00100000, 0x00200000, 0x00400000, 0x00800000
};

const  uint32_t     g_tblPos02[25]  = {
    0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000000,
    0x00000040, 0x00000080, 0x00000100, 0x00000200, 0x00000000,
    0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00000000,
    0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00000000,
    0x00200000, 0x00400000, 0x00800000, 0x01000000, 0x00000000
};

const  uint32_t     g_tblPos03[25]  = {
    0x00000040, 0x000000A1, 0x00000142, 0x00000284, 0x00000108,
    0x00000802, 0x00001425, 0x0000284A, 0x00005094, 0x00002108,
    0x00010040, 0x000284A0, 0x00050940, 0x000A1280, 0x00042100,
    0x00200800, 0x00509400, 0x00A12800, 0x01425000, 0x00842000,
    0x00010000, 0x00128000, 0x00250000, 0x004A0000, 0x00840000
};

const  uint32_t     g_tblPos04[25]  = {
    0x00000042, 0x000000A4, 0x00000148, 0x00000290, 0x00000100,
    0x00000842, 0x00001485, 0x0000290A, 0x00005214, 0x00002008,
    0x00010840, 0x000290A0, 0x00052140, 0x000A4280, 0x00040100,
    0x00210800, 0x00521400, 0x00A42800, 0x01485000, 0x00802000,
    0x00210000, 0x00428000, 0x00850000, 0x010A0000, 0x00040000
};

const  uint32_t     g_tblPos05[25]  = {
    0x00000022, 0x00000065, 0x000000CA, 0x00000194, 0x00000308,
    0x00000441, 0x00000CA3, 0x00001946, 0x0000328C, 0x00006118,
    0x00008820, 0x00019460, 0x000328C0, 0x00065180, 0x000C2300,
    0x00110400, 0x00328C00, 0x00651800, 0x00CA3000, 0x01846000,
    0x00208000, 0x00518000, 0x00A30000, 0x01460000, 0x008C0000
};

const  uint32_t     g_tblPos06[25]  = {
    0x00000062, 0x000000C5, 0x0000018A, 0x00000314, 0x00000208,
    0x00000C43, 0x000018A6, 0x0000314C, 0x00006298, 0x00004110,
    0x00018860, 0x000314C0, 0x00062980, 0x000C5300, 0x00082200,
    0x00310C00, 0x00629800, 0x00C53000, 0x018A6000, 0x01044000,
    0x00218000, 0x00530000, 0x00A60000, 0x014C0000, 0x00880000
};

const  uint32_t     g_tblPos07[25]  = {
    0x00000062, 0x000000E5, 0x000001CA, 0x00000394, 0x00000308,
    0x00000C43, 0x00001CA7, 0x0000394E, 0x0000729C, 0x00006118,
    0x00018860, 0x000394E0, 0x000729C0, 0x000E5380, 0x000C2300,
    0x00310C00, 0x00729C00, 0x00E53800, 0x01CA7000, 0x01846000,
    0x00218000, 0x00538000, 0x00A70000, 0x014E0000, 0x008C0000
};

const  uint32_t     g_tblPos08[25]  = {
    0x01041040, 0x000820A0, 0x00004540, 0x00008A80, 0x00111100,
    0x00820802, 0x01041405, 0x0008A80A, 0x00115014, 0x00222008,
    0x00410044, 0x008280A8, 0x01150151, 0x002A0282, 0x00440104,
    0x00200888, 0x00501510, 0x00A02A20, 0x01405041, 0x00802082,
    0x00011110, 0x0002A200, 0x00054400, 0x000A0820, 0x00041041
};

const  uint32_t     g_tblPos09[25]  = {
    0x0010843E, 0x0021085D, 0x0042109B, 0x00842117, 0x0108420F,
    0x001087C1, 0x00210BA2, 0x00421364, 0x008422E8, 0x010841F0,
    0x0010F821, 0x00217442, 0x00426C84, 0x00845D08, 0x01083E10,
    0x001F0421, 0x002E8842, 0x004D9084, 0x008BA108, 0x0107C210,
    0x01E08421, 0x01D10842, 0x01B21084, 0x01742108, 0x00F84210
};

const  uint32_t     g_tblPos10[25]  = {
    0x01041062, 0x000820E5, 0x000045CA, 0x00008B94, 0x00111308,
    0x00820C43, 0x01041CA7, 0x0008B94E, 0x0011729C, 0x00226118,
    0x00418864, 0x008394E8, 0x011729D1, 0x002E5382, 0x004C2304,
    0x00310C88, 0x00729D10, 0x00E53A20, 0x01CA7041, 0x01846082,
    0x00219110, 0x0053A200, 0x00A74400, 0x014E0820, 0x008C1041
};

const  uint32_t     g_tblPos11[25]  = {
    0x0010847E, 0x002108FD, 0x004211DB, 0x00842397, 0x0108430F,
    0x00108FC3, 0x00211FA7, 0x00423B6E, 0x008472FC, 0x010861F8,
    0x0011F861, 0x0023F4E2, 0x00476DC4, 0x008E5F88, 0x010C3F10,
    0x003F0C21, 0x007E9C42, 0x00EDB884, 0x01CBF108, 0x0187E210,
    0x01E18421, 0x01D38842, 0x01B71084, 0x017E2108, 0x00FC4210
};

}   //  End of (Unnamed) namespace.

void  RuleTablesTest::testExpandDirTable01()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir01, g_tblDir00, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos01,  tblOut) );
}

void  RuleTablesTest::testExpandDirTable02()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir02, g_tblDir00, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos02,  tblOut) );
}

void  RuleTablesTest::testExpandDirTable03()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir03, g_tblDir00, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos03,  tblOut) );
}

void  RuleTablesTest::testExpandDirTable04()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir04, g_tblDir00, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos04,  tblOut) );
}

void  RuleTablesTest::testExpandDirTable05()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir05, g_tblDir00, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos05,  tblOut) );
}

void  RuleTablesTest::testExpandDirTable06()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir06, g_tblDir00, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos06,  tblOut) );
}

void  RuleTablesTest::testExpandDirTable07()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir07, g_tblDir00, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos07,  tblOut) );
}


void  RuleTablesTest::testExpandDirTable08()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir00, g_tblDir08, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos08,  tblOut) );
}

void  RuleTablesTest::testExpandDirTable09()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir00, g_tblDir09, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos09,  tblOut) );
}

void  RuleTablesTest::testExpandDirTable10()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir09, g_tblDir08, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos10,  tblOut) );
}

void  RuleTablesTest::testExpandDirTable11()
{
    uint32_t    tblOut[25];
    uint32_t    tblPin[25][25];

    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            RuleTables::expandDirTable(
                    g_tblDir08, g_tblDir09, tblOut, tblPin));
    CPPUNIT_ASSERT_EQUAL( 0,  checkExpandResult(g_tblPos11,  tblOut) );
}

int  RuleTablesTest::checkExpandResult(
        const  uint32_t  (& tblExp)[25],
        const  uint32_t  (& tblAct)[25])
{
    int sum = 0;

    for ( int i = 0; i < 25; ++ i ) {
        if ( tblExp[i] != tblAct[i] ) {
            std::cerr   <<  "\nIncorrect Table @ "  << i
                        <<  "\nExpect = "   <<  tblExp[i]
                        <<  "\nActual = "   <<  tblAct[i]
                        <<  std::endl;
            ++  sum;
        }
    }
    return ( sum );
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
