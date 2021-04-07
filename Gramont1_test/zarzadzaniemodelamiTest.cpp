#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Process/zarzadzaniemodelami.h"

TEST(ZarzadzanieModelamiTest,LicznikTransformacjiDoPrzerysowania)
{
    ZarzadzanieModelami zarzadzanie;
    zarzadzanie.PrzerysujPoTyluTransformacjach(11);
    for(short i = 0 ; i < 10 ; ++i)zarzadzanie.PowiadomionyOzakonczeniuTransformacji();
    ASSERT_EQ(10,zarzadzanie.LicznikTransformacjiDoPrzerysowania());
}
TEST(ZarzadzanieModelamiTest,PoleceniePrzerysujDomyslniePoJednejTransformacji)
{
    ZarzadzanieModelami zarzadzanie;
    auto kolejka = make_shared<KolejkaPolecen>();
    zarzadzanie.NadawanieDoRenderowania(kolejka);
    zarzadzanie.PowiadomionyOzakonczeniuTransformacji();
    ASSERT_EQ(1,kolejka->size());
}

TEST(ZarzadzanieModelamiTest,PoleceniePrzerysujPoOkreslonejLiczbieTransformacji)
{
    ZarzadzanieModelami zarzadzanie;
    auto kolejka = make_shared<KolejkaPolecen>();
    zarzadzanie.NadawanieDoRenderowania(kolejka);
    zarzadzanie.PrzerysujPoTyluTransformacjach(6);
    for(short i = 0 ; i < 10 ; ++i)zarzadzanie.PowiadomionyOzakonczeniuTransformacji();
    ASSERT_EQ(1,kolejka->size());
}
TEST(ZarzadzanieModelamiTest,ZerowanieLicznikaTransformacjiDoPrzerysowania)
{
    ZarzadzanieModelami zarzadzanie;
    zarzadzanie.PrzerysujPoTyluTransformacjach(6);
    for(short i = 0 ; i < 9 ; ++i)zarzadzanie.PowiadomionyOzakonczeniuTransformacji();
    ASSERT_EQ(3,zarzadzanie.LicznikTransformacjiDoPrzerysowania());
}