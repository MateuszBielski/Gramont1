#include "zarzadzaniemodelami.h"
#include "../Polecenie/przerysuj.h"
#include "../Polecenie/ustawdonarysowania.h"
#include <functional>

ZarzadzanieModelami::ZarzadzanieModelami()
{
//    Stan = &ZarzadzanieModelami::Nic;
    Stan = &ObslugaPolecen::Nic;
}
void ZarzadzanieModelami::DoTransformacji(spTransformowalne tr)
{
	doTrasformacji = tr;
}
int ZarzadzanieModelami::LicznikTransformacjiAkumulowanych()
{
	return licznikTransformacjiDoPrzerysowania;
}
void ZarzadzanieModelami::PowiadomionyOzakonczeniuTransformacji()
{
	bool granica = przerysujPoTyluTransformacjach == ++licznikTransformacjiDoPrzerysowania;
//    if(granica && kolejkaRenderowania)kolejkaRenderowania->push(make_unique<PoleceniePuste>(0));
    if(granica)licznikTransformacjiDoPrzerysowania = 0;
}
void ZarzadzanieModelami::NadawanieDoRenderowania(spKolejkaPolecen k,bool ustawicDoNarysowania)
{
	kolejkaRenderowania = k;
    if(ustawicDoNarysowania)k->push(make_unique<UstawDoNarysowania>(doNarysowania));
}
void ZarzadzanieModelami::LiczbaTransformacjiDoAkumulowania(int k)
{
	przerysujPoTyluTransformacjach = k;
}
void ZarzadzanieModelami::WyslijPoleceniePrzerysuj()
{
//    cout<<"\nZarzadzanieModelami::WyslijPoleceniePrzerysuj";
    if(kolejkaRenderowania)kolejkaRenderowania->push(make_unique<Przerysuj>(doNarysowania));
}
void ZarzadzanieModelami::DoNarysowania(spDoNarysowania rys)
{
	doNarysowania = rys;
}
void ZarzadzanieModelami::DoNarysowaniaItransformacji(spDoNarysowania r)
{
    r->PoleceniaWybierzIwstawWdobrejKolejnosci();
    doNarysowania = r;
    doTrasformacji = r;
}
void ZarzadzanieModelami::WysylaniePrzerysujPoTransformacji()
{
    Stan = &ZarzadzanieModelami::WyslijPoleceniePrzerysuj;
}
void ZarzadzanieModelami::UstawStanNic()
{
	Stan = &ObslugaPolecen::Nic;
}
thread ZarzadzanieModelami::AsynchronicznePrzetwarzanieModeliUruchom()
{
	return move(thread(&ZarzadzanieModelami::PrzetwarzajModele,this));
}

void ZarzadzanieModelami::AsynchronicznePrzetwarzanieModeliZatrzymaj()
{
	
}
void ZarzadzanieModelami::PrzetwarzajModele()
{
	
}
queue<ZarzadzanieModelami::PtrMemZarz>& ZarzadzanieModelami::KolejkaPrzetwarzaniaAsynchronicznego()
{
	return kolejkaPrzetwarzaniaAsynchronicznego;
}
