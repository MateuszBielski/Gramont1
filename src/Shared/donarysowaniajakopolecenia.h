#ifndef DoNarysowaniaJakoPolecenia_H
#define DoNarysowaniaJakoPolecenia_H
#include <list>

using namespace std;

template<typename T,typename Rend>
class DoNarysowaniaJakoPolecenia
{
    using PtrMemRend_T = void(Rend::*)(T);
    
    list<PtrMemRend_T> mojePolecenia;
public:
    DoNarysowaniaJakoPolecenia(){};
    virtual ~DoNarysowaniaJakoPolecenia(){};
    void PoleceniaWybierzIwstawWdobrejKolejnosci(T)
    {
        mojePolecenia.push_back(&Rend::PrzedGeometria);
        mojePolecenia.push_back(&Rend::RysujGeometrie);
        mojePolecenia.push_back(&Rend::PoGeometrii);
    }
    list<PtrMemRend_T> Polecenia(){
        return mojePolecenia;
    }
    
	
protected:

private:
        
};


//#include "donarysowaniajakopolecenia.cpp"
#endif // DoNarysowaniaJakoPolecenia_H
