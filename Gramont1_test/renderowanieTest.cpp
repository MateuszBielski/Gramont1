#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Process/renderowanie.h"
#include "donarysowaniamock.h"
#include "ekranglmock.h"

TEST(RenderowanieTest,FunPrzerysujUzywaMacierzObrotu)
{
    Renderowanie rend;
    
    auto rys(make_shared<DoNarysowaniaMock>());
    rend.FunPrzerysuj(rys);
    ASSERT_TRUE(rys->macierzObrotuIsUsed);
}
//TEST(RenderowanieTest,FunPrzerysujUzywaPunk