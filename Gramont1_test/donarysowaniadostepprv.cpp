#include "donarysowaniadostepprv.h"

DoNarysowaniaDostepPrv::~DoNarysowaniaDostepPrv()
{

}

DoNarysowaniaDostepPrv::DoNarysowaniaDostepPrv(DoNarysowania& r):rys(r)
{
}

void DoNarysowaniaDostepPrv::ListaGlownaOdlaczona(bool f)
{
    rys.listaGlownaOdlaczona = f;
}

bool DoNarysowaniaDostepPrv::ListaGlownaOdlaczona()
{
    return rys.listaGlownaOdlaczona;
}
