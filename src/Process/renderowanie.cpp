#include "renderowanie.h"

Renderowanie::Renderowanie():x{-1.0,0.0,0.0},y{1.0,0.0,0.0},z{0.0,1.0,0.0}
{
    PrzypiszFunkcjeGLdoWskaznikow();
    RejestrujListeGL();
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
    cout<<"\nzarejestrowano listę o id "<<listid;
}
void Renderowanie::RejestrujListeGLJednorazowo()
{
	if(listaZarejestrowana)return;
    RejestrujListeGL();
    listaZarejestrowana = true;
}
void Renderowanie::UstawEkran(spEkranGL e)
{	
	ekranGL = e;
    e->listid = &listid;
//    e->
    e->RysujScene = [this](){
        RejestrujListeGLJednorazowo();
        RysujScene();
        };
}

void Renderowanie::ZarejestrujBezKontekstuRysujWlasnaWkontekscie()
{
//	cout<<"\nRenderowanie::ZarejestrujBezKontekstuRysujWlasnaWkontekscie";
//    RejestrujListeGLJednorazowo();
    RejestrujListeGL();
    ekranGL->WykonajWkontekscieGL(&Renderowanie::RysujScene,*this);
    x[1] += 0.1;
    for(int i = 0 ;i < 3 ;i++) cout<<x[i]<<" ";
}
 
void Renderowanie::RysujScene()
{
//	cout<<"\nRenderowanie::RysujScene";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
//    cout<<"\nwywołanie listy o id "<<listid;
    glCallList(listid);
//    cout<<"glGetError "<<glGetError();
}
void Renderowanie::FunPrzerysuj(spDoNarysowania rys)
{	
	rys->MacierzObrotu();
}
