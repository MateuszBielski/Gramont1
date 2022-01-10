#include "donarysowaniamock.h"


const float* DoNarysowaniaMock::MacierzObrotu()
{
	macierzObrotuIsUsed = true;
}
l_PolecenieIgeometria& DoNarysowaniaMock::Polecenia()
{
    poleceniaIsUsed = true;
    return DoNarysowania::Polecenia();
}
l_PolecenieIgeometriaAktywna& DoNarysowaniaMock::PoleceniaAktywne()
{
	poleceniaAktywneIsUsed = true;
    return DoNarysowania::PoleceniaAktywne();
}
const float* DoNarysowaniaMock::Przesuniecie()
{
	przesuniecieIsUsed = true;
    return Transformowalne::Przesuniecie();
}
void DoNarysowaniaMock::AktualizujMojePolecenia()
{
	aktualizujMojePoleceniaIsUsed = true;
}
void DoNarysowaniaMock::PoleceniaWybierzIwstawWdobrejKolejnosci()
{
	DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci();
    poleceniaWybierzIwstawWdobrejKolejnosciIsUsed = true;
}

void DoNarysowaniaMock::JestObrot(bool b)
{
    jestObrot = b;
}


void DoNarysowaniaMock::JestPrzesuniecie(bool b)
{
    jestPrzesuniecie = b;
}

