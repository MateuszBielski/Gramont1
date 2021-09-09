#ifndef Renderowanie_H
#define Renderowanie_H
#include <gtkglmm.h>

#include "../Shared/ekrangl.h"
#include "../Polecenie/obslugapolecen.h"
#include "../Polecenie/poleceniarenderowania.h"
using namespace std;
using namespace Gtk;




class Renderowanie : public ObslugaPolecen, public PoleceniaRenderowania
{
    friend class TestRenderKlas;
    spEkranGL ekranGL = nullptr;
    spDoNarysowania doNarysowania;
//    PoleceniaRenderowania polecenia;
    
public:
    Renderowanie();
    virtual ~Renderowanie();
    void UstawEkran(spEkranGL);
    virtual void FunPrzerysuj(spDoNarysowania ) override;
    virtual void ustawDoNarysowania(spDoNarysowania) override;
    virtual void RysujScene();
//    void RysujScene(spDoNarysowania);
//    void WywolajPoleceniaZ(spDoNarysowania){};
    
protected:

private:
    void PrzypiszFunkcjeGLdoWskaznikow();
    void RejestrujListeGL();
    
    
    GLuint listid;
    float x[3], y[3], z[3];
    
        
};
using spRenderowanie = shared_ptr<Renderowanie>;
using upRenderowanie = unique_ptr<Renderowanie>;
#endif // Renderowanie_H
