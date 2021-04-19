#include <gtest/gtest.h>
//#include <GL/gl.h>
#include <thread>
#include "../src/Process/renderowanie.h"
#include "../src/Process/obslugasygnalow.h"
#include "donarysowaniamock.h"
#include "ekranglmock.h"

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
//TEST(RenderowanieTest,FunPrzerysujUzywaPunk