#include <gtest/gtest.h>
//#include "testrenderklas.h"
#include "../src/Shared/nazwa.h"

TEST(Nazwa,NazwyNieRowne)
{
    Nazwa n1(23), n2(24);
    
    ASSERT_FALSE(n1 == n2);
}
TEST(Nazwa,NazwyRowne)
{
    Nazwa n1(23), n2(23);
    
    ASSERT_TRUE(n1 == n2);
}
TEST(Nazwa,StringNazwyNieRowne)
{
    Nazwa n1("nazwa1"), n2("nazwa2");
    
    ASSERT_FALSE(n1 == n2);
}
TEST(Nazwa,StringNazwyRowne)
{
    Nazwa n1("nazwa1"), n2("nazwa1");
    
    ASSERT_TRUE(n1 == n2);
}
TEST(Nazwa,StringNieRowneInt)
{
    Nazwa n1("1"), n2(1);
    
    ASSERT_FALSE(n1 == n2);
}
TEST(Nazwa,Przypisanie)
{
    Nazwa n1(3), n2(5);
    n1 = n2;
    ASSERT_TRUE(n1 == n2);
}
TEST(Nazwa,PorownanieRvalue)
{
    Nazwa n1(3);
    bool result = n1 == Nazwa(3);
    ASSERT_TRUE(result);
}
TEST(Nazwa,mniejszeRvalue)
{
    Nazwa n1(3);
    ASSERT_TRUE(n1 < Nazwa(4));
}
TEST(Nazwa,mniejszeInt)
{
    Nazwa n1(3), n2(5);
    ASSERT_TRUE(n1 < n2);
}
TEST(Nazwa,mniejszeStr)
{
    Nazwa n1("nazwa1"), n2("nbzwa2");
    ASSERT_TRUE(n1 < n2);
}
TEST(Nazwa,wiekszeStr)
{
    Nazwa n1("nbzwa1"), n2("nazwa2");
    ASSERT_FALSE(n1 < n2);
}
