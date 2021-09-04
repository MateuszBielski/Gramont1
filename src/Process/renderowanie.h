#ifndef Renderowanie_H
#define Renderowanie_H
#include <gtkglmm.h>

#include "../Shared/ekrangl.h"
#include "../Polecenie/obslugapolecen.h"
#include "../Polecenie/poleceniarenderowania.h"
using namespace std;
using namespace Gtk;

using ptr_vfff = void(*)(float,float,float);
using ptr_vfp = void(*)(const float*);

struct DuzaStruktura
{
    int jeden, dwa, trzy, cztery, adhja, adiaoida, adhaius;
    ptr_vfff jakisWskaznik;
    ptr_vv ptrRysujGeometrieTest = nullptr;
   ptr_vv ptrPoGeometriiTest = nullptr;
    ptr_vv ptrPrzedGeometriaTest = nullptr;
    double dewwe, dqwsdzcs, dwqqweqwddd, dqwqwdqwdnj, bjahsbhjdhbad;
};

class Renderowanie : public ObslugaPolecen, public PoleceniaRenderowania
{
    friend class TestRenderKlas;
    spEkranGL ekranGL = nullptr;
    spDoNarysowania doNarysowania;
//    DuzaStruktura stru;
//    PoleceniaRenderowania polecenia;
    
public:
    Renderowanie();
    virtual ~Renderowanie();
    void UstawEkran(spEkranGL);
    virtual void FunPrzerysuj(spDoNarysowania ) override;
    virtual void ustawDoNarysowania(spDoNarysowania) override;
    virtual void RysujScene();
//    void WywolajPoleceniaZ(spDoNarysowania){};
    
protected:

private:
    void PrzypiszFunkcjeGLdoWskaznikow();
    void RejestrujListeGL();
    
    
    
    ptr_vfff p_glTranslatef = nullptr, p_glVertex3f = nullptr;
    ptr_vfp p_glVertex3fv = nullptr, p_glNormal3fv = nullptr;
    
    GLuint listid;
    float x[3], y[3], z[3];
    
        
};
using spRenderowanie = shared_ptr<Renderowanie>;
using upRenderowanie = unique_ptr<Renderowanie>;
#endif // Renderowanie_H
