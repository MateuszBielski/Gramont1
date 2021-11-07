#include <gtest/gtest.h>
#include <thread>
#include <future>
#include "../src/Shared/grupowalne.h"
#include "../src/Shared/prostytrojkat.h"
#include "../src/Shared/szescian.h"
#include "../src/Process/renderowanie.h"
#include "renderowaniemock.h"//?
#include "testrenderklas.h"
#include "donarysowaniamock.h"
#include "donarysowaniadostepprv.h"


TEST(PoleceniaRenderowania,ustawiaFunkcjeMonitorujaca)
{
    Renderowanie rend;
    TestRenderKlas trk;
    trk.UstawMonitorujaceFunkcjeDla(rend);
    rend.PrzedGeometria(make_unique<DoNarysowania>());
    rend.PrzedGeometria(make_unique<DoNarysowania>());
    rend.PoGeometrii(make_unique<DoNarysowania>());
    rend.PoGeometrii(make_unique<DoNarysowania>());
    rend.PoGeometrii(make_unique<DoNarysowania>());
    ASSERT_EQ(2,trk.uzyteFunkcje["PrzedGeometria"]);
    ASSERT_EQ(3,trk.uzyteFunkcje["PoGeometrii"]);
}

TEST(PoleceniaRenderowania,RenderowaniePotrafiWywolacPoleceniaZlisty)
{
    spDoNarysowania rys = make_shared<ProstyTrojkat>();
    rys->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    Renderowanie rend;
    TestRenderKlas trk;
    trk.UstawMonitorujaceFunkcjeDla(rend);
    rend.WywolajPoleceniaZ(rys); 
    ASSERT_EQ(1,trk.uzyteFunkcje["RysujGeometrie"]);
}
TEST(PoleceniaRenderowania,WywolanieDlaGrupowanych)
{
    spDoNarysowania rys1 = make_shared<DoNarysowania>();
    rys1->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    spDoNarysowania rys2 = make_shared<DoNarysowania>();
    rys2->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    spDoNarysowania rys3 = make_shared<DoNarysowania>();
    rys3->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    
    rys1->DodajDziecko(rys2);
    rys1->DodajDziecko(rys3);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    Renderowanie rend;
    TestRenderKlas trk;
    trk.UstawMonitorujaceFunkcjeDla(rend);
    rend.WywolajPoleceniaZ(rys1); 
    ASSERT_EQ(3,trk.uzyteFunkcje["RysujGeometrie"]);
}
TEST(PoleceniaRenderowania,WywolanieDlaGrupowanych_DuzaLiczba)
{
    spDoNarysowania rys1 = make_shared<DoNarysowania>();
    rys1->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    for(int i = 0; i < 2000 ;i++)
    {
        spDoNarysowania rys2 = make_shared<DoNarysowania>();
        rys2->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
        rys1->DodajDziecko(rys2);
    }
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    Renderowanie rend;
    TestRenderKlas trk;
    trk.UstawMonitorujaceFunkcjeDla(rend);
    rend.WywolajPoleceniaZ(rys1); 
    ASSERT_EQ(2001,trk.uzyteFunkcje["RysujGeometrie"]);
}
TEST(PoleceniaRenderowania,RysujGeometriePowierzchnie_uzywaVertexeInormalne)
{
    TestRenderKlas renderTest;
    Renderowanie rend;
    renderTest.UstawZastepczeOpenGlDla(rend);
    rend.RysujGeometriePowierzchnie(make_unique<Szescian>());
    string expect("n0.0,-1.0,0.0,v0.0,0.0,0.0,v1.0,0.0,0.0,v0.0,0.0,1.0,v1.0,0.0,1.0,");
    expect += "n0.0,0.0,1.0,v0.0,1.0,1.0,v1.0,1.0,1.0,";
    expect += "n0.0,1.0,0.0,v0.0,1.0,0.0,v1.0,1.0,0.0,";
    expect += "n1.0,0.0,0.0,v1.0,1.0,1.0,v1.0,0.0,1.0,v1.0,1.0,0.0,v1.0,0.0,0.0,";
    expect += "n0.0,0.0,-1.0,v0.0,1.0,0.0,v0.0,0.0,0.0,";
    expect += "n-1.0,0.0,0.0,v0.0,1.0,1.0,v0.0,0.0,1.0,";
    string result = renderTest.CiagWywolanOpenGl();
    ASSERT_EQ(expect,result);
}
TEST(PoleceniaRenderowania,Przesun_uzywaPrzesun)
{
    auto rys = make_shared<DoNarysowaniaMock>();
    Renderowanie rend;
    rend.Przesun(rys);
    ASSERT_TRUE(rys->przesuniecieIsUsed);
}
TEST(PoleceniaRenderowania,funkcjeGlCzyWywolujeDlaDzieci)
{
    TestRenderKlas renderTest;
    Renderowanie rend;
    renderTest.UstawZastepczeOpenGlDla(rend);
    
    auto rys = make_shared<DoNarysowania>();
    auto trojkat1 = make_shared<ProstyTrojkat>();
    auto trojkat2 = make_shared<ProstyTrojkat>();
    
    rys->DodajDziecko(trojkat1);
    rys->DodajDziecko(trojkat2);
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    rend.WywolajPoleceniaZ(rys);
    string expect("n0.0,0.0,1.0,v-1.0,0.0,0.0,v1.0,0.0,0.0,v0.0,1.0,0.0,");
    //wartości dla drugiego trójkąta
    expect +="n0.0,0.0,1.0,v-1.0,0.0,0.0,v1.0,0.0,0.0,v0.0,1.0,0.0,";
    string result = renderTest.CiagWywolanOpenGl();
    ASSERT_EQ(expect,result);
}
TEST(PoleceniaRenderowania,WywolajPoleceniaBlokujaMutexDoNarysowania)
{
    TestRenderKlas renderTest;
    Renderowanie rend;
    
    promise<void> moznaSkonczyc;
    renderTest.UstawPrzyszloscDla(moznaSkonczyc.get_future(),rend);
    future<void> wywolajGotowe = renderTest.PrzyszloscZobietnicy(rend);

    auto rys(make_shared<DoNarysowania>());
    DoNarysowaniaDostepPrv dostep(*rys);
    
    future<void> oddzielnyProces = std::async(std::launch::async,
                         [&](){
                                 rend.WywolajPoleceniaZ(rys);
                             });
    //czekam na drugi wątek, który zasygnalizuje, że dotarł do określonego miejsca
    // w tym wypadku po ustawieniu blokady
    wywolajGotowe.wait();
    unique_lock<mutex> blokada(dostep.getMutex(),std::defer_lock);
    bool udaloSieZablokowac = blokada.try_lock();
    //po próbie zablokowania wysyłamy sygnał do drugiego wątku, który teraz czekał, że może iść dalej
    moznaSkonczyc.set_value();
    ASSERT_FALSE(udaloSieZablokowac);
}
