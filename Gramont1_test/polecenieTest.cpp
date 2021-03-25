#include <gtest/gtest.h>
#include <GL/gl.h>
#include "../src/Polecenie/obrot.h"
//#include "../src/Polecenie/kolejkapolecen.h"
//#include "../src/Process/zarzadzaniemodelami.h"
#include "zarzadzaniemodelamimock.h"
//#include "../../gtk_GL_interfaces_tdd/funkcje/FunkcjePomocnicze.h"

TEST(PolecenieTest,UtworzenieObrotZParametremObslugujacy)
{
    spZarzadzanieModelami zarzadzanie= make_shared<ZarzadzanieModelami>();
    
    spPolecenie  polecenie = make_shared<Obrot<ZarzadzanieModelami>>(zarzadzanie);
//    polecenie->Wykonaj();
        ASSERT_NE(nullptr,polecenie);
    
}
TEST(PolecenieTest,obrotWykonajWywolujeDoTransformacji)
{
    spZarzadzanieModelami zarzadzanie= make_shared<ZarzadzanieModelamiMock>();
    spPolecenie  polecenie = make_shared<Obrot<ZarzadzanieModelami>>(zarzadzanie);
    
    polecenie->Wykonaj();
    ASSERT_TRUE(zarzadzanie->doTransformacjiUsed);
}