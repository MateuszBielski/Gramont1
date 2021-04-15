#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Process/zarzadzaniemodelami.h"
#include "../src/Polecenie/przerysuj.h"
#include "../src/Polecenie/obrot.h"
#include "donarysowaniamock.h"
#include "renderowaniemock.h"


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
    zarzadzanie.WysylaniePrzerysujPoTransformacji();
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
    ZarzadzanieModelami zarzadzanie;
    spDoNarysowania rys(make_shared<DoNarysowaniaMock>(12));
    zarzadzanie.DoNarysowania(rys);
    
    
    RenderowanieMock renderowanie;
    auto kolejka = renderowanie.getKolejkaPolecen();
    zarzadzanie.NadawanieDoRenderowania(kolejka);
    
    zarzadzanie.WyslijPoleceniePrzerysuj();
    kolejka->push(make_unique<PolecenieKoniec>());
    renderowanie.Run();
    auto res1 = static_pointer_cast<DoNarysowaniaMock>(renderowanie.DoNarysowania());
    
    ASSERT_EQ(12,res1->id);
}
TEST(ZarzadzanieModelami,PolecenieKoniecWylaczaWysylaniePrzerysujPoTransformacji)
{
    ZarzadzanieModelami zarzadzanie;
    zarzadzanie.WysylaniePrzerysujPoTransformacji();
    auto kolejkaZarzadzanie = zarzadzanie.getKolejkaPolecen();
    auto kolejkaRenderowanie(make_shared<KolejkaPolecen>());
    zarzadzanie.NadawanieDoRenderowania(kolejkaRenderowanie);
    
    kolejkaZarzadzanie->push(make_unique<PolecenieKoniec>());
    zarzadzanie.Run();
    ASSERT_FALSE(kolejkaRenderowanie->size());
    
}
TEST(ZarzadzanieModelami,StanWysylaniePrzeresujPoTransformacji)
{
    ZarzadzanieModelami zarzadzanie;
    zarzadzanie.WysylaniePrzerysujPoTransformacji();
    auto kolejkaZarzadzanie = zarzadzanie.getKolejkaPolecen();
    auto kolejkaRenderowanie(make_shared<KolejkaPolecen>());
    zarzadzanie.NadawanieDoRenderowania(kolejkaRenderowanie);
    
    kolejkaZarzadzanie->push(make_unique<Transformacja>());//może Obrot?
    kolejkaZarzadzanie->push(make_unique<PolecenieKoniec>());
    zarzadzanie.Run();
    ASSERT_EQ(1,kolejkaRenderowanie->size());
}
TEST(ZarzadzanieModelami,CoJestDoRysowaniaAcoDoTransformacji)
{
    
}