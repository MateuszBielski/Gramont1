#include "donarysowaniamock.h"


float* DoNarysowaniaMock::MacierzObrotu()
{
	macierzObrotuIsUsed = true;
}
l_PolecenieIgeometria& DoNarysowaniaMock::Polecenia()
{
    poleceniaIsUsed = true;
    return DoNarysowania::Polecenia();
}
float* DoNarysowaniaMock::Przesuniecie()
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
	poleceniaWybierzIwstawWdobrejKolejnosciIsUsed = true;
}

