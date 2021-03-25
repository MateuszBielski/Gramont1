#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Polecenie/transformacja.h"
#include "../src/Polecenie/kolejkapolecen.h"
#include "../src/Process/zarzadzaniemodelami.h"
//#include "../../gtk_GL_interfaces_tdd/funkcje/FunkcjePomocnicze.h"

TEST(PolecenieTest,DziedziczeniePobierzDane)
{
    upPolecenie polecenie = make_unique<Transformacja>();
    
    //    ASSERT_EQ(expect,macierzString);
    
}
TEST(KolejkaPolecen,Wlasciciel)
{
    spObslugaPolecen zarzadzanie= make_shared<ZarzadzanieModelami>();
    auto kolejka = make_unique<KolejkaPolecen<ObslugaPolecen>>(zarzadzanie);
    ASSERT_EQ(zarzadzanie,kolejka->getWlasciciel());
}
TEST(ObslugaPolecen,Kolejka)
{
    spObslugaPolecen zarzadzanie= make_shared<ZarzadzanieModelami>();
    auto kolejka = zarzadzanie->KolejkaRef();
    
}
TEST(Polecenie,WstawDoKolejki)
{
    
}