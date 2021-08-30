#include <gtest/gtest.h>
#include "../src/Shared/grupowalne.h"
//#include "../src/Shared/prostytrojkat.h"
#include "../src/Shared/rodzajakcji.cpp"

TEST(Grupowalne,DodanieDziecka)
{
    spGrupowalne grupa(make_shared<Grupowalne>());
    spGrupowalne dziecko(make_shared<Grupowalne>());
    grupa->DodajDziecko(dziecko);
    ASSERT_EQ(1,grupa->IleDzieci());
}
TEST(Grupowalne,OdjecieDziecka)
{
    spGrupowalne grupa(make_shared<Grupowalne>());
    spGrupowalne dziecko1(make_shared<Grupowalne>());
    spGrupowalne dziecko2(make_shared<Grupowalne>());
    spGrupowalne dziecko3(make_shared<Grupowalne>());
    spGrupowalne dziecko4(make_shared<Grupowalne>());
    grupa->DodajDziecko(dziecko1);
    grupa->DodajDziecko(dziecko2);
    grupa->DodajDziecko(dziecko3);
    grupa->DodajDziecko(dziecko4);
    ASSERT_EQ(4,grupa->IleDzieci());
    ASSERT_TRUE(grupa->OdejmijDziecko(dziecko2));
    ASSERT_EQ(3,grupa->IleDzieci());
}
TEST(Grupowalne,CzyNieJestDzieckiem)
{
    spGrupowalne grupa(make_shared<Grupowalne>());
    spGrupowalne dziecko1(make_shared<Grupowalne>());
    
    ASSERT_FALSE(grupa->CzyJestMoimDzieckiem(dziecko1));
}
TEST(Grupowalne,CzyJestDzieckiem)
{
    spGrupowalne grupa(make_shared<Grupowalne>());
    spGrupowalne dziecko(make_shared<Grupowalne>());
    grupa->DodajDziecko(dziecko);
    ASSERT_TRUE(grupa->CzyJestMoimDzieckiem(dziecko));
}

TEST (Grupowalne,OdjecieDzieckaNieDodanego)
{
    spGrupowalne grupa(make_shared<Grupowalne>());
    spGrupowalne dziecko1(make_shared<Grupowalne>());
    spGrupowalne dziecko2(make_shared<Grupowalne>());
    spGrupowalne dziecko3(make_shared<Grupowalne>());
    spGrupowalne dziecko4(make_shared<Grupowalne>());
    grupa->DodajDziecko(dziecko1);
    grupa->DodajDziecko(dziecko2);
    grupa->DodajDziecko(dziecko4);
    ASSERT_FALSE(grupa->OdejmijDziecko(dziecko3));
}

TEST (Grupowalne,NieMoznaDoDacDoSiebie)
{
    spGrupowalne g(make_shared<Grupowalne>());
    g->DodajDziecko(g);
    ASSERT_EQ(0,g->IleDzieci());
}
TEST(Grupowalne,PoOdjeciuNieMaRodzica)
{
    spGrupowalne g1(make_shared<Grupowalne>());
    spGrupowalne g2(make_shared<Grupowalne>());
    g1->DodajDziecko(g2);
    g1->OdejmijDziecko(g2);
    ASSERT_EQ(nullptr,g2->Rodzic());
}
TEST(Grupowalne,DoKogoNaleze_PoDodaniu)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    spGrupowalne w2(make_shared<Grupowalne>());
    
    w1->DodajDziecko(w2);
    
    ASSERT_TRUE(w1.get() == w2->Rodzic().get());
}
TEST(Grupowalne,PrzeniesienieDoInnegoWezla)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    spGrupowalne w2(make_shared<Grupowalne>());
    spGrupowalne w3(make_shared<Grupowalne>());
    
    w1->DodajDziecko(w3);
    w2->DodajDziecko(w3);
    ASSERT_EQ(0,w1->IleDzieci());
    ASSERT_TRUE(w2.get() == w3->Rodzic().get());
}
TEST (Grupowalne,StrukturaJakoLista_liczbaObiektow)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    spGrupowalne w1_1(make_shared<Grupowalne>());
    spGrupowalne w1_2(make_shared<Grupowalne>());
    spGrupowalne w1_3(make_shared<Grupowalne>());
    spGrupowalne w1_2_1(make_shared<Grupowalne>());
    spGrupowalne w1_2_2(make_shared<Grupowalne>());
    
    w1_2->DodajDziecko(w1_2_1);
    w1_2->DodajDziecko(w1_2_2);
    
    w1->DodajDziecko(w1_1);
    w1->DodajDziecko(w1_2);
    w1->DodajDziecko(w1_3);
    
    ASSERT_EQ(6,w1->StrukturaJakoLista_Wezly_dlugosc());
}
TEST (Grupowalne,StrukturaJakoLista_liczbaObiektowPoOdjeciu)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    spGrupowalne w1_1(make_shared<Grupowalne>());
    spGrupowalne w1_2(make_shared<Grupowalne>());
    
    spGrupowalne w1_2_1(make_shared<Grupowalne>());
    spGrupowalne w1_2_2(make_shared<Grupowalne>());
     
    w1->DodajDziecko(w1_1);
    w1->DodajDziecko(w1_2);
    
    w1_2->DodajDziecko(w1_2_1);
    w1_2->DodajDziecko(w1_2_2);
    
    ASSERT_EQ(5,w1->StrukturaJakoLista_Wezly_dlugosc());
    w1->OdejmijDziecko(w1_2);
    ASSERT_EQ(2,w1->StrukturaJakoLista_Wezly_dlugosc());
}
TEST (Grupowalne,StrukturaJakoLista_1wezel)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    auto iter = w1->StrukturaJakoLista_Wezly().begin();
    
    ASSERT_TRUE(w1.get() == (*iter).get());
}
TEST (Grupowalne,StrukturaJakoLista_kolejnoscObiektow_2)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    spGrupowalne w1_1(make_shared<Grupowalne>());
    w1->DodajDziecko(w1_1);
    auto iter = w1->StrukturaJakoLista_Wezly().begin();
    
    ASSERT_TRUE(w1.get() == (*iter++).get());
    ASSERT_TRUE(w1_1.get() == (*iter).get());
}

