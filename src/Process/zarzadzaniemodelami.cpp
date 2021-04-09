#include "zarzadzaniemodelami.h"
#include "../Polecenie/przerysuj.h"


void ZarzadzanieModelami::DoTransformacji(spTransformowalne tr)
{
	doTrasformacji = tr;
}
int ZarzadzanieModelami::LicznikTransformacjiDoPrzerysowania()
{
	return licznikTransformacjiDoPrzerysowania;
}
void ZarzadzanieModelami::PowiadomionyOzakonczeniuTransformacji()
{
	bool granica = przerysujPoTyluTransformacjach == ++licznikTransformacjiDoPrzerysowania;
//    if(granica && kolejkaRenderowania)kolejkaRenderowania->push(make_unique<PoleceniePuste>(0));
    if(granica)licznikTransformacjiDoPrzerysowania = 0;
}
void ZarzadzanieModelami::NadawanieDoRenderowania(spKolejkaPolecen k)
{
	kolejkaRenderowania = k;
}
void ZarzadzanieModelami::PrzerysujPoTyluTransformacjach(int k)
{
	przerysujPoTyluTransformacjach = k;
}
void ZarzadzanieModelami::WyslijPoleceniePrzerysuj()
{
    if(kolejkaRenderowania)kolejkaRenderowania->push(make_unique<Przerysuj>());
}
