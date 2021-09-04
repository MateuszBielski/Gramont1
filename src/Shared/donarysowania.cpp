#include "donarysowania.h"
//#include "../Process/renderowanie.h"
void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci()
{
    mojePolecenia.push_back(&PoleceniaRenderowania::PrzedGeometria);
    mojePolecenia.push_back(&PoleceniaRenderowania::RysujGeometrie);
    mojePolecenia.push_back(&PoleceniaRenderowania::PoGeometrii);
//    mojePolecenia.push_back(&Renderowanie::PrzedGeometria);
//    mojePolecenia.push_back(&Renderowanie::RysujGeometrie);
//    mojePolecenia.push_back(&Renderowanie::PoGeometrii);
}
l_PtrMemRend_Geom DoNarysowania::Polecenia()
{
    return mojePolecenia;
}
void DoNarysowania::WstawPolecenie(PtrMemRend_Geom polecenie)
{
    mojePolecenia.push_back(polecenie);
}