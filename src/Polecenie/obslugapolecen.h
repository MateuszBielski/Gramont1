#ifndef ObslugaPolecen_H
#define ObslugaPolecen_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "../Shared/transformowalne.h"
#include "../Shared/donarysowania.h"
#include "kolejkapolecen.h"

using namespace std;
//using namespace Gtk;

class ZarzadzanieItfc
{
public:
    virtual void WyslijPoleceniePrzerysuj() {};
    virtual spTransformowalne DoTransformacji() {};
    virtual void PowiadomionyOzakonczeniuTransformacji(){};
    bool doTransformacjiUsed = false;
};

class RenderowanieItfc
{
public:
    virtual void FunPrzerysuj(spDoNarysowania ){};
    bool przerysujDostaloDoNarysowania = false;
};



class ObslugaPolecen : public ZarzadzanieItfc, public RenderowanieItfc
{
    bool run = true;
public:
    ObslugaPolecen();
    virtual ~ObslugaPolecen(){};
    spKolejkaPolecen getKolejkaPolecen() {return kolejka;};
    void Run();
    void StopRun();
protected:
    spKolejkaPolecen kolejka;
    int protLicznikRun = 0;
    virtual void WykonajStan() {};
    virtual void UstawStanNic() {};
    
private:
        
};
using spObslugaPolecen = shared_ptr<ObslugaPolecen>;
using upObslugaPolecen = unique_ptr<ObslugaPolecen>;
#endif // ObslugaPolecen_H
