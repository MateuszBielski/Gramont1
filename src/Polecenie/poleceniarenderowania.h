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
    PoleceniaRenderowania();
    virtual ~PoleceniaRenderowania();
        
    void PrzedGeometria(spGeometriaModelu);
    void RysujGeometrie(spGeometriaModelu);
    void PoGeometrii(spGeometriaModelu);
    template<typename T>
    void WywolajPoleceniaZ(T& obiektZpoleceniami){
        for(auto& pol : obiektZpoleceniami->Polecenia())
        {
            (this->*pol)(obiektZpoleceniami);
        }
    }
    
	
protected:
//   typedef void(*ptr_vv)() ptrPrzedGeometriaTest = nullptr;
//   ptr_vv ptrRysujGeometrieTest = nullptr;
//   ptr_vv ptrPoGeometriiTest = nullptr;
//    ptr_vv ptrPrzedGeometriaTest = &PustaFunkcja;

private:
//    int liczba;
        
};
using spPoleceniaRenderowania = shared_ptr<PoleceniaRenderowania>;
using upPoleceniaRenderowania = unique_ptr<PoleceniaRenderowania>;
#endif // PoleceniaRenderowania_H
