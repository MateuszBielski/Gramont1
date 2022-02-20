#include "obliczeniadlamodeli.h"
#include "../Pomocnicze/FunkcjeIstruktury.h"


void ObliczeniaDlaModeli::UtrwalTransformacje(spDoNarysowania rys)
{
	const float * m = rys->MacierzObrotu();
    for(short i = 0; i < rys->ileVertexow ; i++)
    {
        IloczynMacierzy4fIwektora3fzTymczasowym(rys->MacierzObrotu(),rys->wspolrzedneVrtx + (i*3));
    }
}
