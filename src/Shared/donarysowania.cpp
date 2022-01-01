#include "donarysowania.h"
#include "../Process/renderowanie.h"

l_PolecenieIgeometria& DoNarysowania::Polecenia()
{
    return listaGlownaOdlaczona ? mojePoleceniaTymczasowa : mojePolecenia;
}
void DoNarysowania::WstawPolecenieNaKoncu(PtrMemRend_Geom polecenie)
{
    PolecenieIgeometria polIGeom = {polecenie,WskaznikNaMnie()};
    mojePolecenia.push_back(polIGeom);
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
    if(jestTransformacja)
    {
        mojePolecenia.push_back({&PoleceniaRenderowania::PushMatrix,WskaznikNaMnie()});
        mojePolecenia.push_back({&PoleceniaRenderowania::Przesun,WskaznikNaMnie()});
    }
    if(jestObrot)mojePolecenia.push_back({&PoleceniaRenderowania::MultMatrix,WskaznikNaMnie()});
    if(!nieWidoczny)mojePolecenia.push_back({&PoleceniaRenderowania::RysujGeometriePowierzchnie,WskaznikNaMnie()});
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
    if(jestTransformacja)
    mojePolecenia.push_back({&PoleceniaRenderowania::PopMatrix,WskaznikNaMnie()});
    #if defined TESTOWANIE_F
        //musi być jakaś funkcja kończąca poziom stosu
        mojePolecenia.push_back({&PoleceniaRenderowania::PopName,WskaznikNaMnie()});
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
//	return listaGlownaOdlaczona? unique_lock<mutex>(mutexDlaTymczasowej):unique_lock<mutex>(mut);
    return unique_lock<mutex>(mut);
}
DoNarysowania::~DoNarysowania()
{
//	mut.lock();
//    
//    mutexDlaTymczasowej.lock();
//    mut.unlock();
//    mutexDlaTymczasowej.unlock();
}







//dla linkera
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<PoleceniaRenderowania>();
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<Renderowanie>();
