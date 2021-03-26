#include <gtest/gtest.h>
#include <GL/gl.h>
//#include <gtkglmm.h>

#include "../src/Polecenie/kolejkapolecen.h"
#include "../src/Process/obslugasygnalow.h"
#include "../src/Polecenie/obrot.h"
//#include "../src/Process/zarzadzaniemodelami.h"
#include "zarzadzaniemodelamimock.h"

/*
TEST(PolecenieTest,UtworzenieObrotZParametremObslugujacy)
{
    spZarzadzanieModelami zarzadzanie= make_shared<ZarzadzanieModelami>();
    
    spPolecenie  polecenie = make_shared<ObrotTemplate<ZarzadzanieModelami>>(zarzadzanie);
        ASSERT_NE(nullptr,polecenie);
    
}
TEST(PolecenieTest,obrotWykonajWywolujeDoTransformacji)
{
    spZarzadzanieModelami zarzadzanie= make_shared<ZarzadzanieModelamiMock>();
    spPolecenie  polecenie = make_shared<ObrotTemplate<ZarzadzanieModelami>>(zarzadzanie);
    
    polecenie->WykonajW();
    ASSERT_TRUE(zarzadzanie->doTransformacjiUsed);
}*/
TEST(PolecenieTest,ObslugaSygnalowDodajeDoKolejki)
{
    auto kolejka = make_shared<KolejkaPolecen>();
    ObslugaSygnalow sygnaly;
    sygnaly.NadawanieDoZarzadzaniaObiektami(kolejka);
    GdkEventMotion e;
    sygnaly.on_motion_notify_event(&e);
    ASSERT_EQ(1,kolejka->size());
}