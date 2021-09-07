#ifndef PoleceniaRenderowania_H
#define PoleceniaRenderowania_H
#include <iostream>
#include <memory>
#include "../Shared/geometriamodelu.h"

using namespace std;

using ptr_vc = void(*)(const char *);
void PustaFunkcja(const char *);

class PoleceniaRenderowania
{
  public:
    PoleceniaRenderowania(){};
    ~PoleceniaRenderowania(){};
        
    void PrzedGeometria(spGeometriaModelu);
    void RysujGeometrie(spGeometriaModelu);
    void PoGeometrii(spGeometriaModelu);
    void RysujGeometriePowierzchnie(spGeometriaModelu);
    void RysujGeometrieKrawedzie(spGeometriaModelu);
    void RysujGeometriePunkty(spGeometriaModelu);
    void PrzesuniecieNaPozycje(spGeometriaModelu);
    
    template<typename T>
    void WywolajPoleceniaZ(T obiektZwezlami);
	
protected:
    ptr_vc ptrFunkcjaMonitorujaca = &PustaFunkcja;
private:
        
};
using spPoleceniaRenderowania = shared_ptr<PoleceniaRenderowania>;
using upPoleceniaRenderowania = unique_ptr<PoleceniaRenderowania>;
#endif // PoleceniaRenderowania_H
