#include "wypisywaniewartosci.h"
#include "FunkcjeIstruktury.h"



void WypisywanieWartosci::MacierzObrotuDoTransformacji(ZarzadzanieModelami* zarzadzanie)
{
    const float * m = zarzadzanie->DoTransformacji()->MacierzObrotu();
    short i = 0;
    string res("{");
    for(i ; i < 15 ; i++)
        {
            res += ToString(m[i],4) + ", ";
        }
    cout<<res<<ToString(m[15],4)<<"}"<<endl;
}
