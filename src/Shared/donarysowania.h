#ifndef DoNarysowania_H
#define DoNarysowania_H
#include <list>
#include "geometriamodelu.h"
#include "../Polecenie/poleceniarenderowania.h"

using namespace std;

using PtrMemRend_Geom = void(PoleceniaRenderowania::*)(spGeometriaModelu);
using l_PtrMemRend_Geom = list<PtrMemRend_Geom>;

class DoNarysowania : public GeometriaModelu
{
    
    l_PtrMemRend_Geom mojePolecenia;
public:
    void PoleceniaWybierzIwstawWdobrejKolejnosci();
    l_PtrMemRend_Geom Polecenia();
    void WstawPolecenie(PtrMemRend_Geom);
};

using spDoNarysowania = shared_ptr<DoNarysowania>;
using upDoNarysowania = unique_ptr<DoNarysowania>;
/*
template<typename T,typename Rend>
class DoNarysowaniaJakoPolecenia
{
    using PtrMemRend_T = void(Rend::*)(T);
    
    list<PtrMemRend_T> mojePolecenia;
public:
    DoNarysowaniaJakoPolecenia(){};
    virtual ~DoNarysowaniaJakoPolecenia(){};
    void WstawPolecenie(PtrMemRend_T polecenie)
    {
        mojePolecenia.push_back(polecenie);
    }
    void PoleceniaWybierzIwstawWdobrejKolejnosci(T)
    {
        mojePolecenia.push_back(&Rend::PrzedGeometria);
        mojePolecenia.push_back(&Rend::RysujGeometrie);
        mojePolecenia.push_back(&Rend::PoGeometrii);
    }
    list<PtrMemRend_T> Polecenia(){
        return mojePolecenia;
    }

        
};
*/

//#include "donarysowaniajakopolecenia.cpp"
#endif // DoNarysowaniaJakoPolecenia_H
