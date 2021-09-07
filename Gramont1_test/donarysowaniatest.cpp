#include <gtest/gtest.h>
//#include <GL/gl.h>
#include "../src/Shared/szescian.h"
#include "../src/Shared/prostytrojkat.h"

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
    for(auto& polecenie : polecenia)
    {
        if (polecenie == adr)
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
    //domyślnie powinien być na 0,0,0
    szescian->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    ASSERT_FALSE(CzyZawiera(&PoleceniaRenderowania::PrzesuniecieNaPozycje,szescian->Polecenia()));
}
TEST(DoNarysowania,wKolejnosciWstaw_PrzesuniecieNaPozycje)
{
    spDoNarysowania szescian(make_shared<Szescian>());
    //domyślnie powinien być na 0,0,0
    float poz[] = {1,0,0};
    szescian->UstawPozycje(poz);
    szescian->PoleceniaWybierzIwstawWdobrejKolejnosci();
    
    ASSERT_TRUE(CzyZawiera(&PoleceniaRenderowania::PrzesuniecieNaPozycje,szescian->Polecenia()));
}


//PushName
//PushMatrix
//PrzesuniecieNaPozycje
//KorektaOsiObrotu
//ObrocWgPunktu
//LoadName
//+GeometriaPowierzchnie
//GeometriaKrawedzie
//GeometriaPunkty
//+NieRysujGeometrii
//PopName
//PopMatrix
//mechanizm powiadomiania o wprowadzeniu zmiany, 
//powiadamianie o zmianie wymusza przebudowanie listy polecen renderowania