#include <gtest/gtest.h>
//#include <GL/gl.h>
#include "../src/Shared/grupowalne.h"
//#include "../src/Shared/prostytrojkat.h"

TEST(Grupowanie,DodanieDziecka)
{
    spGrupowalne grupa(make_shared<Grupowalne>());
    spGrupowalne dziecko(make_shared<Grupowalne>());
    grupa->DodajDziecko(dziecko);
    ASSERT_EQ(1,grupa->IleDzieci());
}
TEST(Grupowanie,OdjecieDziecka)
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
TEST(Grupowanie,CzyNieJestDzieckiem)
{
    spGrupowalne grupa(make_shared<Grupowalne>());
    spGrupowalne dziecko1(make_shared<Grupowalne>());
    
    ASSERT_FALSE(grupa->CzyJestMoimDzieckiem(dziecko1));
}
TEST(Grupowanie,CzyJestDzieckiem)
{
    spGrupowalne grupa(make_shared<Grupowalne>());
    spGrupowalne dziecko(make_shared<Grupowalne>());
    grupa->DodajDziecko(dziecko);
    ASSERT_TRUE(grupa->CzyJestMoimDzieckiem(dziecko));
}

TEST (Grupowanie,OdjecieDzieckaNieDodanego)
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


