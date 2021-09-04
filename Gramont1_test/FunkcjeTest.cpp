#include <gtest/gtest.h>
#include "testrenderklas.h"

TEST(Funkcje,TestRenderKlas_Monitorowanie_brakUzycia)
{
    TestRenderKlas trk;
    ASSERT_TRUE(trk.uzyteFunkcje.empty());
}
TEST(Funkcje,TestRenderKlas_FunkcjaMonitorujaca_jednoUzycie)
{
    TestRenderKlas trk;
    testUzytaFunkcja("funkcja");
    ASSERT_EQ(1,trk.uzyteFunkcje["funkcja"]);
}
TEST(Funkcje,TestRenderKlas_FunkcjaMonitorujaca_dwaUzycia)
{
    TestRenderKlas trk;
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    ASSERT_EQ(2,trk.uzyteFunkcje["funkcjaX"]);
}
TEST(Funkcje,TestRenderKlas_FunkcjaMonitorujaca_zliczaUzyteTylkoTeraz)
{
    TestRenderKlas trk;
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    ASSERT_EQ(3,trk.uzyteFunkcje["funkcjaX"]);
    ASSERT_EQ(0,trk.uzyteFunkcje["funkcja"]);
}

TEST(Funkcje,TestRenderKlas_Monitorowanie_zerujePrzyUruchomieniu)
{
    TestRenderKlas trk;
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    testUzytaFunkcja("funkcjaX");
    TestRenderKlas trk2;
    ASSERT_EQ(0,trk2.uzyteFunkcje.size());
}
