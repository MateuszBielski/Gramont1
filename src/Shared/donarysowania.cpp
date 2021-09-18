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
//    mojePolecenia.push_back(&PoleceniaRenderowania::PrzedGeometria);

//    poczatekMoichPolecen = --mojePolecenia.end();
    
    if(jestTransformacja)
    mojePolecenia.push_back({&PoleceniaRenderowania::Przesun,WskaznikNaMnie()});
    if(!nieWidoczny)mojePolecenia.push_back({&PoleceniaRenderowania::RysujGeometriePowierzchnie,WskaznikNaMnie()});
    for(auto& dziecko : dzieci)
    {
        dziecko->PoleceniaWybierzIwstawWdobrejKolejnosci();
        mojePolecenia.splice(mojePolecenia.end(),dziecko->mojePolecenia);
    }
    int size = mojePolecenia.size();
    pierwszeMojePolecenie = mojePolecenia.begin();
    ostatnieMojePolecenie = --mojePolecenia.end();
}
void DoNarysowania::AktualizujMojePolecenia()
{
	mojePolecenia.clear();
    PoleceniaWybierzIwstawWdobrejKolejnosci();
}
l_PolecenieIgeometria::iterator DoNarysowania::itPierwszeMojePolecenie()
{
	return pierwszeMojePolecenie;
}
l_PolecenieIgeometria::iterator DoNarysowania::itOstatnieMojePolecenie()
{
	return ostatnieMojePolecenie;
}




//dla linkera
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<PoleceniaRenderowania>();
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<Renderowanie>();
