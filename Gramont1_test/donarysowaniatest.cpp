#include <gtest/gtest.h>
//#include <GL/gl.h>
#include "../src/Shared/szescian.h"
#include "../src/Shared/prostytrojkat.h"
#include "../src/Pomocnicze/FunkcjeIstruktury.h"
#include "../src/Process/renderowanie.h"
#include "donarysowaniadostepprv.h"
#include "donarysowaniamock.h"


TEST(DoNarysowania,SzescianIndeksyVertexow)
{
//    w kolejności dla GL_TRIANGLE_STRIP
    spDoNarysowania szescian(make_shared<Szescian>());
    ASSERT_EQ(16,szescian->ileVertexow);
    short narozniki[16] = {3,2,0,1,4,5,7,6,5,1,6,2,7,3,4,0};
    for(short i = 0; i < 16; i++)ASSERT_EQ(narozniki[i],szescian->indeksyVertexow[i]);
}

void assert_gl_3fv(float * v,float f0,float f1,float f2)
{
//    cout<<"\n"<<v[0]<<" "<<v[1]<<" "<<v[2];
    ASSERT_EQ(v[0],f0);
    ASSERT_EQ(v[1],f1);
    ASSERT_EQ(v[2],f2);
};
TEST(DoNarysowania,WspolrzedneTrojkata)
{
    spDoNarysowania trojkat(make_shared<ProstyTrojkat>());
    assert_gl_3fv(&trojkat->wspolrzedneVrtx[trojkat->indeksyVertexow[0]*3],-1,0,0);
    assert_gl_3fv(&trojkat->wspolrzedneVrtx[trojkat->indeksyVertexow[1]*3],1,0,0);
    assert_gl_3fv(&trojkat->wspolrzedneVrtx[trojkat->indeksyVertexow[2]*3],0,1,0);
}
TEST(DoNarysowaniaTest,SzescianWspolrzedneVertexow)
{
    spDoNarysowania szescian(make_shared<Szescian>());
//    float wspolrzedne3f[] = {0,0,-1,};
    assert_gl_3fv(&szescian->wspolrzedneVrtx[szescian->indeksyVertexow[5]*3],1,1,1);
}
TEST(DoNarysowania,SzescianNormalne)
{
    spDoNarysowania szescian(make_shared<Szescian>());
    ASSERT_EQ(6,szescian->ileNormalnych);
    assert_gl_3fv(&szescian->normalne[0*3],0,-1,0);
    assert_gl_3fv(&szescian->normalne[1*3],0,0,1);
    assert_gl_3fv(&szescian->normalne[2*3],0,1,0);
}
TEST(DoNarysowania,TrojkatSchematNormalnych)
{
    spDoNarysowania trojkat(make_shared<ProstyTrojkat>());
    unsigned short schemat[] = {3};
    ASSERT_EQ(schemat[0],trojkat->schematNormalnych[0]);
}
TEST(DoNarysowania,SzescianSchematNormalnych)
{
    spDoNarysowania szescian(make_shared<Szescian>());
    unsigned short schemat[] = {4,2,2,4,2,2};
    
    for(int i = 0 ; i < szescian->ileNormalnych ; i++)ASSERT_EQ(schemat[i],szescian->schematNormalnych[i]);
}
TEST(DoNarysowania,SzescianPrzesunieciePoczatkowe)
{
    spDoNarysowania szescian(make_unique<Szescian>());
    float przes[] = {1.5,0.0,0.0};
    szescian->DoVertexowDodajWektor(przes);
    float wspolrzedneSpodziewane[] = {  
                    1.5,0,1,
                    2.5,0,1,
                    2.5,0,0,
                    1.5,0,0,
                    1.5,1,1,
                    2.5,1,1,
                    2.5,1,0,
                    1.5,1,0};
    for(short i = 0; i < szescian->ileVertexow ; i++)
        ASSERT_EQ(wspolrzedneSpodziewane[i],szescian->wspolrzedneVrtx[i]);
//    std::this_thread::sleep_for(10ms);
}


