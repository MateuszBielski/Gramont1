#include "wypisywaniewartosci.h"



void WypisywanieWartosci::MacierzObrotuDoTransformacji(ZarzadzanieModelami* zarzadzanie)
{
    const float * m = zarzadzanie->DoTransformacji()->MacierzObrotu();
    short i = 0;
    string res("{");
    for(i ; i < 15 ; i ++)res += to_string(m[i]) + ",";
    cout<<res<<m[15]<<"}"<<endl;
}
