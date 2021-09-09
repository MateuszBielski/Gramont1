#include "donarysowania.h"
#include "../Process/renderowanie.h"

l_PolecenieIgeometria DoNarysowania::Polecenia()
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
    if(jestTransformacja)
    mojePolecenia.push_back({&PoleceniaRenderowania::PrzesuniecieNaPozycje,WskaznikNaMnie()});
    
    if(!nieWidoczny)mojePolecenia.push_back({&PoleceniaRenderowania::RysujGeometriePowierzchnie,WskaznikNaMnie()});
    
//    mojePolecenia.push_back(&PoleceniaRenderowania::PoGeometrii);
//    mojePolecenia.push_back(&T::PrzedGeometria);
//    mojePolecenia.push_back(&T::RysujGeometrie);
//    mojePolecenia.push_back(&T::PoGeometrii);
}



//dla linkera
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<PoleceniaRenderowania>();
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<Renderowanie>();
