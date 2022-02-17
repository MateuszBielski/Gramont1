#include <gtest/gtest.h>
//#include <GL/gl.h>
#include "../src/Shared/szescian.h"
#include "../src/Shared/prostytrojkat.h"
#include "../src/Process/renderowanie.h"
#include "../src/Pomocnicze/FunkcjeIstruktury.h"
#include "donarysowaniadostepprv.h"

TEST(AktualizujListe,UstawListyPrzedAktualizacjaglownaOdlaczona_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(false);
    
    rys->UstawListyPrzedAktualizacja();
    
    ASSERT_TRUE(dostep.ListaGlownaOdlaczona());
}
TEST(AktualizujListe,UstawListyPrzedAktualizacjaAdresyListRozniaSie)
{
    auto rys = make_shared<DoNarysowania>();
    auto adres1 = &(rys->Polecenia());
    rys->UstawListyPrzedAktualizacja();
    auto adres2 = &(rys->Polecenia());
    ASSERT_NE(adres1,adres2);
}
TEST(AktualizujListe,PoleceniaZwracajaOdpowiednioJesliListaGlownaOdlaczona)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(false);
    auto adres1 = &(rys->Polecenia());
    dostep.ListaGlownaOdlaczona(true);
    auto adres2 = &(rys->Polecenia());
    ASSERT_NE(adres1,adres2);
}
TEST(AktualizujListe,NieUstawiajListPrzedJesliNieSkopiowanaGlowna_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaSkopiowana(false);
    rys->UstawListyPrzedAktualizacja();
    ASSERT_FALSE(dostep.ListaGlownaOdlaczona());
}
TEST(AktualizujListe,NieUstawiajListPrzed_adresy)
{
    auto rys = make_shared<DoNarysowania>();
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaSkopiowana(false);
    auto adres1 = &(rys->Polecenia());
    rys->UstawListyPrzedAktualizacja();
    auto adres2 = &(rys->Polecenia());
    ASSERT_EQ(adres1,adres2);
}
TEST(AktualizujListe,UstawListyPrzed_ListaGlownaNieSkopiowana_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys); 
    dostep.ListaGlownaSkopiowana(true);
    rys->UstawListyPrzedAktualizacja();
    ASSERT_FALSE(dostep.ListaGlownaSkopiowana());
}
/*******************aktual************/
TEST(AktualizujListe,NieAktualizujJesliListaGlownaNieOdlaczona)
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
TEST(AktualizujListe,NieUkonczonaAktualizacjaJesliListaGlownaNieOdlaczona)
{
    auto rys = make_shared<DoNarysowania>();
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ZakonczonaAktualizacja(true);
    dostep.ListaGlownaOdlaczona(false);
    rys->AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    ASSERT_FALSE(dostep.ZakonczonaAktualizacja());
}
TEST(AktualizujListe,PoAktualizacjiPoleceniaUdostepniajaTymczasowa)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(true);
    auto adresTymczasowa = &(rys->Polecenia());
    rys->AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    ASSERT_EQ(adresTymczasowa,&(rys->Polecenia()));
    
}
TEST(AktualizujListe,DzialajaceAktualizujNieModyfikujeTymczasowej)
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
TEST(AktualizujListe,PoAktualizujZakonczonaAktualizacja)
{
    auto rys = make_shared<DoNarysowania>();
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(true);
    rys->AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    ASSERT_TRUE(dostep.ZakonczonaAktualizacja());
}
TEST(AktualizujListe,NieUstawiaListyPoAktualizacjiJesliNieZakonczonaAktualizacja)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ZakonczonaAktualizacja(false);
    rys->UstawListyPoAktualizacji();
    ASSERT_FALSE(dostep.ListaGlownaOdlaczona());
}
TEST(AktualizujListe,NieKopiujTymczasowejJesliNieZakonczonaAktualizacja)
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
TEST(AktualizujListe,KopiujTymczasowaJesliZakonczonaAktualizacja)
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
TEST(AktualizujListe,UstawListyPo_ListaGlownaSkopiowana_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaSkopiowana(false);
    dostep.ZakonczonaAktualizacja(true);
    rys->UstawListyPoAktualizacji();
    
    ASSERT_TRUE(dostep.ListaGlownaSkopiowana());
    
}
TEST(AktualizujListe,UstawListyPo_ListaGlownaNieSkopiowana_flaga)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaSkopiowana(false);
    dostep.ZakonczonaAktualizacja(false);
    rys->UstawListyPoAktualizacji();
    
    ASSERT_FALSE(dostep.ListaGlownaSkopiowana());
}
/*******razem***/
TEST(AktualizujListe,NieModyfikujeListDlaPrzedAktPo_jesliWstepnyNieSpelniony)
{
     ASSERT_TRUE(false);
}
//pogrupować sprawdzenia dla przed akt po
TEST(AktualizujListe,OddzielneMutexyPodczasAktualizacji)
{
    auto rys = make_shared<DoNarysowania>();
    DoNarysowaniaDostepPrv dostep(*rys);
    dostep.ListaGlownaOdlaczona(true);
    unique_lock<mutex> blokada(dostep.getMutex(),std::defer_lock);
    bool udaloSieZablokowac = blokada.try_lock();
    ASSERT_TRUE(udaloSieZablokowac);
    if(udaloSieZablokowac)blokada.unlock();
}
TEST(AktualizujListe,UstawListyPoAktualizacjiBlokadaMuteksow)
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
TEST(AktualizujListe,ResetListy_zerowanieMoichPoczatkaIkonca)
{
    l_PolecenieIgeometria::iterator iteratorPusty;
    auto rys(make_shared<DoNarysowania>());
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_NE(iteratorPusty,rys->itPierwszeMojePolecenie());
    ASSERT_NE(iteratorPusty,rys->itOstatnieMojePolecenie());
    rys->ListePolecenResetuj();
    ASSERT_EQ(iteratorPusty,rys->itPierwszeMojePolecenie());
    ASSERT_EQ(iteratorPusty,rys->itOstatnieMojePolecenie());
    
}
TEST(AktualizujListe,ResetListy_ListaGlownaZero)
{
    auto rys(make_shared<DoNarysowania>());
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    DoNarysowaniaDostepPrv dostepDoNarys(*rys);
    ASSERT_TRUE(dostepDoNarys.ListaGlownaUstawiona());
    rys->ListePolecenResetuj();
    ASSERT_FALSE(dostepDoNarys.ListaGlownaUstawiona());
}
TEST(AktualizujListe,PrzekazPoleceniaIaktywujDlaWywolujeResetListy
{
    
}
//zerowanie wskaźników przy resecie sprawdzić również dla dzieci
//zakładam, że przekazanie poleceń nie musi automatycznie wywolać przeliczenia
//okaże się to po włączeniu wszystkich testów
    
/*
TEST(AktualizujListe,AktualizacjaListyDzieckaNieModyfikujeListyAktywnejWdonarysowania)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    float poz[] = {1,0,0};
    rys2->UstawPrzesuniecie(poz);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_EQ(8,rys1->Polecenia().size());//-
    ASSERT_EQ(0,rys1->PoleceniaAktywne().size());//-
    
    auto rys3(make_shared<DoNarysowania>());
    rys1->PrzekazPoleceniaIaktywujDla(rys3);
    
//    rys2->NieWidoczny(true);
    rys2->AktualizujMojePolecenia();
    
    ASSERT_EQ(0,rys1->Polecenia().size());//-
    ASSERT_EQ(0,rys2->Polecenia().size());//-
    ASSERT_EQ(8,rys3->PoleceniaAktywne().size());//-
}
 * */
