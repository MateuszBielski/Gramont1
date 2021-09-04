#include "poleceniarenderowania.h"
#include "../Shared/donarysowania.h"//dla linkera - na końcu pliku

void PustaFunkcja(const char*)
{
    
}
template<class T>
void PoleceniaRenderowania::WywolajPoleceniaZ(T obiektZwezlami){
    for(auto& obiektZpoleceniami : obiektZwezlami->StrukturaJakoLista_Wezly())
    {
        for(auto& pol : obiektZpoleceniami->Polecenia())
        {
            (this->*pol)(obiektZpoleceniami);
        }
    }
}
void PoleceniaRenderowania::PrzedGeometria(spGeometriaModelu)
{
//    cout<<"PoleceniaRenderowania::PrzedGeometria"<<endl;
    (*ptrFunkcjaMonitorujaca)("PrzedGeometria");
}

void PoleceniaRenderowania::RysujGeometrie(spGeometriaModelu rys)
{
//    cout<<"PoleceniaRenderowania::RysujGeometrie"<<endl;
//    cout<<"IleVertexow"<<rys->ileVertexow<<endl;
    (*ptrFunkcjaMonitorujaca)("RysujGeometrie");
}

void PoleceniaRenderowania::PoGeometrii(spGeometriaModelu)
{
//    cout<<"PoleceniaRenderowania::PoGeometrii"<<endl;
    (*ptrFunkcjaMonitorujaca)("PoGeometrii");
}

//dla linkera
template void PoleceniaRenderowania::WywolajPoleceniaZ(shared_ptr<DoNarysowania> );