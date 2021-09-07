#include <gtest/gtest.h>
#include "../src/Shared/grupowalne.h"
#include "../src/Shared/prostytrojkat.h"
#include "../src/Process/renderowanie.h"
#include "renderowaniemock.h"//?
#include "testrenderklas.h"


TEST(PoleceniaRenderowania,Wstawienie3Polecen_sprawdzenieSkladni_TrescDoZmiany)
{
    spDoNarysowania trojkat = make_shared<ProstyTrojkat>();
    trojkat->PoleceniaWybierzIwstawWdobrejKolejnosci();
    auto polecenia =  trojkat->Polecenia();
//    
    ASSERT_EQ(3,polecenia.size());
//    
    PoleceniaRenderowania rend;
    for(auto& pol : polecenia)
    {
        (rend.*pol)(trojkat);
    }
}
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
    Renderowanie rend;
    TestRenderKlas trk;
    trk.UstawMonitorujaceFunkcjeDla(rend);
    rend.WywolajPoleceniaZ(rys1); 
    ASSERT_EQ(2001,trk.uzyteFunkcje["RysujGeometrie"]);
}

//TEST(PoleceniaRenderowania,RenderowanieWywolujePoleceniaZwiazaneZdoNarysowania)
//{
//   
//}
//renderowanie dostaje do kolejki polecenie w którym jest obiekt DoNarysowaniaJakoPolecenia, 
//wykonanie z użyciem funkcji szablonwej, bez pytania o typ 
