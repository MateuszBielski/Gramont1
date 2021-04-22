#include <gtest/gtest.h>
//#include <GL/gl.h>
#include <thread>
#include "../src/Process/renderowanie.h"
#include "../src/Process/obslugasygnalow.h"
#include "../src/Shared/prostytrojkat.h"
#include "../src/Shared/szescian.h"
#include "donarysowaniamock.h"
#include "ekranglmock.h"
#include "testrenderklas.h"

TEST(RenderowanieTest,FunRysujSceneUzywaMacierzObrotu)
{
    Renderowanie rend;
    
    auto rys(make_shared<DoNarysowaniaMock>());
    rend.ustawDoNarysowania(rys);
    rend.RysujScene();
    ASSERT_TRUE(rys->macierzObrotuIsUsed);
}

TEST(RenderowanieTest,ZamkniecieOknaKonczyPetleIwatek)
{
    Renderowanie rend;
    thread t_renderowanie(&Renderowanie::Run,&rend);
    auto kolejka = rend.getKolejkaPolecen();
    kolejka->push(make_unique<PolecenieKoniec>());
    t_renderowanie.join();
    ASSERT_TRUE(kolejka->empty());
}
TEST(TestRenderKlasTest,FunkcjeZastepczeDlaOpenGl)
{
    TestRenderKlas renderTest;
    float vertex[] = {9,-2,4.1};
    float normalne[] = {5.2,-2.2,4.1};
    test_glVertex3fv(vertex);
    test_glNormal3fv(normalne);
    string expect("v9.0,-2.0,4.1,n5.2,-2.2,4.1,");
    string result = renderTest.CiagWywolanOpenGl();
    ASSERT_EQ(expect,result);
}
TEST(TestRenderKlasTest,UstawZastepczeFunkcje)
{
    TestRenderKlas renderTest;
    Renderowanie rend;
    ASSERT_TRUE(renderTest.UstawZastepczeOpenGlDla(rend));
}
TEST(RenderowanieTest,funkcjeGlDlaTrojkata)
{
    TestRenderKlas renderTest;
    Renderowanie rend;
    renderTest.UstawZastepczeOpenGlDla(rend);
    rend.ustawDoNarysowania(make_unique<ProstyTrojkat>());
    rend.RysujScene();
    string expect("n0.0,0.0,1.0,v-1.0,0.0,0.0,v1.0,0.0,0.0,v0.0,1.0,0.0,");
    string result = renderTest.CiagWywolanOpenGl();
    ASSERT_EQ(expect,result);
}
TEST(RenderowanieTest,funkcjeGlDlaSzescianu)
{
    TestRenderKlas renderTest;
    Renderowanie rend;
    renderTest.UstawZastepczeOpenGlDla(rend);
    rend.ustawDoNarysowania(make_unique<Szescian>());
    rend.RysujScene();
    string expect("n0.0,-1.0,0.0,v0.0,0.0,0.0,v1.0,0.0,0.0,v0.0,0.0,1.0,v1.0,0.0,1.0,");
    expect += "n0.0,0.0,1.0,v0.0,1.0,1.0,v1.0,1.0,1.0,";
    expect += "n0.0,1.0,0.0,v0.0,1.0,0.0,v1.0,1.0,0.0,";
    expect += "n1.0,0.0,0.0,v1.0,1.0,1.0,v1.0,0.0,1.0,v1.0,1.0,0.0,v1.0,0.0,0.0,";
    expect += "n0.0,0.0,-1.0,v0.0,1.0,0.0,v0.0,0.0,0.0,";
    expect += "n-1.0,0.0,0.0,v0.0,1.0,1.0,v0.0,0.0,1.0,";
//    string expect();
    string result = renderTest.CiagWywolanOpenGl();
    ASSERT_EQ(expect,result);
}
TEST(RenderowanieTest,RysujSceneZglaszaWyjatekPrzyBrakuDoNarysowania)
{
    Renderowanie rend;
    rend.ustawDoNarysowania(nullptr);
    try{
        rend.RysujScene();
    }catch(invalid_argument const & err) {
        EXPECT_EQ(err.what(),string("RysujScene() Brak doNarysowania"));
    }
}