#include "donarysowania.h"
#include "../Process/renderowanie.h"

l_PolecenieIgeometria& DoNarysowania::Polecenia()
{
    return listaGlownaOdlaczona ? mojePoleceniaTymczasowa : mojePolecenia;
}
l_PolecenieIgeometriaAktywna& DoNarysowania::PoleceniaAktywne()
{
    return mojePoleceniaAktywne;
}
void DoNarysowania::PrzekazPoleceniaIaktywujDla(shared_ptr<DoNarysowania> rysDest)
{
    rysDest->mojePoleceniaAktywne.clear();
    for(auto &pol : mojePolecenia)
    {
        rysDest->mojePoleceniaAktywne.push_back(
        {pol.polecenie,pol.geometria.lock()});
    }
    mojePolecenia.clear();
}
void DoNarysowania::WstawPolecenieNaKoncu(PtrMemRend_Geom polecenie)
{
//    PolecenieIgeometria polIGeom = {polecenie,WskaznikNaMnie()};
    mojePolecenia.push_back({polecenie,WskaznikNaMnieSlaby()});
}
void DoNarysowania::NieWidoczny(bool flaga)
{  
    nieWidoczny = flaga;
}
void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci()
{
//    cout<<"PoleceniaWybierzIwstawWdobrejKolejnosci "<<this<<endl;
    
//    lock_guard<mutex> lk(mut);
//    mut.lock();
    if(!poleceniaListaGlowna)poleceniaListaGlowna = &mojePolecenia;
    if(przeznaczonyDoTransformacji)
    {
        mojePolecenia.push_back({&PoleceniaRenderowania::PushMatrix,WskaznikNaMnieSlaby()});
        mojePolecenia.push_back({&PoleceniaRenderowania::Przesun,WskaznikNaMnieSlaby()});
    }
    if(jestObrot || przeznaczonyDoTransformacji)mojePolecenia.push_back({&PoleceniaRenderowania::MultMatrix,WskaznikNaMnieSlaby()});
    if(!nieWidoczny)mojePolecenia.push_back({&PoleceniaRenderowania::RysujGeometriePowierzchnie,WskaznikNaMnieSlaby()});
//    mut.unlock();
    for(auto& dziecko : dzieci)
    {
        dziecko->poleceniaListaGlowna = poleceniaListaGlowna;
        dziecko->PoleceniaWybierzIwstawWdobrejKolejnosci();
        //zakładam, że iteratory dziecka: mojePierwsze i ostatnie polecenie przeniesione zostaną teraz do 
        //listy głównej
//        mut.lock();
        mojePolecenia.splice(mojePolecenia.end(),dziecko->mojePolecenia);
//        mut.unlock();
    }
//    mut.lock();
    if(przeznaczonyDoTransformacji)
    mojePolecenia.push_back({&PoleceniaRenderowania::PopMatrix,WskaznikNaMnieSlaby()});
    #if defined TESTOWANIE_F
        //musi być jakaś funkcja kończąca poziom stosu
        mojePolecenia.push_back({&PoleceniaRenderowania::PopName,WskaznikNaMnieSlaby()});
    #endif
//    mut.unlock();
    pierwszeMojePolecenie = mojePolecenia.begin();
    ostatnieMojePolecenie = --mojePolecenia.end();
}
void DoNarysowania::AktualizujMojePolecenia()
{
	UstawListyPrzedAktualizacja();
    AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    UstawListyPoAktualizacji();
}
void DoNarysowania::UstawListyPrzedAktualizacja()
{
	if(listaGlownaSkopiowana)
    {
        listaGlownaOdlaczona = true;
        listaGlownaSkopiowana = false;
    }
}
void DoNarysowania::AktualizujMojePoleceniaNaLiscieZabezpieczonej()
{
    aktualizacjaUkonczona = false;
    if(!poleceniaListaGlowna || !listaGlownaOdlaczona){
        listaGlownaSkopiowana = true;
        return;
    }
    mojePolecenia.clear();
    auto pierwszeWymienianegoZakresu = pierwszeMojePolecenie;
    auto ostatnieWymienianegoZakresu = ostatnieMojePolecenie;
    
    PoleceniaWybierzIwstawWdobrejKolejnosci();

    bool czyMojaListaNieJestGlowna = &mojePolecenia != poleceniaListaGlowna;
    if(poleceniaListaGlowna && czyMojaListaNieJestGlowna )
    {
//        lock_guard<mutex> lk(mut);
//        mut.lock();
        auto przedTymWstawiamyNowaZawartosc = poleceniaListaGlowna->
        erase(pierwszeWymienianegoZakresu,++ostatnieWymienianegoZakresu);
        poleceniaListaGlowna->splice(przedTymWstawiamyNowaZawartosc,mojePolecenia);
//        mut.unlock();
    }
    aktualizacjaUkonczona = true;
    int s = (*poleceniaListaGlowna).size();
}
void DoNarysowania::UstawListyPoAktualizacji()
{
    listaGlownaOdlaczona = false;
    if(aktualizacjaUkonczona)
    {   
       
//        lock_guard<mutex> lk(mutexDlaTymczasowej);
//        bool udaloSieZablokowac = mutexDlaTymczasowej.try_lock();
        mojePoleceniaTymczasowa = mojePolecenia;
//        if(udaloSieZablokowac)mutexDlaTymczasowej.unlock();
        listaGlownaSkopiowana = true;
    }
}
l_PolecenieIgeometria::iterator DoNarysowania::itPierwszeMojePolecenie()
{
	return pierwszeMojePolecenie;
}
l_PolecenieIgeometria::iterator DoNarysowania::itOstatnieMojePolecenie()
{
	return ostatnieMojePolecenie;
}
void DoNarysowania::PodczasDodajDziecko()
{
    AktualizujMojePolecenia();
}
void DoNarysowania::PodczasOdejmijDziecko()
{
    AktualizujMojePolecenia();
}
bool DoNarysowania::czyPoleceniaListaGlownaJestTaSama(l_PolecenieIgeometria* wsk)
{
    return poleceniaListaGlowna == wsk;
}
Nazwa DoNarysowania::getNazwa()
{
	return nazwa;
}
void DoNarysowania::setNazwa(Nazwa&& n)
{
	nazwa = move(n);
}

