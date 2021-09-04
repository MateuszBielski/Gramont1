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
    
}

TEST(PoleceniaRenderowania,RenderowaniePotrafiWywolacPoleceniaZlisty)
{
    spDoNarysowania rys = make_shared<ProstyTrojkat>();
    rys->WstawPolecenie(&PoleceniaRenderowania::RysujGeometrie);
    Renderowanie rend;
    TestRenderKlas testRenderKlas;
//    testRenderKlas.UstawMonitorujaceFunkcjeDla(rend);
    rend.WywolajPoleceniaZ(rys);
//    rend.
}
TEST(PoleceniaRenderowania,RenderowanieWywolujePoleceniaZwiazaneZdoNarysowania)
{
    spDoNarysowania trojkat = make_shared<ProstyTrojkat>();
//    DoNarysowaniaJakoPolecenia polecenia;
    Renderowanie rend;
//    rend.WywolajPolecenia(trojkat.PoleceniaRenderowania());
    //tu powinno być możliwy dostęp do odpowiedniego obiektu DoNarysowaniaJakoPolecenia
    //miejsce w którym następuje wygenerowanie listy poleceń: Renderowanie, jako właściciel tych poleceń, ale jest sprzeczność, 
    //bo powinno tobyć zrobione w innym wątku
}
//renderowanie dostaje do kolejki polecenie w którym jest obiekt DoNarysowaniaJakoPolecenia, 
//wykonanie z użyciem funkcji szablonwej, bez pytania o typ 
