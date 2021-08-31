#include "renderowanie.h"
#include <stdexcept>

Renderowanie::Renderowanie():doNarysowania(make_shared<DoNarysowania>()),x{-1.0,0.0,0.0},y{0.5,0.0,0.0},z{0.0,1.0,0.0}
{
    PrzypiszFunkcjeGLdoWskaznikow();
}

Renderowanie::~Renderowanie()
{

}
void Renderowanie::PrzypiszFunkcjeGLdoWskaznikow()
{
	p_glTranslatef = &glTranslatef;
    p_glVertex3f = &glVertex3f;
    p_glVertex3fv = &glVertex3fv;
    p_glNormal3fv = &glNormal3fv;
}
void Renderowanie::RejestrujListeGL()
{
    listid = glGenLists( 1 );
    glNewList( listid, GL_COMPILE );
        p_glTranslatef(0.0,0.0,-10.0);
        glBegin(GL_TRIANGLES);
//        p_glVertex3fv(-1.0,0.0,0.0);
//        p_glVertex3fv(1.0,0.0,0.0);
//        p_glVertex3fv(0.0,1.0,0.0);
        p_glVertex3fv(x);
        p_glVertex3fv(y);
        p_glVertex3fv(z);
    
        glEnd();
    glEndList();
//    cout<<"\nzarejestrowano listę o id "<<listid;
}

void Renderowanie::UstawEkran(spEkranGL e)
{	
	ekranGL = e;
    e->listid = &listid;
    e->RysujScene = [this](){
        RysujScene();
        };
}
void Renderowanie::RysujScene()
{
    if(!doNarysowania)throw invalid_argument("RysujScene() Brak doNarysowania");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); 
    p_glTranslatef(0.0,0.0,-10.0);
    glMultMatrixf(doNarysowania->MacierzObrotu());
    
    if(!doNarysowania->ileNormalnych)return;
    glBegin(GL_TRIANGLE_STRIP);
        unsigned short v = 0;
        for(unsigned short n = 0 ; n < doNarysowania->ileNormalnych ; n++)
        {
            p_glNormal3fv(&doNarysowania->normalne[n*3]);
            for(unsigned short s = 0 ; s < doNarysowania->schematNormalnych[n] ; s++)
            p_glVertex3fv(&doNarysowania->wspolrzedneVrtx[doNarysowania->indeksyVertexow[v++]*3]);
        }
        glEnd();
}
/****************************
void Renderowanie::RysujScene_projektFunkcji()
{
    for(auto poleceniaRysujace :doNarysowania->kolejnePoleceniaRenderowania())
    {
        this->polecenieRysujace;
    }
    //
        
}
void Renderowanie::PrzedGeometriaModelu(spDoNarysowania rys)
{
    //np wejście na następny poziom w hierarchii czyli
    //glPushName()
    //glPushMatrix()
    //transformacje dla danego modelu i jego grupy
}
void Renderowanie::RysujGeometrieModelu(spDoNarysowania rys)
{
    //rozumiane jako petle po wierzcholkach i normalnych
}
void Renderowanie::RysujGeometrieModeluNiestandardowo(spDoNarysowania rys)
{
    //funkcja po funkcji
}
void Renderowanie::PoGeometriiModelu(spDoNarysowania rys)
{
    //wyjście z poziomów, odpowiednią ilość razy np:
    //glPopName();
    //glPopMatrix();
    
}


****************************/
void Renderowanie::FunPrzerysuj(spDoNarysowania rys)
{	
    doNarysowania = rys;
    if(ekranGL)ekranGL->WykonajWkontekscieGL(&Renderowanie::RysujScene,*this);
}
void Renderowanie::ustawDoNarysowania(spDoNarysowania rys)
{
	doNarysowania = rys;
}
