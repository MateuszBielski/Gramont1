#ifndef Renderowanie_H
#define Renderowanie_H
//#include <gtkmm.h>
#include <gtkglmm.h>
//#include <iostream>
//#include <memory>
#include "../Shared/ekrangl.h"
using namespace std;
using namespace Gtk;

using ptr_vfff = void(*)(float,float,float);
using ptr_vfp = void(*)(const float*);

class Renderowanie
{
  public:
    Renderowanie();
    virtual ~Renderowanie();
    void UstawEkran(spEkranGL);
    bool ZarejestrujListeIprzerysujEkran(GdkEventButton* );
//	bool ZarejestrujListeIrysujScene(GdkEventButton* );
    bool ZarejestrujBezKontekstuRysujWlasnaWkontekscie(GdkEventButton* );
protected:

private:
    void PrzypiszFunkcjeGLdoWskaznikow();
    void RejestrujListeGL();
    void RejestrujListeGLJednorazowo();
    void RysujScene();
    
    
    spEkranGL ekranGL = nullptr;
    ptr_vfff p_glTranslatef = nullptr, p_glVertex3f = nullptr;
    ptr_vfp p_glVertex3fv = nullptr;
    GLuint listid;
    float x[3], y[3], z[3];
    bool listaZarejestrowana = false;
    
        
};
using spRenderowanie = shared_ptr<Renderowanie>;
using upRenderowanie = unique_ptr<Renderowanie>;
#endif // Renderowanie_H
