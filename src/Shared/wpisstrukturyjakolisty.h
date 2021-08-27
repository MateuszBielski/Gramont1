#ifndef WpisStrukturyJakoListy_H
#define WpisStrukturyJakoListy_H
//#include <iostream>
//#include <memory>

enum class RodzajAkcji;

template<typename T>
struct WpisStrukturyJakoListy
{
    RodzajAkcji akcjaPrzed;
    RodzajAkcji akcjaPo;
    T wezel;    
};
#endif // WpisStrukturyJakoListy_H