TEST(DoNarysowania,wKolejnosciWstaw_NieWidoczny)
{
    auto szescian(make_shared<Szescian>());
    auto szescian2(make_shared<Szescian>());
//    auto szescian = make_shared<DoNarysowania>();
//    auto szescian2 = make_shared<DoNarysowania>();
    szescian->NieWidoczny(true);
    szescian->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::RysujGeometriePowierzchnie,szescian->Polecenia()));
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::RysujGeometrieKrawedzie,szescian->Polecenia()));
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::RysujGeometriePunkty,szescian->Polecenia()));
    szescian2->PoleceniaWybierzIwstawWdobrejKolejnosci();
}
TEST(DoNarysowania,wKolejnosciWstaw_RysujGeometriePowierzchnie)
{
//    std::this_thread::sleep_for(2ms);
    spDoNarysowania szescian(make_shared<Szescian>());
    szescian->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::RysujGeometriePowierzchnie,szescian->Polecenia()));
}
TEST(DoNarysowania,wKolejnosciWstaw_PrzesuniecieNaPozycje_nieWstawia)
{
//    std::this_thread::sleep_for(2ms);
    spDoNarysowania szescian(make_shared<Szescian>());
    szescian->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::Przesun,szescian->Polecenia()));
}
TEST(DoNarysowania,wKolejnosciWstaw_PrzesuniecieNaPozycje)
{
//    std::this_thread::sleep_for(2ms);
    spDoNarysowania szescian(make_shared<Szescian>());
    //domyślnie powinien być na 0,0,0
    float poz[] = {1,0,0};
    szescian->UstawPrzesuniecie(poz);
    szescian->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::Przesun,szescian->Polecenia()));
}
TEST(DoNarysowania,JesliTransformacjaToJestPushIpopMatrix)
{
    auto rys(make_shared<DoNarysowania>());
    rys->przeznaczonyDoTransformacji = true;
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::PushMatrix,rys->Polecenia()));
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::PopMatrix,rys->Polecenia()));
}
TEST(DoNarysowania,NieMaPushIpopMatrix)
{
    auto rys(make_shared<DoNarysowania>());
    rys->przeznaczonyDoTransformacji = false;
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::PushMatrix,rys->Polecenia()));
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::PopMatrix,rys->Polecenia()));
}
TEST(DoNarysowania,ListyDzieciSaPuste)
{
    spDoNarysowania rys1(make_shared<DoNarysowania>());
    spDoNarysowania rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_TRUE(rys2->Polecenia().empty());
}
TEST(DoNarysowania,ListaZawieraPoleceniaDzieci)
{
    spDoNarysowania rys1(make_shared<DoNarysowania>());
    spDoNarysowania rys2(make_shared<DoNarysowania>());
    rys1->NieWidoczny(true);
    
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    //powinno być polecenie dziecka
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::RysujGeometriePowierzchnie,rys1->Polecenia()));
}
TEST(DoNarysowania,PrzyInicjacjiListaJestPusta)
{
    auto rys1(make_unique<DoNarysowania>());
    ASSERT_TRUE(rys1->Polecenia().empty());
}

