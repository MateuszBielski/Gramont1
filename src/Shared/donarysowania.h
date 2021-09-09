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
    bool nieWidoczny = false;
public:
//    template<typename T>
    void PoleceniaWybierzIwstawWdobrejKolejnosci();
    l_PolecenieIgeometria Polecenia();
    void WstawPolecenieNaKoncu(PtrMemRend_Geom);
    
    void NieWidoczny(bool);
};

using spDoNarysowania = shared_ptr<DoNarysowania>;
using upDoNarysowania = unique_ptr<DoNarysowania>;

#endif // DoNarysowaniaJakoPolecenia_H
