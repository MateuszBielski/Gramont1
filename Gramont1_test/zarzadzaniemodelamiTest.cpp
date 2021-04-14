#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Process/zarzadzaniemodelami.h"
#include "../src/Polecenie/przerysuj.h"
#include "../src/Polecenie/obrot.h"


TEST(ZarzadzanieModelami,LicznikTransformacjiDoAkumulowania)
{
    ZarzadzanieModelami zarzadzanie;
    zarzadzanie.LiczbaTransformacjiDoAkumulowania(11);
    for(short i = 0 ; i < 10 ; ++i)zarzadzanie.PowiadomionyOzakonczeniuTransformacji();
    ASSERT_EQ(10,zarzadzanie.LicznikTransformacjiAkumulowanych());
}
/*poniższe nie znajdują uzasadnienia przed dopracowaniem wyzwalacza renderowania
TEST(ZarzadzanieModelami,AkumulujeDomyslnieJednaTransformacje)
{
    ZarzadzanieModelami zarzadzanie;
//    auto kolejka(make_shared<KolejkaPolecen>());
//    zarzadzanie.NadawanieDoRenderowania(kolejka);
    zarzadzanie.PowiadomionyOzakonczeniuTransformacji();
    ASSERT_EQ(1,kolejka->size());
}

TEST(ZarzadzanieModelami,PowiadomienieOzakumulowaniuTransformacji)
{
    ZarzadzanieModelami zarzadzanie;
    auto kolejka(make_shared<KolejkaPolecen>());
    zarzadzanie.NadawanieDoRenderowania(kolejka);
    zarzadzanie.LiczbaTransformacjiDoAkumulowania(6);
    for(short i = 0 ; i < 10 ; ++i)zarzadzanie.PowiadomionyOzakonczeniuTransformacji();
    ASSERT_EQ(1,kolejka->size());
}
 * */

TEST(ZarzadzanieModelami,ZerowanieLicznikaTransformacjiDoPrzerysowania)
{
    ZarzadzanieModelami zarzadzanie;
    zarzadzanie.LiczbaTransformacjiDoAkumulowania(6);
    for(short i = 0 ; i < 9 ; ++i)zarzadzanie.PowiadomionyOzakonczeniuTransformacji();
    ASSERT_EQ(3,zarzadzanie.LicznikTransformacjiAkumulowanych());
}
TEST(ZarzadzanieModelami,WyslijPoleceniePrzerysuj_DodajeDoKolejki)
{
    ZarzadzanieModelami zarzadzanie;
    auto kolejkaRenderowanie(make_shared<KolejkaPolecen>());
    zarzadzanie.NadawanieDoRenderowania(kolejkaRenderowanie);
    zarzadzanie.WyslijPoleceniePrzerysuj();
    ASSERT_EQ(1,kolejkaRenderowanie->size());
}
TEST(ZarzadzanieModelami,PoWykonaniuObrotWstawiaPoleceniePrzerysuj)
{
    
    ZarzadzanieModelami zarzadzanie;
    auto kolejkaZarzadzania = zarzadzanie.getKolejkaPolecen();
    auto kolejkaRenderowanie(make_shared<KolejkaPolecen>());
    zarzadzanie.NadawanieDoRenderowania(kolejkaRenderowanie);
    
    zarzadzanie.DoTransformacji(make_unique<Transformowalne>());

    kolejkaZarzadzania->push(make_unique<Obrot>());
    kolejkaZarzadzania->push(make_unique<PolecenieKoniec>());
    ASSERT_TRUE(kolejkaRenderowanie->empty());
    zarzadzanie.Run();
    kolejkaRenderowanie->push(make_unique<PoleceniePuste>(0));
    
    auto polecenie = kolejkaRenderowanie->wait_and_pop();
    ASSERT_EQ(1,kolejkaRenderowanie->size());// powinno zawierać tylko 1 PoleceniePuste

    string expect("9Przerysuj");
    string result(typeid(*polecenie).name());
    
    ASSERT_EQ(expect,result);
    
}
TEST(ZarzadzanieModelami,PoleceniePrzerysujZawierajaceRysowalne)
{
    //Wstaw
}