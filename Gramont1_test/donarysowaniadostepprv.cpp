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

void DoNarysowaniaDostepPrv::ZakonczonaAktualizacja(bool f)
{
    rys.aktualizacjaUkonczona = f;
}

bool DoNarysowaniaDostepPrv::ZakonczonaAktualizacja()
{
    return rys.aktualizacjaUkonczona;
}

void DoNarysowaniaDostepPrv::ListaGlownaSkopiowana(bool f)
{
    rys.listaGlownaSkopiowana = f;
}

bool DoNarysowaniaDostepPrv::ListaGlownaSkopiowana()
{   
    return rys.listaGlownaSkopiowana;
}
mutex& DoNarysowaniaDostepPrv::getMutex()
{
//	return mutDostep;
    return rys.mut;
}
bool DoNarysowaniaDostepPrv::PoleceniaAktywnePuste()
{
	return rys.mojePoleceniaAktywne.empty();
}
bool DoNarysowaniaDostepPrv::PoleceniaPuste()
{
	return rys.mojePolecenia.empty();
}
bool DoNarysowaniaDostepPrv::ListaGlownaUstawiona()
{	
	return rys.poleceniaListaGlowna;
}
