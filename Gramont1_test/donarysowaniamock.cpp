#include "donarysowaniamock.h"


float* DoNarysowaniaMock::MacierzObrotu()
{
	macierzObrotuIsUsed = true;
}
l_PolecenieIgeometria DoNarysowaniaMock::Polecenia()
{
    polecenieaIsUsed = true;
    l_PolecenieIgeometria pustaLista;
    return pustaLista;
}
