#ifndef ZarzadzanieModelami_H
#define ZarzadzanieModelami_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>

#include "../Shared/transformowalne.h"
#include "../Polecenie/obslugapolecen.h"


using namespace std;
//using namespace Gtk;


class ZarzadzanieModelami : public ObslugaPolecen
{
    spTransformowalne doTrasformacji = nullptr;
    spDoNarysowania doNarysowania = nullptr;
    spKolejkaPolecen kolejkaRenderowania = nullptr;
    int licznikTransformacjiDoPrzerysowania = 0;
    int przerysujPoTyluTransformacjach = 1;
  public:
    ZarzadzanieModelami();
    virtual ~ZarzadzanieModelami(){};
	virtual spTransformowalne DoTransformacji() override {return doTrasformacji;};
    virtual void PowiadomionyOzakonczeniuTransformacji() override;
    virtual void WyslijPoleceniePrzerysuj() override ;
    virtual void UstawStanNic() override;
    
    int LicznikTransformacjiAkumulowanych();
    void NadawanieDoRenderowania(spKolejkaPolecen);
    void LiczbaTransformacjiDoAkumulowania(int);
    void WysylaniePrzerysujPoTransformacji();
    
    void DoTransformacji(spTransformowalne );
    void DoNarysowania(spDoNarysowania);
    void DoNarysowaniaItransformacji(spDoNarysowania);
    
    
protected:
    virtual void WykonajStan() override {(this->*Stan)();};
private:
    void (ZarzadzanieModelami::*Stan)();
        
};
using spZarzadzanieModelami = shared_ptr<ZarzadzanieModelami>;
using upZarzadzanieModelami = unique_ptr<ZarzadzanieModelami>;
#endif // ZarzadzanieModelami_H
