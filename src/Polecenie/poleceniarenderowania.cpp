#include "poleceniarenderowania.h"
#include "../Shared/donarysowania.h"//dla linkera - na końcu pliku

void PustaFunkcja(const char*)
{
    
}
template<class T>
void PoleceniaRenderowania::WywolajPoleceniaZ(T obiektZpoleceniami){
    auto blokadaMutexu = obiektZpoleceniami->getBlokadaMutexu();
    #if defined TESTOWANIE_F
//    cout<<"przed fut.wait"<<endl;
    try
    {
        prom.set_value();
        fut.wait(); 
    }catch(...)
    {
        
    }
//    cout<<"po fut.wait"<<endl;
    #endif
    for(auto& pol : obiektZpoleceniami->Polecenia())
        {
            (this->*pol.polecenie)(pol.geometria);
        }
}
void PoleceniaRenderowania::PrzedGeometria(spGeometriaModelu)
{
    #if defined TESTOWANIE_F    
    (*ptrFunkcjaMonitorujaca)("PrzedGeometria");
    #endif
}

void PoleceniaRenderowania::RysujGeometrie(spGeometriaModelu rys)
{
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("RysujGeometrie");
    #endif
}

void PoleceniaRenderowania::PoGeometrii(spGeometriaModelu)
{
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("PoGeometrii");
    #endif
}
void PoleceniaRenderowania::RysujGeometriePowierzchnie(spGeometriaModelu geom)
{
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("RysujGeometriePowierzchnie");
//    cout<<"RysujGeometriePowierzchnie"<<endl;
    #endif
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
	const float* p = geom->Przesuniecie();
    p_glTranslatef(p[0],p[1],p[2]);
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("Przesun");
    #endif
}

void PoleceniaRenderowania::RysujGeometrieKrawedzie(spGeometriaModelu)
{
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("RysujGeometrieKrawedzie");
    #endif
}

void PoleceniaRenderowania::RysujGeometriePunkty(spGeometriaModelu)
{
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("RysujGeometriePunkty");
    #endif
}

void PoleceniaRenderowania::PushMatrix(spGeometriaModelu)
{
    glPushMatrix();
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("PushMatrix");
    #endif
}

void PoleceniaRenderowania::PopMatrix(spGeometriaModelu)
{
    glPopMatrix();
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("PopMatrix");
    #endif
}

void PoleceniaRenderowania::PushName(spGeometriaModelu)
{   
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("PushName");
    #endif
}

void PoleceniaRenderowania::PopName(spGeometriaModelu)
{
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("PopName");
    #endif
}
void PoleceniaRenderowania::MultMatrix(spGeometriaModelu geom)
{
	glMultMatrixf(geom->MacierzObrotu());
    #if defined TESTOWANIE_F
    (*ptrFunkcjaMonitorujaca)("MultMatrix");
    #endif
}

//dla linkera
template void PoleceniaRenderowania::WywolajPoleceniaZ(shared_ptr<DoNarysowania> );
