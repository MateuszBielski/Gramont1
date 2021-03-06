#ifndef DoNarysowania_H
#define DoNarysowania_H
#include <list>

#include "geometriamodelu.h"
#include "../Polecenie/poleceniarenderowania.h"
#include "nazwa.h"
#include "grupowalne.h"
#include <mutex>

using namespace std;
/*
using PtrMemRend_Geom = void(PoleceniaRenderowania::*)(spGeometriaModelu);

struct PolecenieIgeometria
{
    PtrMemRend_Geom polecenie;
    spGeometriaModelu geometria;
};
*/
using PtrMemRend_Geom = void(PoleceniaRenderowania::*)(spGeometriaModelu);

template<typename T_ptr_geom>
struct PolecenieIgeometria
{
    PtrMemRend_Geom polecenie;
    T_ptr_geom geometria;//przy tworzeniu ma być weak_ptr a później aktywacja
    ~PolecenieIgeometria()
    {
        int i = 1;
    };
};
using PolecenieIgeometriaSlabe = PolecenieIgeometria<weak_ptr<GeometriaModelu>>;
using PolecenieIgeometriaAktywne = PolecenieIgeometria<spGeometriaModelu>;
using l_PolecenieIgeometria = list<PolecenieIgeometriaSlabe>;
using l_PolecenieIgeometriaAktywna = list<PolecenieIgeometriaAktywne>;

class DoNarysowania : public GeometriaModelu, public Grupowalne_T<DoNarysowania>
{
    friend class DoNarysowaniaDostepPrv;
    mutable std::mutex mutexDlaTymczasowej;
    mutable std::mutex mut;
//    int zmienna[3];
    Nazwa nazwa;
    
    l_PolecenieIgeometriaAktywna mojePoleceniaAktywne;
    l_PolecenieIgeometria mojePolecenia;
    l_PolecenieIgeometria mojePoleceniaTymczasowa;
    l_PolecenieIgeometria* poleceniaListaGlowna = nullptr;
    bool listaGlownaOdlaczona = false;
    bool aktualizacjaUkonczona = false;
    bool listaGlownaSkopiowana = true;
    
    l_PolecenieIgeometria::iterator pierwszeMojePolecenie;
    l_PolecenieIgeometria::iterator ostatnieMojePolecenie;
    
    bool nieWidoczny = false;
public:
    DoNarysowania();
    ~DoNarysowania();
    DoNarysowania(const DoNarysowania&);
    DoNarysowania& operator = (const DoNarysowania&);
    void setNazwa(Nazwa&& );
    Nazwa getNazwa();
    virtual void PoleceniaWybierzIwstawWdobrejKolejnosci();
    virtual void ListePolecenResetuj();
    virtual void AktualizujMojePolecenia();
    void UstawListyPoAktualizacji();
    void UstawListyPrzedAktualizacja();
    void AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    
    virtual l_PolecenieIgeometria& Polecenia();
    virtual l_PolecenieIgeometriaAktywna& PoleceniaAktywne();
    virtual void PrzekazPoleceniaIaktywujDla(shared_ptr<DoNarysowania> rysDest);
    bool czyPoleceniaListaGlownaJestTaSama(l_PolecenieIgeometria* );
    void WstawPolecenieNaKoncu(PtrMemRend_Geom);
    l_PolecenieIgeometria::iterator itPierwszeMojePolecenie();
    l_PolecenieIgeometria::iterator itOstatnieMojePolecenie();
    unique_lock<mutex> getBlokadaMutexu();// uzywane tylko w PoleceniaRenderowania::WywolajPoleceniaZ
    
    void NieWidoczny(bool);
private:
    virtual void PodczasDodajDziecko() override;
    virtual void PodczasOdejmijDziecko() override;
    int id = 0;
    static int liczbaKonstruktorow;
    static int liczbaDestruktorow;
    static int ostatnioZniszczony;
    static vector<bool> obiektZniszczony;
};

using spDoNarysowania = shared_ptr<DoNarysowania>;
using upDoNarysowania = unique_ptr<DoNarysowania>;

#endif // DoNarysowaniaJakoPolecenia_H