TEST (Grupowalne,StrukturaJakoLista_kolejnoscObiektow_6)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    spGrupowalne w1_1(make_shared<Grupowalne>());
    spGrupowalne w1_2(make_shared<Grupowalne>());
    spGrupowalne w1_3(make_shared<Grupowalne>());
    spGrupowalne w1_2_1(make_shared<Grupowalne>());
    spGrupowalne w1_2_2(make_shared<Grupowalne>());
    
    w1_2->DodajDziecko(w1_2_1);
    w1_2->DodajDziecko(w1_2_2);
    
    w1->DodajDziecko(w1_1);
    w1->DodajDziecko(w1_2);
    w1->DodajDziecko(w1_3);
    
    auto iter = w1->StrukturaJakoLista_Wezly().begin();
    
    ASSERT_TRUE(w1.get() == (*iter++).get());
    ASSERT_TRUE(w1_1.get() == (*iter++).get());
    ASSERT_TRUE(w1_2.get() == (*iter++).get());
    ASSERT_TRUE(w1_2_1.get() == (*iter++).get());
    ASSERT_TRUE(w1_2_2.get() == (*iter++).get());
    ASSERT_TRUE(w1_3.get() == (*iter++).get());
    
}
TEST(Grupowalne,StrukturaJakoLista_rodzajAkcji_1wezel)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    auto iter = w1->StrukturaJakoLista_RodzajAkcji().begin();
    ASSERT_EQ(RodzajAkcji::wezel,*iter);
}
TEST(Grupowalne,StrukturaJakoLista_rodzajAkcji_rodzic_dziecko)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    spGrupowalne w1_1(make_shared<Grupowalne>());
    w1->DodajDziecko(w1_1);
    
    auto iter = w1->StrukturaJakoLista_RodzajAkcji().begin();
    
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::wejscie,*iter++);
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::powrot,*iter++);
}

TEST(Grupowalne,StrukturaJakoLista_rodzic_2dzieci)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    spGrupowalne w1_1(make_shared<Grupowalne>());
    spGrupowalne w1_2(make_shared<Grupowalne>());
    w1->DodajDziecko(w1_1);
    w1->DodajDziecko(w1_2);
    
    auto iter = w1->StrukturaJakoLista_RodzajAkcji().begin();
    
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::wejscie,*iter++);
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::powrot,*iter++);
}

TEST (Grupowalne,StrukturaJakoLista_kolejnoscAkcji_6)
{
    spGrupowalne w1(make_shared<Grupowalne>());
    spGrupowalne w1_1(make_shared<Grupowalne>());
    spGrupowalne w1_2(make_shared<Grupowalne>());
    spGrupowalne w1_3(make_shared<Grupowalne>());
    spGrupowalne w1_2_1(make_shared<Grupowalne>());
    spGrupowalne w1_2_2(make_shared<Grupowalne>());
    
    w1_2->DodajDziecko(w1_2_1);
    w1_2->DodajDziecko(w1_2_2);
    
    w1->DodajDziecko(w1_1);
    w1->DodajDziecko(w1_2);
    w1->DodajDziecko(w1_3);
    
    auto iter = w1->StrukturaJakoLista_RodzajAkcji().begin();
    
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::wejscie,*iter++);
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::wejscie,*iter++);
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::powrot,*iter++);
    ASSERT_EQ(RodzajAkcji::wezel,*iter++);
    ASSERT_EQ(RodzajAkcji::powrot,*iter++);
}
