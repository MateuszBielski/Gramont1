#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Shared/kursor2d.h"

TEST(Kursor2d,ObliczRuch_ruch_xy)
{
//    ASSERT_EQ(expect,macierzString);
    Kursor2D kursor;
    kursor.PobierzPierwotnePolozenie(14,14);
    auto ruch = kursor.ObliczRuch(17,19);
    ASSERT_EQ(3,ruch.x);
    ASSERT_EQ(5,ruch.y);
}
TEST(Kursor2d,ObliczRuch_punktyDlaTrackball)
{
//    float p1x, float p1y, float p2x, float p2y
    Kursor2D kursor;
    kursor.PobierzWymiaryEkranu(200,100);
    kursor.PobierzPierwotnePolozenie(95,55);
    auto ruch = kursor.ObliczRuch(102,48);
    EXPECT_FLOAT_EQ(-0.05,ruch.p1x);
    EXPECT_FLOAT_EQ(-0.1,ruch.p1y);
    EXPECT_FLOAT_EQ(0.02,ruch.p2x);
    EXPECT_FLOAT_EQ(0.04,ruch.p2y);
}


