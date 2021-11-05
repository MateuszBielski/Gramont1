#ifndef PoleceniaRenderowania_H
#define PoleceniaRenderowania_H
#include <iostream>
#include <memory>
#include <future>
#include "../Shared/geometriamodelu.h"

using namespace std;

using ptr_vc = void(*)(const char *);
using ptr_vfff = void(*)(float,float,float);
using ptr_vfp = void(*)(const float*);
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
    void Przesun(spGeometriaModelu);
    void PushMatrix(spGeometriaModelu);
    void PopMatrix(spGeometriaModelu);
    void PushName(spGeometriaModelu);
    void PopName(spGeometriaModelu);
    
    template<typename T>
    void WywolajPoleceniaZ(T obiektZwezlami);
	
protected:
    ptr_vc ptrFunkcjaMonitorujaca = &PustaFunkcja;
    
    ptr_vfff p_glTranslatef = nullptr, p_glVertex3f = nullptr;
    ptr_vfp p_glVertex3fv = nullptr, p_glNormal3fv = nullptr;
    //dla testow
    future<void>* fut;
    
private:
        
};
using spPoleceniaRenderowania = shared_ptr<PoleceniaRenderowania>;
using upPoleceniaRenderowania = unique_ptr<PoleceniaRenderowania>;
#endif // PoleceniaRenderowania_H
