#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Shared/transformowalne.h"
#include "../src/Polecenie/obrot.h"
#include "zarzadzaniemodelamimock.h"

TEST(TransformacjaTest,ObrotWykonaj_DostarczenieTransformowanego)
{
    ZarzadzanieModelamiMock zarzadzanie;//= make_shared<ZarzadzanieModelamiMock>();
//    spPolecenie  polecenie = make_shared<ObrotTemplate<ZarzadzanieModelami>>(zarzadzanie);
    upTransformacja polecenie = make_unique<Obrot>();
    polecenie->WykonajW(zarzadzanie);
    ASSERT_TRUE(zarzadzanie.doTransformacjiUsed);
}

TEST(TransformacjaTest,ObrotWykonaj_PrzekazanyRuchWplywaNaMacierzObrotu)
{
    
//    upTransformacja polecenie = make_unique<Obrot>(move(r));
    
    auto model = make_shared<DoNarysowania>();
    ZarzadzanieModelami zarzadzanie;
    zarzadzanie.DoTransformacji(model);
//    zarzadzanie.DoTransformacji(make_unique<Transformowalne>());
    RuchNaEkranie ruch;
    ruch.p1x = 0.0;
    ruch.p1y = 0.0;
    ruch.p2x = 0.02;
    ruch.p2y = 0.03;
    
    Obrot obrot(move(ruch));
    obrot.WykonajW(zarzadzanie);
    float expected[] = {0.99968731, -0.0004689882, -0.025, 0,
                        -0.0004689882, 0.99929655, -0.0375, 0,
                        0.025, 0.0375, 0.99898386, 0, 
                        0, 0, 0, 1};
    for(short i = 0 ; i < 16 ; i++){
        auto m = model->MacierzObrotu()[i];
//        cout<<m<<", ";
        EXPECT_FLOAT_EQ(expected[i],m);
    }
    int x = 0;
}
TEST(TransformacjaTest,ObrotInformujeOzakonczeniuTransformacji)
{
    ZarzadzanieModelamiMock zarzadzanie;
    Obrot obrot;
    obrot.WykonajW(zarzadzanie);
    ASSERT_TRUE(zarzadzanie.powiadomionyOzakonczeniuTransformacji);
}
    
