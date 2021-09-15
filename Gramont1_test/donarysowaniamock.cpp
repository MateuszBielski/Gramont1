#include "donarysowaniamock.h"


float* DoNarysowaniaMock::MacierzObrotu()
{
	macierzObrotuIsUsed = true;
}
l_PolecenieIgeometria DoNarysowaniaMock::Polecenia()
{
    poleceniaIsUsed = true;
    l_PolecenieIgeometria pustaLista;
    return pustaLista;
}
float* DoNarysowaniaMock::Przesuniecie()
{
	przesuniecieIsUsed = true;
    return Transformowalne::Przesuniecie();
}
