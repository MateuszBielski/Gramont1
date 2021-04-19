#include "renderowanie.h"

Renderowanie::Renderowanie():doNarysowania(make_shared<DoNarysowania>()),x{-1.0,0.0,0.0},y{1.0,0.0,0.0},z{0.0,1.0,0.0}
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
    float a[] = {1.0,1.5,0.5};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); 
    p_glTranslatef(0.0,0.0,-10.0);
    glMultMatrixf(doNarysowania->MacierzObrotu());
    glBegin(GL_TRIANGLE_STRIP);
    p_glVertex3fv(x);
    p_glVertex3fv(y);
    p_glVertex3fv(z);
    p_glVertex3fv(a);

    glEnd();
//    glCallList(listid);
}

void Renderowanie::FunPrzerysuj(spDoNarysowania rys)
{	
    doNarysowania = rys;
    if(ekranGL)ekranGL->WykonajWkontekscieGL(&Renderowanie::RysujScene,*this);
}
void Renderowanie::ustawDoNarysowania(spDoNarysowania rys)
{
	doNarysowania = rys;
}
