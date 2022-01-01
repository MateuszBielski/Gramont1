#ifndef DoNarysowania_H
#define DoNarysowania_H
#include <list>

#include "geometriamodelu.h"
#include "../Polecenie/poleceniarenderowania.h"
#include "nazwa.h"
#include "grupowalne.h"
#include <mutex>

using namespace std;

using PtrMemRend_Geom = void(PoleceniaRenderowania::*)(spGeometriaModelu);

struct PolecenieIgeometria
{
    PtrMemRend_Geom polecenie;
    spGeometriaModelu geometria;
};

using l_PolecenieIgeometria = list<PolecenieIgeometria>;

class DoNarysowania : public GeometriaModelu, public Grupowalne_T<DoNarysowania>
{
    friend class DoNarysowaniaDostepPrv;
//    mutable std::mutex mutexDlaTymczasowej;
    mutable std::mutex mut;
//    int zmienna[3];
    Nazwa nazwa;
    
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
    DoNarysowania(){};
    virtual ~DoNarysowania();
    void setNazwa(Nazwa&& );
    Nazwa getNazwa();
    virtual void PoleceniaWybierzIwstawWdobrejKolejnosci();
    virtual void AktualizujMojePolecenia();
    void UstawListyPoAktualizacji();
    void UstawListyPrzedAktualizacja();
    void AktualizujMojePoleceniaNaLiscieZabezpieczonej();
    
    virtual l_PolecenieIgeometria& Polecenia();
    bool czyPoleceniaListaGlownaJestTaSama(l_PolecenieIgeometria* );
    void WstawPolecenieNaKoncu(PtrMemRend_Geom);
    l_PolecenieIgeometria::iterator itPierwszeMojePolecenie();
    l_PolecenieIgeometria::iterator itOstatnieMojePolecenie();
    unique_lock<mutex> getBlokadaMutexu();// uzywane tylko w PoleceniaRenderowania::WywolajPoleceniaZ
    
    void NieWidoczny(bool);
private:
    virtual void PodczasDodajDziecko() override;
    virtual void PodczasOdejmijDziecko() override;
};

using spDoNarysowania = shared_ptr<DoNarysowania>;
using upDoNarysowania = unique_ptr<DoNarysowania>;

#endif // DoNarysowaniaJakoPolecenia_H
