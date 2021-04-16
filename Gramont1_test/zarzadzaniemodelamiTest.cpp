#include <gtest/gtest.h>
#include <GL/gl.h>
#include <thread>
#include "../src/Process/zarzadzaniemodelami.h"
#include "../src/Process/obslugasygnalow.h"
#include "../src/Polecenie/przerysuj.h"
#include "../src/Polecenie/obrot.h"
#include "../src/Shared/oknogtk.h"
#include "../src/Shared/ruchnaekranie.h"
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
TEST(ZarzadzanieModelami,WdrugimWatkuOdbieraPoleceniaZobslugiSyganlow)
{   
    OknoGtk okno(200,200);
    spEkranGL ekran = make_shared<EkranGL>();
    
    ObslugaSygnalow sygnaly;
    ZarzadzanieModelami zarzadzanie;
    okno.ZamontujEkran(ekran);
	sygnaly.ObslugujEkran(ekran);
    auto kolejka = zarzadzanie.getKolejkaPolecen();
    sygnaly.NadawanieDoZarzadzaniaObiektami(kolejka);
    GdkEventButton event1;
    event1.x = 100;event1.y = 100;
    GdkEventMotion event2;
    event2.x = 101;event2.y = 98;
    GdkEventAny event3;
    sygnaly.signal_button_press_event(&event1);
    sygnaly.on_motion_notify_event(&event2);
    sygnaly.on_delete_event(&event3);
    ASSERT_EQ(2,kolejka->size());
    thread t_zarzadzanie(&ZarzadzanieModelami::Run,&zarzadzanie);
    
    t_zarzadzanie.join();
    ASSERT_EQ(0,kolejka->size());
}
TEST(ZarzadzanieModelami,DoNarysowaniaItransformacji)
{
    ZarzadzanieModelami zarzadzanie;
    auto doNarysowania = make_shared<DoNarysowania>();
    zarzadzanie.DoNarysowaniaItransformacji(doNarysowania);
//    ASSERT_EQ(doNarysowania.get(),zarzadzanie.DoNarysowania().get());
    ASSERT_EQ(doNarysowania.get(),zarzadzanie.DoTransformacji().get());
}
TEST(ZarzadzanieModelami,WyslaneDoNarysowaniaNieJestPuste)
{
    ZarzadzanieModelami zarzadzanie;
    RenderowanieMock renderowanie;
    zarzadzanie.DoNarysowaniaItransformacji(make_shared<DoNarysowania>());
    zarzadzanie.WysylaniePrzerysujPoTransformacji();
    
    auto kolejkaZarz = zarzadzanie.getKolejkaPolecen();
    auto kolejkaRend = renderowanie.getKolejkaPolecen();
    zarzadzanie.NadawanieDoRenderowania(kolejkaRend);
    
    thread t_zarzadzanie(&ZarzadzanieModelami::Run,&zarzadzanie);
    thread t_renderowanie(&Renderowanie::Run,&renderowanie);
    
    RuchNaEkranie ruch;
    ruch.p1x = 0;
    ruch.p1y = 0;
    ruch.p2x = 0.33;
    ruch.p2y = -0.1;
    kolejkaZarz->push(make_unique<Obrot>(move(ruch)));
    
    
    kolejkaZarz->push(make_unique<PolecenieKoniec>());
    t_zarzadzanie.join();
    
    //Najpierw musi pierwszy wątek się skończyć, bo drugi zakończy się za nim zdąży od niego odebrać polecenia przerysuj. 
    kolejkaRend->push(make_unique<PolecenieKoniec>());
    t_renderowanie.join();
    
    ASSERT_TRUE(renderowanie.przerysujDostaloDoNarysowania);
}