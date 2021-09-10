#include "poleceniarenderowania.h"
#include "../Shared/donarysowania.h"//dla linkera - na końcu pliku

void PustaFunkcja(const char*)
{
    
}
template<class T>
//void PoleceniaRenderowania::WywolajPoleceniaZ(T obiektZwezlami){
void PoleceniaRenderowania::WywolajPoleceniaZ(T obiektZpoleceniami){
     for(auto& pol : obiektZpoleceniami->Polecenia())
        {
            (this->*pol.polecenie)(obiektZpoleceniami);
        }
}
void PoleceniaRenderowania::PrzedGeometria(spGeometriaModelu)
{
    (*ptrFunkcjaMonitorujaca)("PrzedGeometria");
}

void PoleceniaRenderowania::RysujGeometrie(spGeometriaModelu rys)
{
    (*ptrFunkcjaMonitorujaca)("RysujGeometrie");
}

void PoleceniaRenderowania::PoGeometrii(spGeometriaModelu)
{
    (*ptrFunkcjaMonitorujaca)("PoGeometrii");
}
void PoleceniaRenderowania::RysujGeometriePowierzchnie(spGeometriaModelu geom)
{
    (*ptrFunkcjaMonitorujaca)("RysujGeometriePowierzchnie");
    if(!geom->ileNormalnych)return;
    glBegin(GL_TRIANGLE_STRIP);
        unsigned short v = 0;
        for(unsigned short n = 0 ; n < geom->ileNormalnych ; n++)
        {
            p_glNormal3fv(&geom->normalne[n*3]);
            for(unsigned short s = 0 ; s < geom->schematNormalnych[n] ; s++)
            p_glVertex3fv(&geom->wspolrzedneVrtx[geom->indeksyVertexow[v++]*3]);
        }
        glEnd();
}

void PoleceniaRenderowania::RysujGeometrieKrawedzie(spGeometriaModelu)
{
    (*ptrFunkcjaMonitorujaca)("RysujGeometrieKrawedzie");
}

void PoleceniaRenderowania::RysujGeometriePunkty(spGeometriaModelu)
{
    (*ptrFunkcjaMonitorujaca)("RysujGeometriePunkty");
}
void PoleceniaRenderowania::PrzesuniecieNaPozycje(spGeometriaModelu)
{
	(*ptrFunkcjaMonitorujaca)("PrzesuniecieNaPozycje");
}

//dla linkera
template void PoleceniaRenderowania::WywolajPoleceniaZ(shared_ptr<DoNarysowania> );
