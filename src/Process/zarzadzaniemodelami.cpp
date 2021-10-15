#include "zarzadzaniemodelami.h"
#include "../Polecenie/przerysuj.h"
#include "../Polecenie/ustawdonarysowania.h"
#include <functional>

ZarzadzanieModelami::ZarzadzanieModelami()
:kolejkaPrzetwarzaniaAsynchronicznego(make_shared<KolejkaMiedzyWatkami<PtrMemZarz>>())
{
//    Stan = &ZarzadzanieModelami::Nic;
    Stan = &ObslugaPolecen::Nic;
}
void ZarzadzanieModelami::DoTransformacji(spDoNarysowania tr)
{
	doTrasformacjiPoprzedni = doTrasformacji;
    if(doTrasformacjiPoprzedni)
    doTrasformacjiPoprzedni->jestTransformacja = false;
	
    doTrasformacji = tr;
    tr->jestTransformacja = true;
    kolejkaPrzetwarzaniaAsynchronicznego->push(&ZarzadzanieModelami::AktualizujPoleceniaUstawionegoDoTransformacji);
    kolejkaPrzetwarzaniaAsynchronicznego->push(&ZarzadzanieModelami::AktualizujPoleceniaUstawionegoDoTransformacjiPoprz);
}
void ZarzadzanieModelami::DoNarysowania(spDoNarysowania rys)
{
	doNarysowania = rys;
    kolejkaPrzetwarzaniaAsynchronicznego->push(&ZarzadzanieModelami::PrzygotujPoleceniaUstawionegoDoNarysowania);
}
void ZarzadzanieModelami::DoNarysowaniaItransformacji(spDoNarysowania r)
{
    r->PoleceniaWybierzIwstawWdobrejKolejnosci();
    doNarysowania = r;
    doTrasformacji = r;
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


void ZarzadzanieModelami::WysylaniePrzerysujPoTransformacji()
{
    Stan = &ZarzadzanieModelami::WyslijPoleceniePrzerysuj;
}
void ZarzadzanieModelami::UstawStanNic()
{
	Stan = &ObslugaPolecen::Nic;
}
void ZarzadzanieModelami::Run()
{
    przetwarzanieModeliWatek = AsynchronicznePrzetwarzanieModeliUruchom();
    ObslugaPolecen::Run();
    AsynchronicznePrzetwarzanieModeliZatrzymaj();
    przetwarzanieModeliWatek.join();
}
thread ZarzadzanieModelami::AsynchronicznePrzetwarzanieModeliUruchom()
{
	przetwarzajModele = true;
    return move(thread(&ZarzadzanieModelami::PrzetwarzajModele,this));
}

void ZarzadzanieModelami::AsynchronicznePrzetwarzanieModeliZatrzymaj()
{
    kolejkaPrzetwarzaniaAsynchronicznego->push(&ZarzadzanieModelami::UstawPrzetwarzajModeleFalse);
}
void ZarzadzanieModelami::UstawPrzetwarzajModeleFalse()
{
    przetwarzajModele = false;
}

void ZarzadzanieModelami::PrzetwarzajModele()
{
	PtrMemZarz polecenieZarz;
    while(przetwarzajModele)
    {
        polecenieZarz = kolejkaPrzetwarzaniaAsynchronicznego->wait_and_pop();
        (this->*polecenieZarz)();
    }
}
ZarzadzanieModelami::spKolejkaPolecenZarzadzania ZarzadzanieModelami::KolejkaPrzetwarzaniaAsynchronicznego()
{
	return kolejkaPrzetwarzaniaAsynchronicznego;
}
int ZarzadzanieModelami::LiczbaModeli()
{
	return modele.size();
}
void ZarzadzanieModelami::DodajModel(spDoNarysowania rys)
{
    modele[rys->getNazwa()] = rys;
}
spDoNarysowania ZarzadzanieModelami::WyszukajModel(Nazwa&& n)
{
    auto iter = modele.find(n);
    if(iter != modele.end())return iter->second;
    return nullptr;
}
void ZarzadzanieModelami::AktualizujPoleceniaUstawionegoDoTransformacji()
{
	doTrasformacji->AktualizujMojePolecenia();
}
void ZarzadzanieModelami::AktualizujPoleceniaUstawionegoDoTransformacjiPoprz()
{
	if(doTrasformacjiPoprzedni)
    doTrasformacjiPoprzedni->AktualizujMojePolecenia();
}
void ZarzadzanieModelami::PrzygotujPoleceniaUstawionegoDoNarysowania()
{
    doNarysowania->PoleceniaWybierzIwstawWdobrejKolejnosci();
}

