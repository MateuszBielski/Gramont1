#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Shared/transformowalne.h"

TEST(TransformowalneTest,MacierzObrotuZapisOdczyt)
{
    float macierz[] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    Transformowalne model;
    model.MacierzObrotu(macierz);
    EXPECT_FLOAT_EQ(2,model.MacierzObrotu()[3]);
}

TEST(TransformowalneTest,Quat)
{
    float quat[] = {2,2,2,2};
    Transformowalne model;
    model.Quat(quat);
    EXPECT_FLOAT_EQ(2,model.Quat()[2]);
}

TEST(TransformowalneTest,QuatDiff)
{
    float quat[] = {2,2,3,2};
    Transformowalne model;
    model.QuatDiff(quat);
    EXPECT_FLOAT_EQ(3,model.QuatDiff()[2]);
}
TEST(TransformowalneTest,WartosciStartowe)
{
    Transformowalne model;
    EXPECT_FLOAT_EQ(0,model.QuatDiff()[2]);
    EXPECT_FLOAT_EQ(1,model.QuatDiff()[3]);
    EXPECT_FLOAT_EQ(0,model.Quat()[0]);
    EXPECT_FLOAT_EQ(1,model.Quat()[3]);
    EXPECT_FLOAT_EQ(1,model.ppMacierzObrotu()[0][0]);
    EXPECT_FLOAT_EQ(1,model.ppMacierzObrotu()[2][2]);
}
TEST(TransformowalneTest,ReferencjaMacierzy)
{
    Transformowalne model;
    model.ppMacierzObrotu()[2][1] = 32.1;
    EXPECT_FLOAT_EQ(32.1,model.ppMacierzObrotu()[2][1]);
}
TEST(TransformowalneTest,UstawPozycje_kopiuje)
{
    float poz[] = {1,2,3.3};
    Transformowalne model;
    model.UstawPozycje(poz);
    poz[1] = 4;
    ASSERT_EQ(1,model.Pozycja()[0]);
    ASSERT_EQ(2,model.Pozycja()[1]);
    ASSERT_FLOAT_EQ(3.3,model.Pozycja()[2]);
}


