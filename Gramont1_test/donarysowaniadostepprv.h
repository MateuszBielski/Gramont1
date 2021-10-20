#ifndef DoNarysowaniaDostepPrv_H
#define DoNarysowaniaDostepPrv_H
#include <iostream>
#include "../src/Shared/donarysowania.h"

using namespace std;

class DoNarysowaniaDostepPrv
{
  DoNarysowania& rys;
public:
    DoNarysowaniaDostepPrv(DoNarysowania& );
    ~DoNarysowaniaDostepPrv();
    void ListaGlownaOdlaczona(bool);
    bool ListaGlownaOdlaczona();


        
};
#endif // DoNarysowaniaDostepPrv_H
