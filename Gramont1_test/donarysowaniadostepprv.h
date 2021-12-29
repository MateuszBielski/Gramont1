#ifndef DoNarysowaniaDostepPrv_H
#define DoNarysowaniaDostepPrv_H
#include <iostream>
#include <mutex>
#include "../src/Shared/donarysowania.h"

using namespace std;

class DoNarysowaniaDostepPrv
{
  DoNarysowania& rys;
  mutable std::mutex mutDostep;
  
public:
    DoNarysowaniaDostepPrv(DoNarysowania& );
    ~DoNarysowaniaDostepPrv();
    void ListaGlownaOdlaczona(bool);
    bool ListaGlownaOdlaczona();
    void ZakonczonaAktualizacja(bool);
    bool ZakonczonaAktualizacja();
    void ListaGlownaSkopiowana(bool);
    bool ListaGlownaSkopiowana();
    mutex& getMutex();
    


        
};
#endif // DoNarysowaniaDostepPrv_H
