#include <gtest/gtest.h>
#include "testrenderklas.h"
#include "../src/Shared/nazwa.h"

TEST(Wybieralne,NazwyNieRowne)
{
    Nazwa n1(23), n2(24);
    
    ASSERT_FALSE(n1 == n2);
}
TEST(Wybieralne,NazwyRowne)
{
    Nazwa n1(23), n2(23);
    
    ASSERT_TRUE(n1 == n2);
}
