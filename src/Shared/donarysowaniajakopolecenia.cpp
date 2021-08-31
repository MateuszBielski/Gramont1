#ifndef DoNarysowaniaJakoPolecenia_CPP
#define DoNarysowaniaJakoPolecenia_CPP
//#include "donarysowaniajakopolecenia.h"
#include "../Process/renderowanie.h"

template<typename T>
void DoNarysowaniaJakoPolecenia::PoleceniaWybierzIwstawWdobrejKolejnosci(T rys)
{
       mojePolecenia.push_back(&Renderowanie::PrzedGeometria);
       mojePolecenia.push_back(&Renderowanie::RysujGeometrie);
       mojePolecenia.push_back(&Renderowanie::PoGeometrii);
}


list<PtrMemRend_T> DoNarysowaniaJakoPolecenia::Polecenia()
{
	return mojePolecenia;
}
#endif