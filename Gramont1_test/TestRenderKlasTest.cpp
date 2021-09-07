#include <gtest/gtest.h>
#include "testrenderklas.h"

TEST(TestRenderKlas,Monitorowanie_brakUzycia)
{
    TestRenderKlas trk;
    ASSERT_TRUE(trk.uzyteFunkcje.empty());
}
TEST(TestRenderKlas,FunkcjaMonitorujaca_jednoUzycie)
{
    TestRenderKlas trk;
    testUzytaFunkcja("funkcja");
    ASSERT_EQ(1,trk.uzyteFunkcje["funkcja"]);
}
TEST(TestRenderKlas,FunkcjaMonitorujaca_dwaUzycia)
{
    TestRenderKlas trk;
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    ASSERT_EQ(2,trk.uzyteFunkcje["funkcjaX"]);
}
TEST(TestRenderKlas,FunkcjaMonitorujaca_zliczaUzyteTylkoTeraz)
{
    TestRenderKlas trk;
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    ASSERT_EQ(3,trk.uzyteFunkcje["funkcjaX"]);
    ASSERT_EQ(0,trk.uzyteFunkcje["funkcja"]);
}

TEST(TestRenderKlas,Monitorowanie_zerujePrzyUruchomieniu)
{
    TestRenderKlas trk;
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    TestRenderKlas trk2;
    ASSERT_EQ(0,trk2.uzyteFunkcje.size());
}
TEST(TestRenderKlas,MonitorujeKolejnoscFunkcji)
{
    TestRenderKlas trk;
    testUzytaFunkcja("f_x");
    testUzytaFunkcja("f_y");
    testUzytaFunkcja("f_z");
    testUzytaFunkcja("f_y");
    auto iter = trk.funkcjeWkolejnosci.begin();
    ASSERT_EQ("f_x",*iter++);
    ASSERT_EQ("f_y",*iter++);
    ASSERT_EQ("f_z",*iter++);
    ASSERT_EQ("f_y",*iter++);
}
