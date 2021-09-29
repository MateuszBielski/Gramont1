#include "donarysowania.h"
#include "../Process/renderowanie.h"

l_PolecenieIgeometria& DoNarysowania::Polecenia()
{
    return mojePolecenia;
}
void DoNarysowania::WstawPolecenieNaKoncu(PtrMemRend_Geom polecenie)
{
    PolecenieIgeometria polIGeom = {polecenie,WskaznikNaMnie()};
    mojePolecenia.push_back(polIGeom);
}
void DoNarysowania::NieWidoczny(bool flaga)
{  
    nieWidoczny = flaga;
}
void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci()
{
    if(!poleceniaListaGlowna)poleceniaListaGlowna = &mojePolecenia;
    if(jestTransformacja)
    {
        mojePolecenia.push_back({&PoleceniaRenderowania::PushMatrix,WskaznikNaMnie()});
        mojePolecenia.push_back({&PoleceniaRenderowania::Przesun,WskaznikNaMnie()});
    }
    if(!nieWidoczny)mojePolecenia.push_back({&PoleceniaRenderowania::RysujGeometriePowierzchnie,WskaznikNaMnie()});
    for(auto& dziecko : dzieci)
    {
        dziecko->poleceniaListaGlowna = poleceniaListaGlowna;
        dziecko->PoleceniaWybierzIwstawWdobrejKolejnosci();
        //zakładam, że iteratory dziecka: mojePierwsze i ostatnie polecenie przeniesione zostaną teraz do 
        //listy głównej
        mojePolecenia.splice(mojePolecenia.end(),dziecko->mojePolecenia);
    }
    mojePolecenia.push_back({&PoleceniaRenderowania::PopMatrix,WskaznikNaMnie()});
    
    pierwszeMojePolecenie = mojePolecenia.begin();
    ostatnieMojePolecenie = --mojePolecenia.end();
}
void DoNarysowania::AktualizujMojePolecenia()
{
	if(!poleceniaListaGlowna)return;
    mojePolecenia.clear();
    auto pierwszeWymienianegoZakresu = pierwszeMojePolecenie;
    auto ostatnieWymienianegoZakresu = ostatnieMojePolecenie;
    
    PoleceniaWybierzIwstawWdobrejKolejnosci();

    bool czyMojaListaNieJestGlowna = &mojePolecenia != poleceniaListaGlowna;
    if(poleceniaListaGlowna && czyMojaListaNieJestGlowna )
    {
        auto odleglosc = distance(pierwszeWymienianegoZakresu,ostatnieWymienianegoZakresu);//-
        auto przedTymWstawiamyNowaZawartosc = poleceniaListaGlowna->
        erase(pierwszeWymienianegoZakresu,++ostatnieWymienianegoZakresu);
        poleceniaListaGlowna->splice(przedTymWstawiamyNowaZawartosc,mojePolecenia);
    }
}
l_PolecenieIgeometria::iterator DoNarysowania::itPierwszeMojePolecenie()
{
	return pierwszeMojePolecenie;
}
l_PolecenieIgeometria::iterator DoNarysowania::itOstatnieMojePolecenie()
{
	return ostatnieMojePolecenie;
}
void DoNarysowania::PodczasDodajDziecko()
{
    AktualizujMojePolecenia();
}
void DoNarysowania::PodczasOdejmijDziecko()
{
}
bool DoNarysowania::czyPoleceniaListaGlownaJestTaSama(l_PolecenieIgeometria* wsk)
{
//	return false;
    
    return poleceniaListaGlowna == wsk;
}




//dla linkera
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<PoleceniaRenderowania>();
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<Renderowanie>();
