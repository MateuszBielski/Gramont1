#include <gtest/gtest.h>
#include "../src/Process/obliczeniadlamodeli.h"
#include "../src/Shared/prostytrojkat.h"

TEST(Obliczenia,UtrwalTransformacje_MacierzObrotuZmieniaWartosciWertexow)
{
    auto kopiuj9f = [](float *src, float * dest ){
                    for(short i = 0 ; i < 9 ; i++)
                    dest[i] = src[i];
                    };
    spDoNarysowania troj= make_shared<ProstyTrojkat>();
    float m[] = {0.7544, -0.3364, 0.5637, 0.0000, 0.1320, 0.9189, 0.3717, 0.0000, -0.6430, -0.2061, 0.7376, 0.0000, 0.0000, 0.0000, 0.0000, 1.0000};
    //powyżej prawidłowege wartości przykładowego obrotu generowane funkcją 
    //WypisywanieWartosci::MacierzObrotuDoTransformacji(ZarzadzanieModelami* zarzadzanie)
//    troj->MacierzObrotu(m);
    ObliczeniaDlaModeli obl;
    
    float vrtx0[9], vrtx1[9];
    kopiuj9f(troj->wspolrzedneVrtx, vrtx0);
    obl.UtrwalTransformacje(troj);
    kopiuj9f(troj->wspolrzedneVrtx, vrtx1);
    bool zmiana = false;
    for(short i = 0 ; i < 9 ; i++)
    {
        if(vrtx0[i] != vrtx1[i]) zmiana = true;
    }
    ASSERT_TRUE(zmiana);
}
//UtrwalObrot_MacierzObrotuZnowJednostkowa
