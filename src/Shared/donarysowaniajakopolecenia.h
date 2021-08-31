#ifndef DoNarysowaniaJakoPolecenia_H
#define DoNarysowaniaJakoPolecenia_H
#include <list>
#include "../Polecenie/poleceniarenderowania.h"
#include "../Process/renderowanie.h"

using namespace std;

template<typename T>
class DoNarysowaniaJakoPolecenia
{
    using PtrMemRend_T = void(PoleceniaRenderowania::*)(T);
    
//    spDoNarysowania doNarysowania;
    list<PtrMemRend_T> mojePolecenia;
public:
    DoNarysowaniaJakoPolecenia(){};
    virtual ~DoNarysowaniaJakoPolecenia(){};
    void PoleceniaWybierzIwstawWdobrejKolejnosci(T)
    {
        mojePolecenia.push_back(&Renderowanie::PrzedGeometria);
        mojePolecenia.push_back(&Renderowanie::RysujGeometrie);
        mojePolecenia.push_back(&Renderowanie::PoGeometrii);
    }
    list<PtrMemRend_T> Polecenia(){
        return mojePolecenia;
    }
    
	
protected:

private:
        
};


//#include "donarysowaniajakopolecenia.cpp"
#endif // DoNarysowaniaJakoPolecenia_H
