#include "poleceniarenderowania.h"

void PustaFunkcja()
{
    
}

void PoleceniaRenderowania::PrzedGeometria(spGeometriaModelu)
{
    cout<<"PoleceniaRenderowania::PrzedGeometria"<<endl;
    (*ptrPrzedGeometriaTest)();
}

void PoleceniaRenderowania::RysujGeometrie(spGeometriaModelu rys)
{
    cout<<"PoleceniaRenderowania::RysujGeometrie"<<endl;
    cout<<"IleVertexow"<<rys->ileVertexow<<endl;
    (*ptrRysujGeometrieTest)();
}

void PoleceniaRenderowania::PoGeometrii(spGeometriaModelu)
{
    cout<<"PoleceniaRenderowania::PoGeometrii"<<endl;
    (*ptrPoGeometriiTest)();
}
