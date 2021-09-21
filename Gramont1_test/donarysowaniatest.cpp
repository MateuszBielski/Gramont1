#include <gtest/gtest.h>
//#include <GL/gl.h>
#include "../src/Shared/szescian.h"
#include "../src/Shared/prostytrojkat.h"
#include "../src/Process/renderowanie.h"

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
template<typename AdrFun, typename Polecenia>
bool CzyZawiera(AdrFun adr,Polecenia polecenia)
{
    bool result = false;
    for(auto& polIgeom : polecenia)
    {
        if (polIgeom.polecenie == adr)
        {
            result = true;
            break;
        }
    }
    return result;
}
TEST(DoNarysowania,wKolejnosciWstaw_NieWidoczny)
{
    spDoNarysowania szescian(make_shared<Szescian>());
    szescian->NieWidoczny(true);
    szescian->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::RysujGeometriePowierzchnie,szescian->Polecenia()));
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::RysujGeometrieKrawedzie,szescian->Polecenia()));
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::RysujGeometriePunkty,szescian->Polecenia()));
}
TEST(DoNarysowania,wKolejnosciWstaw_RysujGeometriePowierzchnie)
{
    spDoNarysowania szescian(make_shared<Szescian>());
    szescian->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::RysujGeometriePowierzchnie,szescian->Polecenia()));
}
TEST(DoNarysowania,wKolejnosciWstaw_PrzesuniecieNaPozycje_nieWstawia)
{
    spDoNarysowania szescian(make_shared<Szescian>());
    szescian->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::Przesun,szescian->Polecenia()));
}
TEST(DoNarysowania,wKolejnosciWstaw_PrzesuniecieNaPozycje)
{
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
    rys->jestTransformacja = true;
    rys->PoleceniaWybierzIwstawWdobrejKolejnosci();
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::PushMatrix,rys->Polecenia()));
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::PopMatrix,rys->Polecenia()));
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
        auto adr = &(*(polIgeom.geometria));
        ASSERT_EQ(adr2,adr);
    }
}
TEST(DoNarysowania,AktualizujListe_NieJestJuzPusta)
{
    auto rys1(make_shared<DoNarysowania>());
    rys1->AktualizujMojePolecenia();
    ASSERT_FALSE(rys1->Polecenia().empty());
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
        if(adresGeom1 == &*polIgeom.geometria)
            ileDlaRys1Przed++;
    
    float przes[] = {1.3,0,0};
    rys2->DodajPrzesuniecie(przes);
    rys2->AktualizujMojePolecenia();
    int ileDlaRys1Po = 0;
    for(auto& polIgeom : rys1->Polecenia()) 
        if(adresGeom1 == &*polIgeom.geometria)
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
        if(adresGeom2 == &*polIgeom.geometria)
            ileDlaRys2Przed++;
    
    float przes[] = {1.3,0,0};
    rys2->DodajPrzesuniecie(przes);
    rys2->AktualizujMojePolecenia();
    int ileDlaRys2Po = 0;
    for(auto& polIgeom : rys1->Polecenia()) 
        if(adresGeom2 == &*polIgeom.geometria)
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
    for(auto polecenie : rys1->Polecenia())
    {
        cout<<&*polecenie.geometria<<endl;
    }
    float przes[] = {1.3,0,0};
    rys2->DodajPrzesuniecie(przes);
    rys2->AktualizujMojePolecenia();
    auto adrGeom1 = &(*rys1);
    auto adrGeom2 = &(*rys2);
    auto adrGeom3 = &(*rys3);
    
    for(auto polecenie : rys1->Polecenia())
    {
        cout<<&*polecenie.geometria<<endl;
    }
    
    auto poczatekPolecen2 = rys2->itPierwszeMojePolecenie();
    auto koniecPolecen2 = rys2->itOstatnieMojePolecenie();
    
    auto adresGeomNaPoczatku2 = &*(*poczatekPolecen2--).geometria;
    ASSERT_EQ(adresGeomNaPoczatku2,adrGeom2);
    
    auto adresGeomPrzedPoczatkiem2 = &*(*poczatekPolecen2).geometria;
    ASSERT_EQ(adresGeomPrzedPoczatkiem2,adrGeom1);
    
    
    auto adresGeomNaKoncu2 = &*(*koniecPolecen2++).geometria;
    ASSERT_EQ(adresGeomNaKoncu2,adrGeom2);
    
    
    auto adresGeomPoKoncu2 = &*(*koniecPolecen2).geometria;
    ASSERT_EQ(adresGeomPoKoncu2,adrGeom1);
}

//NieMożnaAktualizować, jeśli moje pierwsze i ostatnie polecenie nie jest znane, użyć dodatkowej flagi
//dwa razy aktualizować, czy nie robią się problemy z listami
/*
TEST(DoNarysowania,DodanieKolejnegoDzieckaAktualizuje)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    auto rys3(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys3);
    
    auto it3 = rys3->itPierwszeMojePolecenie();
    auto koniec3 = ++(rys3->itOstatnieMojePolecenie());
    auto adr3 = &(*rys3);
    while(it3 != koniec3)
    {
        auto polIgeom = *(it3++);
        auto adr = &(*(polIgeom.geometria));
        ASSERT_EQ(adr3,adr);
    }
}
TEST(DoNarysowania,DodanieDzieckaGlebiejAktualizuje)
{
    auto rys1(make_shared<DoNarysowania>());
    auto rys2(make_shared<DoNarysowania>());
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    auto rys3(make_shared<DoNarysowania>());
    rys2->DodajDziecko(rys3);
    
    auto it3 = rys3->itPierwszeMojePolecenie();
    auto koniec3 = ++(rys3->itOstatnieMojePolecenie());
    auto adr3 = &(*rys3);
    while(it3 != koniec3)
    {
        auto polIgeom = *(it3++);
        auto adr = &(*(polIgeom.geometria));
        ASSERT_EQ(adr3,adr);
    }
}
*/
/*
TEST(DoNarysowania,DodanieDziecka_zmianaRozmiaruListyPolecen)
{
    spDoNarysowania rys1(make_shared<DoNarysowania>());
    spDoNarysowania rys2(make_shared<DoNarysowania>());
    
    rys1->DodajDziecko(rys2);
    rys1->PoleceniaWybierzIwstawWdobrejKolejnosci();
    auto rozmiarPrzedZmiana = rys1->Polecenia().size();
    
    spDoNarysowania rys3(make_shared<DoNarysowania>());
    rys2->DodajDziecko(rys3);
//    rys2->PoleceniaWybierzIwstawWdobrejKolejnosci();
    auto rozmiarPoZmianie = rys1->Polecenia().size();
    ASSERT_TRUE(rozmiarPrzedZmiana != rozmiarPoZmianie);
}
*/
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