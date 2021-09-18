#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Shared/transformowalne.h"

TEST(Transformowalne,MacierzObrotuZapisOdczyt)
{
    float macierz[] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    Transformowalne model;
    model.MacierzObrotu(macierz);
    EXPECT_FLOAT_EQ(2,model.MacierzObrotu()[3]);
}

TEST(Transformowalne,Quat)
{
    float quat[] = {2,2,2,2};
    Transformowalne model;
    model.Quat(quat);
    EXPECT_FLOAT_EQ(2,model.Quat()[2]);
}

TEST(Transformowalne,QuatDiff)
{
    float quat[] = {2,2,3,2};
    Transformowalne model;
    model.QuatDiff(quat);
    EXPECT_FLOAT_EQ(3,model.QuatDiff()[2]);
}
TEST(Transformowalne,WartosciStartowe)
{
    Transformowalne model;
    EXPECT_FLOAT_EQ(0,model.QuatDiff()[2]);
    EXPECT_FLOAT_EQ(1,model.QuatDiff()[3]);
    EXPECT_FLOAT_EQ(0,model.Quat()[0]);
    EXPECT_FLOAT_EQ(1,model.Quat()[3]);
    EXPECT_FLOAT_EQ(1,model.ppMacierzObrotu()[0][0]);
    EXPECT_FLOAT_EQ(1,model.ppMacierzObrotu()[2][2]);
}
TEST(Transformowalne,ReferencjaMacierzy)
{
    Transformowalne model;
    model.ppMacierzObrotu()[2][1] = 32.1;
    EXPECT_FLOAT_EQ(32.1,model.ppMacierzObrotu()[2][1]);
}
TEST(Transformowalne,UstawPrzesuniecie_kopiuje)
{
    float poz[] = {1,2,3.3};
    Transformowalne model;
    model.UstawPrzesuniecie(poz);
    poz[1] = 4;
    ASSERT_EQ(1,model.Przesuniecie()[0]);
    ASSERT_EQ(2,model.Przesuniecie()[1]);
    ASSERT_FLOAT_EQ(3.3,model.Przesuniecie()[2]);
}
TEST(Transformowalne,NieMaTransformacji)
{
    Transformowalne model;
    ASSERT_FALSE(model.jestTransformacja);
}
TEST(Transformowalne,JestTransformacja_przesuniecie)
{
    Transformowalne model;
    float poz[] = {1,2,3.3};
    model.UstawPrzesuniecie(poz);
    ASSERT_TRUE(model.jestTransformacja);
}
TEST(Transformowalne,NieMa_obrot)
{
    Transformowalne model;
    float macierz[] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    model.MacierzObrotu(macierz);
    ASSERT_FALSE(model.jestTransformacja);
}
TEST(Transformowalne,JestTransformacja_obrot)
{
    Transformowalne model;
    float macierz[] = {1,0,0,0.1,0,1,0,0,0,0,1,0,0,0,0,1};
    model.MacierzObrotu(macierz);
    ASSERT_TRUE(model.jestTransformacja);
}
TEST(Transformowalne,DodajPrzesuniecie)
{
    Transformowalne t;
    float przes1[] = {2,2,0};
    float przes2[] = {-1.5,0.2,-0.4};
    t.UstawPrzesuniecie(przes1);
    t.DodajPrzesuniecie(przes2);
    ASSERT_FLOAT_EQ(0.5,t.Przesuniecie()[0]);
    ASSERT_FLOAT_EQ(2.2,t.Przesuniecie()[1]);
    ASSERT_FLOAT_EQ(-0.4,t.Przesuniecie()[2]);
}
TEST(Transformowalne,DodajPrzesuniecie_jestTransformacja)
{
    Transformowalne t;
    float przes1[] = {2,2,0};
    t.DodajPrzesuniecie(przes1);
    ASSERT_TRUE(t.jestTransformacja);
}
TEST(Transformowalne,DodajPrzesuniecie_nieMaTransformacji)
{
    Transformowalne t;
    float przes1[] = {0,0,0};
    t.DodajPrzesuniecie(przes1);
    ASSERT_FALSE(t.jestTransformacja);
}
TEST(Transformowalne,PowrotPrzesunieciaNaZero_nieMaTransformacji)
{
    Transformowalne t;
    float przes1[] = {0,2.3,0};
    float przes2[] = {0,-2.3,0};
    t.DodajPrzesuniecie(przes1);
    t.DodajPrzesuniecie(przes2);
    ASSERT_FALSE(t.jestTransformacja);
}
TEST(Transformowalne,UstawPrzesunieciaNaZero_nieMaTransformacji)
{
    Transformowalne t;
    t.jestTransformacja =true;
    float poz[] = {0,0,0};
    t.UstawPrzesuniecie(poz);
    ASSERT_FALSE(t.jestTransformacja);
}
TEST(Transformowalne,ObrotJest_PrzesWyzerowane)
{
    Transformowalne model;
    float macierz[] = {1,0,0,0.1,0,1,0,0,0,0,1,0,0,0,0,1};
    float poz[] = {0,1.2,0};
    model.UstawPrzesuniecie(poz);
    model.MacierzObrotu(macierz);
    float poz2[] = {0,0,0};
    model.UstawPrzesuniecie(poz2);
    
    ASSERT_TRUE(model.jestTransformacja);
}
TEST(Transformowalne,PrzesuniecieJest_ObrotWyzerowany)
{
    Transformowalne model;
    float macierz[] = {1,0,0,0.1,0,1,0,0,0,0,1,0,0,0,0,1};
    float poz[] = {0,1.2,0};
    model.UstawPrzesuniecie(poz);
    model.MacierzObrotu(macierz);
    float macierz2[] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    model.MacierzObrotu(macierz2);
    
    ASSERT_TRUE(model.jestTransformacja);
}

