#include <gtest/gtest.h>
//#include <GL/gl.h>
#include "../src/Shared/szescian.h"
#include "../src/Shared/prostytrojkat.h"

TEST(DoNarysowania,SzescianIndeksyNaroznikow)
{
//    w kolejności dla GL_TRIANGLE_STRIP
    spDoNarysowania szescian(make_shared<Szescian>());
    ASSERT_EQ(16,szescian->ileNaroznikow);
    short narozniki[16] = {3,2,0,1,4,5,7,6,5,1,6,2,7,3,4,0};
    for(short i = 0; i < 16; i++)ASSERT_EQ(narozniki[i],szescian->indeksyNaroznikow[i]);
        
}
TEST(DoNarysowania,WspolrzedneTrojkata)
{
    auto lambda_gl_vertex3fv = [](float * v,float f0,float f1,float f2){
        ASSERT_EQ(v[0],f0);
        ASSERT_EQ(v[1],f1);
        ASSERT_EQ(v[2],f2);
        };
    spDoNarysowania trojkat(make_shared<ProstyTrojkat>());
    float wspolrzedne[] = {-1,0,0,1,0,0,0,1,0};
    lambda_gl_vertex3fv(&trojkat->wspolrzedne[trojkat->indeksyNaroznikow[0]*3],-1,0,0);
    lambda_gl_vertex3fv(&trojkat->wspolrzedne[trojkat->indeksyNaroznikow[1]*3],1,0,0);
    lambda_gl_vertex3fv(&trojkat->wspolrzedne[trojkat->indeksyNaroznikow[2]*3],0,1,0);
}
//TEST(DoNarysowaniaTest,SzescianWspolrzedneWierzcholkow)
//{
//    doNarysowania szescian(make_shared<Szescian>());
//    float wspolrzedne3f[] = {0,0,-1,};
//}


