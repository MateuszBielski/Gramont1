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
    int licznikTransformacjiDoPrzerysowania = 0;
    spKolejkaPolecen kolejkaRenderowania = nullptr;
    int przerysujPoTyluTransformacjach = 1;
  public:
    ZarzadzanieModelami();
    virtual ~ZarzadzanieModelami(){};
	virtual spTransformowalne DoTransformacji() override {return doTrasformacji;};
    virtual void PowiadomionyOzakonczeniuTransformacji() override;
    int LicznikTransformacjiAkumulowanych();
    void NadawanieDoRenderowania(spKolejkaPolecen);
    void LiczbaTransformacjiDoAkumulowania(int);
    virtual void WyslijPoleceniePrzerysuj() override ;
    void WysylaniePrzerysujPoTransformacji();
    virtual void UstawStanNic() override;
    
    void DoTransformacji(spTransformowalne );
    void DoNarysowania(spDoNarysowania);
    
    
protected:
    virtual void WykonajStan() override {(this->*Stan)();};
private:
    void (ZarzadzanieModelami::*Stan)();
    void Nic(){};
        
};
using spZarzadzanieModelami = shared_ptr<ZarzadzanieModelami>;
using upZarzadzanieModelami = unique_ptr<ZarzadzanieModelami>;
#endif // ZarzadzanieModelami_H