TEST(DoNarysowania,PierwszeMojePolecenie_WlasciweIteratory)
{
    auto rys1(make_shared<DoNarysowania>());
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    auto adr1 = &(*(rys1->Polecenia().begin()));
    auto adr2 = &(*(rys1->itPierwszeMojePolecenie()));
    ASSERT_EQ(adr1,adr2);
}
TEST(DoNarysowania,OstatnieMojePolecenie_WlasciweIteratory)
{
    auto rys1(make_shared<DoNarysowania>());
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    auto adr1 = &(*(rys1->Polecenia().rbegin()));
    auto adr2 = &(*(rys1->itOstatnieMojePolecenie()));
    ASSERT_EQ(adr1,adr2);
}
TEST(DoNarysowania,WskaznikiPolecenDzieckaZawierajaJegoPolecenia)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    float przes[] = {1.0,1.3,-7.2};
    rys2->DodajPrzesuniecie(przes);//wydłuża listę
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    auto it2 = rys2->itPierwszeMojePolecenie();
    auto koniec2 = ++(rys2->itOstatnieMojePolecenie());
    auto adr2 = &(*rys2);
    while(it2 != koniec2)
    {
        auto polIgeom = *(it2++);
//        auto adr = &(*(polIgeom.geometria));gdy nie używano słabego
        auto adr = &(*(polIgeom.geometria.lock()));
        ASSERT_EQ(adr2,adr);
    }
}
TEST(DoNarysowania,AktualizujListe_NieJestJuzPusta)
{
    auto rys1(make_shared<DoNarysowania>());
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    rys1->AktualizujMojePolecenia();
    ASSERT_FALSE(rys1->Polecenia().empty());
}
TEST(DoNarysowania,WskaznikListyGlownejDzieci)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    auto rys3(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys2->DodajDziecko(rys3);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    ASSERT_TRUE(rys2->czyPoleceniaListaGlownaJestTaSama(&rys1->Polecenia()));
    ASSERT_TRUE(rys3->czyPoleceniaListaGlownaJestTaSama(&rys1->Polecenia()));
}
TEST(DoNarysowania,AktualizujListe_PoZmianieParametrowInnyRozmiar)
{
    auto rys1(make_shared<DoNarysowania>());
    float przes[] = {1.3,0,0};
    rys1->DodajPrzesuniecie(przes);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    auto rozmiar1(rys1->Polecenia().size());
    przes[0] = 0.0;
    rys1->UstawPrzesuniecie(przes);
    rys1->AktualizujMojePolecenia();
    auto rozmiar2(rys1->Polecenia().size());
    ASSERT_NE(rozmiar1,rozmiar2);
    
}
TEST(DoNarysowania,AktualizujListe_NieWymieniaZawartosciPozaSwoimZakresem)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    int ileDlaRys1Przed = 0;
    auto adresGeom1 = &(*rys1);
    for(auto& polIgeom : rys1->Polecenia()) 
        if(adresGeom1 == &*polIgeom.geometria.lock())
            ileDlaRys1Przed++;
    
    float przes[] = {1.3,0,0};
    rys2->DodajPrzesuniecie(przes);
    rys2->AktualizujMojePolecenia();
    int ileDlaRys1Po = 0;
    for(auto& polIgeom : rys1->Polecenia()) 
        if(adresGeom1 == &*polIgeom.geometria.lock())
            ileDlaRys1Po++;
    ASSERT_EQ(ileDlaRys1Przed,ileDlaRys1Po);
}
TEST(DoNarysowania,AktualizujListe_WymieniaZawartoscWswoimZakresie)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    int ileDlaRys2Przed = 0;
    auto adresGeom2 = &(*rys2);
    for(auto& polIgeom : rys1->Polecenia()) 
        if(adresGeom2 == &*polIgeom.geometria.lock())
            ileDlaRys2Przed++;
    
    float przes[] = {1.3,0,0};
    rys2->DodajPrzesuniecie(przes);
    rys2->AktualizujMojePolecenia();
    int ileDlaRys2Po = 0;
    for(auto& polIgeom : rys1->Polecenia()) 
        if(adresGeom2 == &*polIgeom.geometria.lock())
            ileDlaRys2Po++;
    ASSERT_NE(ileDlaRys2Przed,ileDlaRys2Po);
}
TEST(DoNarysowania,PoAktualizacjiPoczatkiIkonceZakresuWskazujaNaWlasciweMiejsca)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    auto rys3(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys2->DodajDziecko(rys3);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    /***/
    int a1 = rys1.use_count();
    int a2 = rys2.use_count();
//    int b = rys1.weak_count();
    /***/

    float przes[] = {1.3,0,0};
    rys2->DodajPrzesuniecie(przes);
    rys2->AktualizujMojePolecenia();
    int b1 = rys1.use_count();//**
    int b2 = rys2.use_count();//**
    
    auto adrGeom1 = &(*rys1);
    auto adrGeom2 = &(*rys2);
    auto adrGeom3 = &(*rys3);
    
    auto poczatekPolecen2 = rys2->itPierwszeMojePolecenie();
    auto koniecPolecen2 = rys2->itOstatnieMojePolecenie();
    
    auto adresGeomNaPoczatku2 = &*(*poczatekPolecen2--).geometria.lock();
    ASSERT_EQ(adresGeomNaPoczatku2,adrGeom2);
    
    auto adresGeomPrzedPoczatkiem2 = &*(*poczatekPolecen2).geometria.lock();
    ASSERT_EQ(adresGeomPrzedPoczatkiem2,adrGeom1);
    
    auto adresGeomNaKoncu2 = &*(*koniecPolecen2++).geometria.lock();
    ASSERT_EQ(adresGeomNaKoncu2,adrGeom2);
    
    auto adresGeomPoKoncu2 = &*(*koniecPolecen2).geometria.lock();
    ASSERT_EQ(adresGeomPoKoncu2,adrGeom1);
}
//NieMożnaAktualizować, jeśli moje pierwsze i ostatnie polecenie nie jest znane, użyć dodatkowej flagi, przyjęto, że to samo zanczenie ma sprawdzenie, czy znana jest główna lista
TEST(DoNarysowania,NieAktualizujePrzedZaistnieniemPodstawowejListy)
{
    auto rys(make_shared<DoNarysowania>());
    rys->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    rys->AktualizujMojePolecenia();
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::RysujGeometrie,rys->Polecenia()));
    ASSERT_EQ(1,rys->Polecenia().size());
}
TEST(DoNarysowania,DodanieKolejnegoDzieckaAktualizuje_ZmianaRozmiaru)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    int rozmiarPrzed = rys1->Polecenia().size();
    
    auto rys3(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys3);
    int rozmiarPo = rys1->Polecenia().size();
    
    ASSERT_NE(rozmiarPrzed,rozmiarPo);
}
TEST(DoNarysowania,DodanieKolejnegoDzieckaAktualizuje_dostepDoPolecenDodanego)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    int rozmiarPrzed = rys1->Polecenia().size();
    
    auto rys3(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys3);
    int rozmiarPo = rys1->Polecenia().size();
    
    ASSERT_NE(rozmiarPrzed,rozmiarPo);
    
    auto it3 = rys3->itPierwszeMojePolecenie();
    auto koniec3 = ++(rys3->itOstatnieMojePolecenie());
    auto adr3 = &(*rys3);
    while(it3 != koniec3)
    {
        auto polIgeom = *(it3++);
        auto adr = &(*(polIgeom.geometria.lock()));
        ASSERT_EQ(adr3,adr);
    }
}
TEST(DoNarysowania,DodanieKolejnegoDzieckaAktualizuje_WglownejLiscieSaPoleceniaDodanego)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    auto it = rys1->itPierwszeMojePolecenie();
    auto koniec = ++(rys1->itOstatnieMojePolecenie());
    
    auto rys3(make_shared<DoNarysowania>());
    auto adr3 = &(*rys3);
    
    bool result1 = false;
    bool result2 = false;
    while(it != koniec)
    {
        auto polIgeom = *(it++);
        auto adr = &(*(polIgeom.geometria.lock()));
        if(adr == adr3) result1 = true;
    }
    ASSERT_FALSE(result1);
    rys1->DodajDziecko(rys3);
    
    it = rys1->itPierwszeMojePolecenie();
    while(it != koniec)
    {
        auto polIgeom = *(it++);
        auto adr = &(*(polIgeom.geometria.lock()));
        if(adr == adr3) result2 = true;
    }
    ASSERT_TRUE(result2);
}
TEST(DoNarysowania,DodanieGlebiejDzieckaAktualizuje)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    auto it = rys1->itPierwszeMojePolecenie();
    auto koniec = ++(rys1->itOstatnieMojePolecenie());
    
    auto rys3(make_shared<DoNarysowania>());
    auto adr3 = &(*rys3);
    
    bool result1 = false;
    bool result2 = false;
    while(it != koniec)
    {
        auto polIgeom = *(it++);
        auto adr = &(*(polIgeom.geometria.lock()));
        if(adr == adr3) result1 = true;
    }
    ASSERT_FALSE(result1);
    rys2->DodajDziecko(rys3);
    
    it = rys1->itPierwszeMojePolecenie();
    while(it != koniec)
    {
        auto polIgeom = *(it++);
        auto adr = &(*(polIgeom.geometria.lock()));
        if(adr == adr3) result2 = true;
    }
    ASSERT_TRUE(result2);
}
TEST(DoNarysowania,OdjecieDzieckaAktualizuje)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    auto rys3(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys2->DodajDziecko(rys3);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    auto it = rys1->itPierwszeMojePolecenie();
    auto koniec = ++(rys1->itOstatnieMojePolecenie());
    
    auto adr3 = &(*rys3);
    
    bool result1 = false;
    bool result2 = false;
    while(it != koniec)
    {
        auto polIgeom = *(it++);
        auto adr = &(*(polIgeom.geometria.lock()));
        if(adr == adr3) result1 = true;
    }
    ASSERT_TRUE(result1);
    
    rys2->OdejmijDziecko(rys3);
    
    it = rys1->itPierwszeMojePolecenie();
    while(it != koniec)
    {
        auto polIgeom = *(it++);
        auto adr = &(*(polIgeom.geometria.lock()));
        if(adr == adr3) result2 = true;
    }
    ASSERT_FALSE(result2);
}
TEST(DoNarysowania,NadanieNazwyInt)
{
    upDoNarysowania rys = make_unique<DoNarysowania>();
    rys->setNazwa(24);
    Nazwa n(24);
    ASSERT_TRUE(n == rys->getNazwa());
}
TEST(DoNarysowania,NadanieNazwyStr)
{
    upDoNarysowania rys = make_unique<DoNarysowania>();
    rys->setNazwa("nazwa");
    Nazwa n("nazwa");
    ASSERT_TRUE(n == rys->getNazwa());
}
TEST(DoNarysowania,NieMaObrotu_NieDajeMultMatrix)
{
    auto rys = make_shared<DoNarysowaniaMock>();
    rys->JestObrot(false);
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::MultMatrix,rys->Polecenia()));
}
TEST(DoNarysowania,JestObrot_DajeMultMatrix)
{
    auto rys = make_shared<DoNarysowaniaMock>();
    rys->JestObrot(true);
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::MultMatrix,rys->Polecenia()));
}
TEST(DoNarysowania,PrzeznaczonyDoTransformacjiNieMaObrotu_DajeMultMatrix)
{
    auto rys = make_shared<DoNarysowaniaMock>();
    rys->JestObrot(false);
    rys->przeznaczonyDoTransformacji = true;
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::MultMatrix,rys->Polecenia()));
}
TEST(DoNarysowania,PrzekazPolecenia_ZrodloPuste)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    DoNarysowaniaDostepPrv dost1(*rys1);
    DoNarysowaniaDostepPrv dost2(*rys2);
    ASSERT_TRUE(dost2.PoleceniaAktywnePuste());
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    rys1->PrzekazPoleceniaIaktywujDla(rys2);
    ASSERT_TRUE(dost1.PoleceniaPuste());
}
TEST(DoNarysowania,PrzekazPolecenia_CelNiePusty)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    DoNarysowaniaDostepPrv dost1(*rys1);
    DoNarysowaniaDostepPrv dost2(*rys2);
    ASSERT_TRUE(dost2.PoleceniaAktywnePuste());
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    rys1->PrzekazPoleceniaIaktywujDla(rys2);
    ASSERT_FALSE(dost2.PoleceniaAktywnePuste());
}
TEST(DoNarysowania,WstawPolecenia_IloscOdwolan)
{
    auto rys1(make_shared<DoNarysowania>());
    rys1->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    ASSERT_EQ(1,rys1.use_count());//wstawione polecenie ma słaby wskaźnik
    auto rys2(make_shared<DoNarysowania>());
    rys1->PrzekazPoleceniaIaktywujDla(rys2);
    ASSERT_EQ(2,rys1.use_count());//jedno w tym zakresie a drugie w liście poleceń przekazanych do rys 2
}
TEST(DoNarysowania,Dzieci_IloscOdwolanPoAktywacji)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    rys2->WstawPolecenieNaKoncu(&PoleceniaRenderowania::RysujGeometrie);
    rys1->DodajDziecko(rys2);
    ASSERT_EQ(2,rys2.use_count());//wstawione polecenie ma słaby wskaźnik, ale drugie odwołanie jest w rys1 jako dziecko
    auto rys3(make_shared<DoNarysowania>());
    ASSERT_EQ(1,rys1.use_count());
    rys1->PrzekazPoleceniaIaktywujDla(rys3);
    ASSERT_EQ(2,rys1.use_count());
    
}
TEST(DoNarysowania,PoAktywacjiPolecenUdzieciListaGlownaJestNull)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    float poz[] = {1,0,0};
    rys2->UstawPrzesuniecie(poz);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    auto rys3(make_shared<DoNarysowania>());
    rys1->PrzekazPoleceniaIaktywujDla(rys3);
    
}
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
TEST(AktualizujListe,ResetListy_wywolujeTezDlaDzieci)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowaniaMock>());
    rys1->DodajDziecko(rys2);
    float poz[] = {1,0,0};
    rys2->UstawPrzesuniecie(poz);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    rys1->ListePolecenResetuj();
    ASSERT_TRUE(rys2->listePolecenResetujIsUsed);
}
TEST(AktualizujListe,PrzekazPoleceniaIaktywujDlaWywolujeResetListy)
{
    auto rys1(make_shared<DoNarysowaniaMock>());
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    auto rys3(make_shared<DoNarysowania>());
    rys1->PrzekazPoleceniaIaktywujDla(rys3);
    ASSERT_TRUE(rys1->listePolecenResetujIsUsed);
}
//zakładam, że przekazanie poleceń nie musi automatycznie wywolać przeliczenia
//okaże się to po włączeniu wszystkich testów

//PushName
//KorektaOsiObrotu
//ObrocWgPunktu
//LoadName
//+GeometriaPowierzchnie
//GeometriaKrawedzie
//GeometriaPunkty
//+NieRysujGeometrii
//PopName

//mechanizm powiadomiania o wprowadzeniu zmiany, 
//powiadamianie o zmianie wymusza przebudowanie listy polecen renderowania