#ifndef ObslugaPolecen_H
#define ObslugaPolecen_H
//#include <gtkmm.h>
//#include <gtkglmm.h>
#include <iostream>
#include <memory>
#include "../Shared/transformowalne.h"
#include "kolejkapolecen.h"

using namespace std;
//using namespace Gtk;


class ObslugaPolecen
{
    bool run = true;
public:
    ObslugaPolecen();
    virtual ~ObslugaPolecen(){};
    virtual spTransformowalne DoTransformacji() = 0;
    virtual void PowiadomionyOzakonczeniuTransformacji() = 0;
    spKolejkaPolecen getKolejkaPolecen() {return kolejka;};
    void Run();
    void StopRun();
    
    bool doTransformacjiUsed = false;
	
protected:
    spKolejkaPolecen kolejka;
    int protLicznikRun = 0;
private:
        
};
using spObslugaPolecen = shared_ptr<ObslugaPolecen>;
using upObslugaPolecen = unique_ptr<ObslugaPolecen>;
#endif // ObslugaPolecen_H
