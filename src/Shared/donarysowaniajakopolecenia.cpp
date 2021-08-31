#include "donarysowaniajakopolecenia.h"
#include "../Process/renderowanie.h"

DoNarysowaniaJakoPolecenia::DoNarysowaniaJakoPolecenia()
{
}

DoNarysowaniaJakoPolecenia::~DoNarysowaniaJakoPolecenia()
{

}
void DoNarysowaniaJakoPolecenia::PoleceniaWybierzIwstawWdobrejKolejnosci(spDoNarysowania)
{
	mojePolecenia.push_back(&Renderowanie::PrzedGeometria);
	mojePolecenia.push_back(&Renderowanie::RysujGeometrie);
	mojePolecenia.push_back(&Renderowanie::PoGeometrii);
}
list<PtrMemRend_doNarys> DoNarysowaniaJakoPolecenia::Polecenia()
{
	return mojePolecenia;
}
