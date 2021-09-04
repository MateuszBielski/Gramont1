#ifndef PoleceniaRenderowania_H
#define PoleceniaRenderowania_H
#include <iostream>
#include <memory>
#include "../Shared/geometriamodelu.h"

using namespace std;

using ptr_vv = void(*)();
void PustaFunkcja();

class PoleceniaRenderowania
{
  public:
    PoleceniaRenderowania(){};
    ~PoleceniaRenderowania(){};
        
    void PrzedGeometria(spGeometriaModelu);
    void RysujGeometrie(spGeometriaModelu);
    void PoGeometrii(spGeometriaModelu);
    
    template<typename T>
    void WywolajPoleceniaZ(T obiektZpoleceniami){
        for(auto& pol : obiektZpoleceniami->Polecenia())
        {
            (this->*pol)(obiektZpoleceniami);
        }
    }
    
	
protected:
//   typedef void(*ptr_vv)() ptrPrzedGeometriaTest = nullptr;
   ptr_vv ptrRysujGeometrieTest = &PustaFunkcja;
   ptr_vv ptrPoGeometriiTest = &PustaFunkcja;
    ptr_vv ptrPrzedGeometriaTest = &PustaFunkcja;
//   ptr_vv ptrRysujGeometrieTest = nullptr;
//   ptr_vv ptrPoGeometriiTest = nullptr;
//    ptr_vv ptrPrzedGeometriaTest = nullptr;
    int jeden, dwa, trzy;
    double dewwe, dqwsdzcs, dwqqweqwddd, dqwqwdqwdnj, bjahsbhjdhbad;
private:
//    int liczba;
        
};
using spPoleceniaRenderowania = shared_ptr<PoleceniaRenderowania>;
using upPoleceniaRenderowania = unique_ptr<PoleceniaRenderowania>;
#endif // PoleceniaRenderowania_H
