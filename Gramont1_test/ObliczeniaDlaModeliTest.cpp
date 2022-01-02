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
    float m[16];//dopisać generowane wartości
    troj->MacierzObrotu(m);
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
