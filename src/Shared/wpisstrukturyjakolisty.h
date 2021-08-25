#ifndef WpisStrukturyJakoListy_H
#define WpisStrukturyJakoListy_H
//#include <iostream>
//#include <memory>

enum class RodzajAkcji: int{wejscie,obok,powrot};

template<typename T>
struct WpisStrukturyJakoListy
{
    RodzajAkcji akcjaPo;
    T wezel;    
};
#endif // WpisStrukturyJakoListy_H
