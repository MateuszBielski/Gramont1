#include <gtest/gtest.h>
//#include <GL/gl.h>
#include "../src/Shared/szescian.h"
#include "../src/Shared/prostytrojkat.h"
#include "../src/Process/renderowanie.h"
#include "../src/Shared/FunkcjeIstruktury.h"
#include "donarysowaniadostepprv.h"

TEST(DoNarysowania,UstawListyPrzedAktualizacjaglownaOdlaczona_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(false);
    
    rys->UstawListyPrzedAktualizacja();
    
    ASSERT_TRUE(dostep.ListaGlownaOdlaczona());
}
TEST(DoNarysowania,UstawListyPrzedAktualizacjaAdresyListRozniaSie)
{
    auto rys = make_shared<DoNarysowania>();
    auto adres1 = &(rys->Polecenia());
    rys->UstawListyPrzedAktualizacja();
    auto adres2 = &(rys->Polecenia());
    ASSERT_NE(adres1,adres2);
}
TEST(DoNarysowania,PoleceniaZwracajaOdpowiednioJesliListaGlownaOdlaczona)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(false);
    auto adres1 = &(rys->Polecenia());
    dostep.ListaGlownaOdlaczona(true);
    auto adres2 = &(rys->Polecenia());
    ASSERT_NE(adres1,adres2);
}
TEST(DoNarysowania,NieUstawiajListPrzedJesliNieSkopiowanaGlowna_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaSkopiowana(false);
    rys->UstawListyPrzedAktualizacja();
    ASSERT_FALSE(dostep.ListaGlownaOdlaczona());
}
TEST(DoNarysowania,NieUstawiajListPrzed_adresy)
{
    auto rys = make_shared<DoNarysowania>();
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaSkopiowana(false);
    auto adres1 = &(rys->Polecenia());
    rys->UstawListyPrzedAktualizacja();
    auto adres2 = &(rys->Polecenia());
    ASSERT_EQ(adres1,adres2);
}
TEST(DoNarysowania,UstawListyPrzed_ListaGlownaNieSkopiowana_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys); 
    dostep.ListaGlownaSkopiowana(true);
    rys->UstawListyPrzedAktualizacja();
    ASSERT_FALSE(dostep.ListaGlownaSkopiowana());
}
/*******************aktual************/
TEST(DoNarysowania,NieAktualizujJesliListaGlownaNieOdlaczona)
{
//    listaGlownaOdlaczona
    auto rys = make_shared<DoNarysowania>();
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    rys->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(false);
    
    rys->AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::RysujGeometrie,rys->Polecenia()));
}
TEST(DoNarysowania,NieUkonczonaAktualizacjaJesliListaGlownaNieOdlaczona)
{
    auto rys = make_shared<DoNarysowania>();
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ZakonczonaAktualizacja(true);
    dostep.ListaGlownaOdlaczona(false);
    rys->AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    ASSERT_FALSE(dostep.ZakonczonaAktualizacja());
}
TEST(DoNarysowania,PoAktualizacjiPoleceniaUdostepniajaTymczasowa)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(true);
    auto adresTymczasowa = &(rys->Polecenia());
    rys->AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    ASSERT_EQ(adresTymczasowa,&(rys->Polecenia()));
    
}
TEST(DoNarysowania,DzialajaceAktualizujNieModyfikujeTymczasowej)
{
    auto rys = make_shared<DoNarysowania>();
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(false);
    auto& glowna = rys->Polecenia();
    dostep.ListaGlownaOdlaczona(true);
    auto& tymczasowa = rys->Polecenia();
    
    tymczasowa.clear();
    tymczasowa.push_back({&PoleceniaRenderowania::PushMatrix,rys});
    tymczasowa.push_back({&PoleceniaRenderowania::Przesun,rys});
    tymczasowa.push_back({&PoleceniaRenderowania::PopMatrix,rys});
    
    glowna.clear();
    rys->AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    //upewniamy się że powyższe zrobiło jakąś akcję
    ASSERT_TRUE(glowna.size() > 0);
    
    ASSERT_EQ(3,tymczasowa.size());
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::PopMatrix,tymczasowa));
}
/**************Po***********/
TEST(DoNarysowania,PoAktualizujZakonczonaAktualizacja)
{
    auto rys = make_shared<DoNarysowania>();
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(true);
    rys->AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    ASSERT_TRUE(dostep.ZakonczonaAktualizacja());
}
TEST(DoNarysowania,NieUstawiaListyPoAktualizacjiJesliNieZakonczonaAktualizacja)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ZakonczonaAktualizacja(false);
    rys->UstawListyPoAktualizacji();
    ASSERT_FALSE(dostep.ListaGlownaOdlaczona());
}
TEST(DoNarysowania,NieKopiujTymczasowejJesliNieZakonczonaAktualizacja)
{   
    auto rys = make_shared<DoNarysowania>();
//    spGeometriaModelu geom = rys;
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(true);
    auto& tymczasowa = rys->Polecenia();
    dostep.ListaGlownaOdlaczona(false);
    auto& glowna = rys->Polecenia();
    
    tymczasowa.clear();
    glowna.clear();
    glowna.push_back({&PoleceniaRenderowania::Przesun,rys});
    glowna.push_back({&PoleceniaRenderowania::Przesun,rys});
    
    dostep.ZakonczonaAktualizacja(false);
    rys->UstawListyPoAktualizacji();
    ASSERT_EQ(0,tymczasowa.size());
}
TEST(DoNarysowania,KopiujTymczasowaJesliZakonczonaAktualizacja)
{   
    auto rys = make_shared<DoNarysowania>();
//    spGeometriaModelu geom = rys;
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(true);
    auto& tymczasowa = rys->Polecenia();
    dostep.ListaGlownaOdlaczona(false);
    auto& glowna = rys->Polecenia();
    
    tymczasowa.clear();
    glowna.clear();
    glowna.push_back({&PoleceniaRenderowania::Przesun,rys});
    glowna.push_back({&PoleceniaRenderowania::Przesun,rys});
    
    dostep.ZakonczonaAktualizacja(true);
    rys->UstawListyPoAktualizacji();
    ASSERT_EQ(2,tymczasowa.size());
}
TEST(DoNarysowania,UstawListyPo_ListaGlownaSkopiowana_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaSkopiowana(false);
    dostep.ZakonczonaAktualizacja(true);
    rys->UstawListyPoAktualizacji();
    
    ASSERT_TRUE(dostep.ListaGlownaSkopiowana());
    
}
TEST(DoNarysowania,UstawListyPo_ListaGlownaNieSkopiowana_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaSkopiowana(false);
    dostep.ZakonczonaAktualizacja(false);
    rys->UstawListyPoAktualizacji();
    
    ASSERT_FALSE(dostep.ListaGlownaSkopiowana());
}
/*******razem***/
TEST(DoNarysowania,NieModyfikujeListDlaPrzedAktPo_jesliWstepnyNieSpelniony)
{
    
}
//pogrupować sprawdzenia dla przed akt po
TEST(DoNarysowania,UstawListyPoAktualizacjiBlokadaMuteksow)
{
//    auto rys = make_shared<DoNarysowania>();
//    
//    DoNarysowaniaDostepPrv dostep(*rys);
//    dostep.ListaGlownaOdlaczona(false);
//    rys->UstawListyPoAktualizacji();
    ASSERT_TRUE(false);
}

//AktualizacjaPracujeNaKopiiListyIpoWykonaniuPodmieniaJą
//dwa razy aktualizować, czy nie robią się problemy z listami