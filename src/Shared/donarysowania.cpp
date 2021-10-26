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
    lock_guard<mutex> lk(mut);
    if(!poleceniaListaGlowna)poleceniaListaGlowna = &mojePolecenia;
    if(jestTransformacja)
    {
        mojePolecenia.push_back({&PoleceniaRenderowania::PushMatrix,WskaznikNaMnie()});
        mojePolecenia.push_back({&PoleceniaRenderowania::Przesun,WskaznikNaMnie()});
    }
    if(!nieWidoczny)mojePolecenia.push_back({&PoleceniaRenderowania::RysujGeometriePowierzchnie,WskaznikNaMnie()});
    for(auto& dziecko : dzieci)
    {
        dziecko->poleceniaListaGlowna = poleceniaListaGlowna;
        dziecko->PoleceniaWybierzIwstawWdobrejKolejnosci();
        //zakładam, że iteratory dziecka: mojePierwsze i ostatnie polecenie przeniesione zostaną teraz do 
        //listy głównej
        mojePolecenia.splice(mojePolecenia.end(),dziecko->mojePolecenia);
    }
    if(jestTransformacja)
    mojePolecenia.push_back({&PoleceniaRenderowania::PopMatrix,WskaznikNaMnie()});
    
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
        lock_guard<mutex> lk(mut);
        auto przedTymWstawiamyNowaZawartosc = poleceniaListaGlowna->
        erase(pierwszeWymienianegoZakresu,++ostatnieWymienianegoZakresu);
        poleceniaListaGlowna->splice(przedTymWstawiamyNowaZawartosc,mojePolecenia);
    }
    aktualizacjaUkonczona = true;
}
void DoNarysowania::UstawListyPoAktualizacji()
{
    listaGlownaOdlaczona = false;
    if(aktualizacjaUkonczona)
    {
        mojePoleceniaTymczasowa = mojePolecenia;
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
	return unique_lock<mutex>(mut);
}







//dla linkera
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<PoleceniaRenderowania>();
//template void DoNarysowania::PoleceniaWybierzIwstawWdobrejKolejnosci<Renderowanie>();
