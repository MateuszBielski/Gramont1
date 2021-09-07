#include "donarysowania.h"
#include "../Process/renderowanie.h"

l_PtrMemRend_Geom DoNarysowania::Polecenia()
{
    return mojePolecenia;
}
void DoNarysowania::WstawPolecenieNaKoncu(PtrMemRend_Geom polecenie)
{
    mojePolecenia.push_back(polecenie);
}
void DoNarysowania::NieWidoczny(bool flaga)
{  
    nieWidoczny = flaga;
}
void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci()
{
//    mojePolecenia.push_back(&PoleceniaRenderowania::PrzedGeometria);
    if(Pozycja()[0] || Pozycja()[1] || Pozycja()[2])
    mojePolecenia.push_back(&PoleceniaRenderowania::PrzesuniecieNaPozycje);
    
    if(!nieWidoczny)mojePolecenia.push_back(&PoleceniaRenderowania::RysujGeometriePowierzchnie);
    
//    mojePolecenia.push_back(&PoleceniaRenderowania::PoGeometrii);
//    mojePolecenia.push_back(&T::PrzedGeometria);
//    mojePolecenia.push_back(&T::RysujGeometrie);
//    mojePolecenia.push_back(&T::PoGeometrii);
}



//dla linkera
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<PoleceniaRenderowania>();
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<Renderowanie>();