unique_lock<mutex> DoNarysowania::getBlokadaMutexu()
{
	return listaGlownaOdlaczona? unique_lock<mutex>(mutexDlaTymczasowej):unique_lock<mutex>(mut);
//    return unique_lock<mutex>(mut);
}
DoNarysowania& DoNarysowania::operator=(const DoNarysowania& other)
{
    if (this == &other)return *this;
    return *this;
}
DoNarysowania::DoNarysowania(const DoNarysowania& other)
{
    if (this == &other)return;
    mojePolecenia = other.mojePolecenia;
    id = ++liczbaKonstruktorow;
}
int DoNarysowania::liczbaKonstruktorow = 0;
int DoNarysowania::liczbaDestruktorow = 0;
int DoNarysowania::ostatnioZniszczony = 0;
vector<bool> DoNarysowania::obiektZniszczony = vector<bool>(5000,false);
DoNarysowania::DoNarysowania()
{
    int roznica = liczbaKonstruktorow - liczbaDestruktorow;
    id = ++liczbaKonstruktorow;
    if(id == 16)
    {
        int i = 1;
        i++;
    }
    if(roznica > 0)
    {
       int i = 1;
        i++; 
    }
}
    
DoNarysowania::~DoNarysowania()
{
    liczbaDestruktorow++;
    if(obiektZniszczony.at(id))
    {
        //próba powtórnego zniszczenia
        int i = id;
        i++;
    }
    if((id - ostatnioZniszczony) > 1)
    {
        //tzn poprzedni id nie został zniszczony
        int i = id - ostatnioZniszczony;
        i++;
    }
    if(id < ostatnioZniszczony)
    {
        //niszczy w odwrotnej kolejności
        int i = ostatnioZniszczony;
        i++;
    }
    obiektZniszczony.at(id) = true;
    ostatnioZniszczony = id;
    int s = mojePolecenia.size();
    int r = 5;
//	mut.lock();
//    
//    mutexDlaTymczasowej.lock();
//    mut.unlock();
//    mutexDlaTymczasowej.unlock();
}







//dla linkera
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<PoleceniaRenderowania>();
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<Renderowanie>();
