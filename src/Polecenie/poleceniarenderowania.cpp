#include "poleceniarenderowania.h"
#include "../Shared/donarysowania.h"//dla linkera - na końcu pliku

void PustaFunkcja(const char*)
{
    
}
template<class T>
void PoleceniaRenderowania::WywolajPoleceniaZ(T obiektZpoleceniami){
    auto blokadaMutexu = obiektZpoleceniami->getBlokadaMutexu();
    for(auto& pol : obiektZpoleceniami->Polecenia())
        {
            (this->*pol.polecenie)(pol.geometria);
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
//        cout<<"ile normalnych: "<<geom->ileNormalnych<<endl;-
        for(unsigned short n = 0 ; n < geom->ileNormalnych ; n++)
        {
            p_glNormal3fv(&geom->normalne[n*3]);
            for(unsigned short s = 0 ; s < geom->schematNormalnych[n] ; s++)
            p_glVertex3fv(&geom->wspolrzedneVrtx[geom->indeksyVertexow[v++]*3]);
        }
        glEnd();
}
void PoleceniaRenderowania::Przesun(spGeometriaModelu geom)
{
	float* p = geom->Przesuniecie();
    p_glTranslatef(p[0],p[1],p[2]);
    (*ptrFunkcjaMonitorujaca)("Przesun");
}

void PoleceniaRenderowania::RysujGeometrieKrawedzie(spGeometriaModelu)
{
    (*ptrFunkcjaMonitorujaca)("RysujGeometrieKrawedzie");
}

void PoleceniaRenderowania::RysujGeometriePunkty(spGeometriaModelu)
{
    (*ptrFunkcjaMonitorujaca)("RysujGeometriePunkty");
}

void PoleceniaRenderowania::PushMatrix(spGeometriaModelu)
{
    (*ptrFunkcjaMonitorujaca)("PushMatrix");
}

void PoleceniaRenderowania::PopMatrix(spGeometriaModelu)
{
    (*ptrFunkcjaMonitorujaca)("PopMatrix");
}

//dla linkera
template void PoleceniaRenderowania::WywolajPoleceniaZ(shared_ptr<DoNarysowania> );
