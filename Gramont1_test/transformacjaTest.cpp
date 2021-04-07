#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Shared/transformacjaItfc.h"
#include "../src/Shared/transformowalne.h"
#include "../src/Polecenie/obrot.h"
#include "zarzadzaniemodelamimock.h"
//#include "../src/Polecenie.h"

TEST(TransformacjaTest,Obracaj_macierzObrotu)
{
    RuchNaEkranie r;
    r.p1x = 0.0;
    r.p1y = 0.0;
    r.p2x = 0.02;
    r.p2y = 0.03;
    
    auto model = make_shared<Transformowalne>();
    
    TransformacjaItfc tr;
    
    tr.Transformowalne(model);
    
    tr.Obracaj(move(r));
    float expected[] = {0.99968731, -0.0004689882, -0.025, 0,
                        -0.0004689882, 0.99929655, -0.0375, 0,
                        0.025, 0.0375, 0.99898386, 0, 
                        0, 0, 0, 1};
    for(short i = 0 ; i < 16 ; i++){
        auto m = model->MacierzObrotu()[i];
//        cout<<m<<", ";
        EXPECT_FLOAT_EQ(expected[i],m);
    }
}
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
    
    auto model = make_shared<Transformowalne>();
    ZarzadzanieModelami zarzadzanie;
    zarzadzanie.DoTransformacji(model);
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
//    auto model = make_shared<Transformowalne>();
//    zarzadzanie.DoTransformacji(model);
    Obrot obrot;
    obrot.WykonajW(zarzadzanie);
    ASSERT_TRUE(zarzadzanie.powiadomionyOzakonczeniuTransformacji);
}
    //zrobić kolejkę wewnętrzną - bufor zmian do realizacji.
