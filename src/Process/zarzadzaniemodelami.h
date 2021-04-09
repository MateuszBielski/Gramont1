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
    int licznikTransformacjiDoPrzerysowania = 0;
    spKolejkaPolecen kolejkaRenderowania = nullptr;
    int przerysujPoTyluTransformacjach = 1;
  public:
    ZarzadzanieModelami(){};
    virtual ~ZarzadzanieModelami(){};
	virtual spTransformowalne DoTransformacji() override {return doTrasformacji;};
    virtual void PowiadomionyOzakonczeniuTransformacji() override;
    int LicznikTransformacjiDoPrzerysowania();
    void NadawanieDoRenderowania(spKolejkaPolecen);
    void PrzerysujPoTyluTransformacjach(int);
    virtual void WyslijPoleceniePrzerysuj() override ;
    
    void DoTransformacji(spTransformowalne );
    
    
protected:

private:
        
};
using spZarzadzanieModelami = shared_ptr<ZarzadzanieModelami>;
using upZarzadzanieModelami = unique_ptr<ZarzadzanieModelami>;
#endif // ZarzadzanieModelami_H
