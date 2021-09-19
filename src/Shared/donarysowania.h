#ifndef DoNarysowania_H
#define DoNarysowania_H
#include <list>
#include "geometriamodelu.h"
#include "../Polecenie/poleceniarenderowania.h"

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
    
    l_PolecenieIgeometria mojePolecenia;
    l_PolecenieIgeometria* poleceniaListaGlowna = nullptr;
    
    l_PolecenieIgeometria::iterator pierwszeMojePolecenie;
    l_PolecenieIgeometria::iterator ostatnieMojePolecenie;
    
    bool nieWidoczny = false;
public:
    void PoleceniaWybierzIwstawWdobrejKolejnosci();
    void AktualizujMojePolecenia();
    virtual l_PolecenieIgeometria& Polecenia();
    void WstawPolecenieNaKoncu(PtrMemRend_Geom);
    l_PolecenieIgeometria::iterator itPierwszeMojePolecenie();
    l_PolecenieIgeometria::iterator itOstatnieMojePolecenie();
    
    void NieWidoczny(bool);
};

using spDoNarysowania = shared_ptr<DoNarysowania>;
using upDoNarysowania = unique_ptr<DoNarysowania>;

#endif // DoNarysowaniaJakoPolecenia_H
